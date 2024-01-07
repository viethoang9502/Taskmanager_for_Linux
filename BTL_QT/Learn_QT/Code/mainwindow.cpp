#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets/QTableWidget>
#include <QProcess>
#include <QStringList>
#include <QDebug>
#include <QListWidgetItem>
#include <QTimer>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QStringList>
#include <QMap>
#include <QString>
#include <QMessageBox>
#include <QRegularExpression>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::Taskmanager)
{
    ui->setupUi(this);
    updateAppHistoryTimer = new QTimer(this);
    connect(updateAppHistoryTimer, &QTimer::timeout, this, &MainWindow::updateAppHistory);
    updateAppHistoryTimer->start(1000);
    // Kết nối nút với các hàm xử lýd
    connect(ui->processesBtn, SIGNAL(clicked()), this, SLOT(showProcessesWidget()));
    connect(ui->performanceBtn, SIGNAL(clicked()), this, SLOT(showPerformanceWidget()));
    connect(ui->apphistoryBtn, SIGNAL(clicked()), this, SLOT(showApphistoryWidget()));
    killProcess = new QProcess(this);
    showProcessesWidget();


}

MainWindow::~MainWindow()
{
    delete ui;
    if (updateAppHistoryTimer->isActive()) {
        updateAppHistoryTimer->stop();
    }
    delete ui;
}

void MainWindow::showProcessesWidget()
{
    // Hiển thị trang chứa processesWidget
    ui->stackedWidget_2->setCurrentIndex(0);

    // Lấy con trỏ đến QTableWidget đã được thêm vào trong tab "Process"
    QTableWidget *tableWidget = ui->tableWidget;


    // Setup table

    ui->tableWidget->setColumnCount(5);
    ui->tableWidget->setColumnWidth(0, 120);
    ui->tableWidget->setColumnWidth(1, 380);
    ui->tableWidget->setColumnWidth(3, 120);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->setHorizontalHeaderLabels({"Process ID", "Name", "Status", "RAM", "CPU"});
    ui->tableWidget->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(ui->tableWidget, &QTableWidget::cellClicked, this, &MainWindow::onTableClicked);
    // Display process here
    connect(ui->tableWidget, &QWidget::customContextMenuRequested, this, &MainWindow::onTableWidgetContextMenu);

    DisplayProcesses();

    // Khởi tạo và cấu hình QTimer
    updateTimer = new QTimer(this);
    connect(updateTimer, &QTimer::timeout, this, &MainWindow::updateTable);

    // Bắt đầu định kỳ cập nhật mỗi 2 giây (2000 ms)
    updateTimer->start(2000);


}
void MainWindow::onTableWidgetContextMenu(const QPoint &pos)
{
    QMenu contextMenu(tr("Context menu"), this);

    QAction action1("End Task", this);
    connect(&action1, &QAction::triggered, this, &MainWindow::killProcessById);
    contextMenu.addAction(&action1);

    contextMenu.exec(ui->tableWidget->viewport()->mapToGlobal(pos));
}

void MainWindow::DisplayProcesses()
{
    QProcess process;
    process.start("ps", QStringList() << "aux");
    process.waitForFinished();

    QByteArray result = process.readAllStandardOutput();
    QString resultString(result);
    // qDebug() << "Dữ liệu đầu ra từ lệnh 'top':\n" << resultString;
    QStringList lines = resultString.split('\n', Qt::SkipEmptyParts);

    // Create a list to store processes data
    QList<QList<QTableWidgetItem*>> processesData;

    foreach (const QString &line, lines) {
        QStringList tokens = line.simplified().split(' ', Qt::SkipEmptyParts);

        if (tokens.size() >= 11) {
            QString processId = tokens.at(1);
            QString processName = tokens.at(10);
            QString processStatus = tokens.at(7);
            QString ramUsage = tokens.at(5);
            QString cpuUsage = tokens.at(2);

            // Create a list to store data for each process
            QList<QTableWidgetItem*> rowData;
            rowData << new QTableWidgetItem(processId);
            rowData << new QTableWidgetItem(processName);
            rowData << new QTableWidgetItem(processStatus);
            rowData << new QTableWidgetItem(ramUsage);
            rowData << new QTableWidgetItem(cpuUsage);

            processesData.append(rowData);
        }
    }

    // Sort processesData based on CPU usage
    std::sort(processesData.begin(), processesData.end(), [](const QList<QTableWidgetItem*> &a, const QList<QTableWidgetItem*> &b) {
        return a[4]->text().toDouble() > b[4]->text().toDouble();
    });

    // Populate the table with sorted data
    ui->tableWidget->setRowCount(0); // Clear existing rows

    int row = 0;
    foreach (const QList<QTableWidgetItem*> &rowData, processesData) {
        ui->tableWidget->insertRow(row);

        // Set data in each cell
        for (int col = 0; col < rowData.size(); ++col) {
            ui->tableWidget->setItem(row, col, rowData.at(col)->clone());
        }

        row++;
    }
}

// Slot để cập nhật bảng tiến trình
void MainWindow::updateTable()
{
    // Dừng timer để tránh cập nhật khi đang xử lý dữ liệu
    updateTimer->stop();

    // Cập nhật bảng tiến trình
    DisplayProcesses();

    // Khởi động lại timer
    updateTimer->start();
}
void MainWindow::onTableClicked(int row, int column) {
    selectedProcessId = ui->tableWidget->item(row, 0)->text();  // Giả sử cột 0 chứa Process ID
    qDebug() << "Selected Process ID: " << selectedProcessId;
}

void MainWindow::killProcessById() {
    if (!killProcess) {
        qDebug() << "killProcess is null!";
        return;
    }

    QStringList args;
    args << "-9" << selectedProcessId;  // Sử dụng -9 để kill ngay lập tức

    killProcess->start("kill", args);
    killProcess->waitForFinished();

    if (killProcess->exitCode() == 0) {
        // Kill thành công, cập nhật bảng tiến trình
        DisplayProcesses();
        qDebug() << "Process" << selectedProcessId << "killed successfully.";

        // Hiển thị thông báo thành công
        QMessageBox::information(this, "Success", "Process killed successfully.");
    } else {
        // Kill thất bại
        qDebug() << "Failed to kill process" << selectedProcessId;

        // Hiển thị thông báo thất bại
        QMessageBox::critical(this, "Error", "Failed to kill the process.");
    }
}


void MainWindow::showPerformanceWidget()
{
    // Hiển thị trang chứa performanceWidget
    ui->stackedWidget_2->setCurrentIndex(1);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(check_cpu()));
    connect(timer, SIGNAL(timeout()), this, SLOT(check_memory()));
    connect(timer, SIGNAL(timeout()), this, SLOT(check_wifi()));
    timer->start(1000);
    QTimer *networkTimer = new QTimer(this);
    connect(networkTimer, SIGNAL(timeout()), this, SLOT(check_network()));
    networkTimer->start(2000);

    // Tạo và cấu hình QChart cho CPU
    series = new QLineSeries();
    chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);


    chart->setTitle("CPU Usage (%)");
    QPen pen(Qt::blue);
    pen.setWidth(3);
    series->setPen(pen);

    // Tạo QChartView cho CPU chart
    chartView = new QChartView(chart);
    chartView->setFixedSize(400, 220);
    chartView->setRenderHint(QPainter::Antialiasing);
    ui->gridLayout_1->addWidget(chartView, 1, 0);

    // Tạo và cấu hình QChart cho Memory
    memorySeries = new QLineSeries();
    memoryChart = new QChart();
    memoryChart->legend()->hide();
    memoryChart->addSeries(memorySeries);


    memoryChart->setTitle("Memory Usage (GB)");
    QPen memoryPen(Qt::green);
    memoryPen.setWidth(3);
    memorySeries->setPen(memoryPen);

    // Tạo QChartView cho Memory chartGB
    memoryChartView = new QChartView(memoryChart);
    memoryChartView->setFixedSize(400, 220);
    memoryChartView->setRenderHint(QPainter::Antialiasing);
    ui->gridLayout_1->addWidget(memoryChartView, 2, 0);

    // Create and configure QLineSeries for WiFi
    wifiSeries = new QLineSeries();
    wifiChart = new QChart();
    wifiChart->legend()->hide();
    wifiChart->addSeries(wifiSeries);

    wifiChart->setTitle("Ethernet Signal (dBM)");
    QPen wifiPen(Qt::red);  // Choose an appropriate colorbmr
    wifiPen.setWidth(3);
    wifiSeries->setPen(wifiPen);

    // Create QChartView for WiFi chartdBm
    wifiChartView = new QChartView(wifiChart);
    wifiChartView->setFixedSize(400, 220); // Adjust size as needed
    wifiChartView->setRenderHint(QPainter::Antialiasing);
    ui->gridLayout_1->addWidget(wifiChartView, 1, 1); // Adjust position as needed

    receivedSeries = new QLineSeries();
    transmittedSeries = new QLineSeries();

    // Khởi tạo QChart cho Network
    networkChart = new QChart();
    networkChart->legend()->hide();
    networkChart->addSeries(receivedSeries);
    networkChart->addSeries(transmittedSeries);

    networkChart->setTitle("Ethernet (Kbps) *Yellow:R Cyan:S*");
    QPen receivedPen(Qt::yellow);
    receivedPen.setWidth(3);
    receivedSeries->setPen(receivedPen);
    QPen transmittedPen(Qt::cyan);
    transmittedPen.setWidth(3);
    transmittedSeries->setPen(transmittedPen);

    // Khởi tạo QChartView cho Network chart
    networkChartView = new QChartView(networkChart);
    networkChartView->setFixedSize(400, 220);
    networkChartView->setRenderHint(QPainter::Antialiasing);
    ui->gridLayout_1->addWidget(networkChartView, 2, 1);
}

void MainWindow::check_cpu() {
    try {
        // Declares used variables for calculation
        unsigned int total_now = 0, user_now = 0;
        std::tuple<unsigned int, unsigned int> tuple = readFile();
        user_now = std::get<0>(tuple);
        total_now = std::get<1>(tuple);

        // The usage is ratio of user's usage and total usage
        // within a certain period of time.
        unsigned int user_over_period = user_now - user, total_over_period = total_now - total;
        int cpu_usage = static_cast<double>(user_over_period)/total_over_period * 100;

        // Adds new point to graph series.
        // Keeps the maximum of points to 10 and updates
        // the chart.
        series->append(iter, cpu_usage);
        iter++;
        if (series->count() > 10) series->remove(0);
        chart->removeSeries(series);
        chart->addSeries(series);
        chart->createDefaultAxes();
        ui->label_2->setText("CPU: <span style=\"color:blue;\">" + QString::number(cpu_usage) + "%</span>");

        // Sets the current number of processes

        // to a global value for next iteration.
        total = total_now;
        user = user_now;

    } catch (QFileDevice::FileError) {
        // If file wasn't found, user will be prompt with dialog 3window
        // and program will close itself.
        QMessageBox::critical(this, "Can't read file /proc/stat", "Please install Linux, ty! :D");
        this->close();
    }

}

// Returns tuple of current number of processes of user and computer
// for current cycle. Reads required data from Linux file /proc/stat
// and converts it to a unsigned integer.
std::tuple<unsigned int, unsigned int> MainWindow::readFile() {
    char line[40];
    unsigned int total_now = 0, user_now = 0, pos = 0;

    QString filename = "/proc/stat";
    QFile file(filename);

    //Tries to open the file else throws error.
    if(file.open(QIODevice::ReadOnly)) {
        file.readLine(line, 40);
        char* str = strtok(line," ");
        while (str != nullptr) {
            total_now += std::strtoul(str, nullptr, 0);
            if(pos < 3) user_now += std::strtoul(str, nullptr, 0);
            str = strtok(nullptr, " ");
            pos++;
        }
// ui->label_2->setText("CPU: " + QString::number(user_now) );
        return std::make_tuple(user_now, total_now);
    } else {
        throw file.error();
    }

}
void MainWindow::check_memory() {
    try {
        qint64 totalMemory = 0, avaiMemory = 0;
        std::tie(totalMemory, avaiMemory) = readMemoryFile();

        double memoryUsage = static_cast<double>(totalMemory - avaiMemory) ;
        // qDebug() << "Memory Usage:" << memoryUsage << "%";
        memorySeries->append(iter, memoryUsage);
        iter++;
        if (memorySeries->count() > 10) memorySeries->remove(0);

        memoryChart->removeSeries(memorySeries);
        memoryChart->addSeries(memorySeries);
        memoryChart->createDefaultAxes();
        ui->label_3->setText("Memory: <span style=\"color:green;\">" + QString::number(totalMemory - avaiMemory) + "/" + QString::number(totalMemory) + " GB</span>");
    } catch (const std::runtime_error &e) {
        QMessageBox::critical(this, "Error", e.what());
        this->close();
    }
}

std::tuple<double, double> MainWindow::readMemoryFile() {
    qint64 totalMemory = 0, avaiMemory = 0;
    QFile file("/proc/meminfo");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        QString line = in.readLine();
        while (!line.isNull()) {


            if (line.startsWith("MemTotal:")) {
                QStringList tokens = line.split(' ', Qt::SkipEmptyParts);
                if (tokens.size() >= 2) {
                    totalMemory = tokens.at(1).toLongLong() / (1024*1024); // Chuyển KB thành MB
                }
            }
            else if (line.startsWith("MemAvailable:")) {
                QStringList tokens = line.split(' ', Qt::SkipEmptyParts);
                if (tokens.size() >= 2) {
                    avaiMemory = tokens.at(1).toLongLong() / (1024*1024); // Chuyển KB thành
                }
        }
                        line = in.readLine();
    }
        file.close(); // Đóng file sau khi đọc
    } else {
        throw std::runtime_error("Unable to open /proc/meminfo");
    }
    return std::make_tuple(totalMemory, avaiMemory);
}
void MainWindow::check_wifi() {
    try {
        bool isConnected;
        int signalStrength;
        std::tie(isConnected, signalStrength) = readWifiFile();

        // qDebug() << "WiFi Connected:" << isConnected;


        // Append the new signal strength to the series
        static int wifiIter = 0;
        wifiSeries->append(wifiIter, signalStrength);
        wifiIter++;
        if (wifiSeries->count() > 10) wifiSeries->remove(0);

        wifiChart->removeSeries(wifiSeries);
        wifiChart->addSeries(wifiSeries);
        wifiChart->createDefaultAxes(); // Adjust axes as needed
        ui->label_5->setText("Ethernet signal: <span style=\"color:red;\">" + QString::number(signalStrength) + " dBM</span>");
    } catch (const std::runtime_error &e){
        QMessageBox::critical(this, "Error", e.what());
        this->close();
    }
}


std::tuple<bool, int> MainWindow::readWifiFile() {
    QFile file("/proc/net/wireless");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        // qDebug() << "Error: Unable to open /proc/net/wireless";
        throw std::runtime_error("Unable to open /proc/net/wireless");
    }

    QTextStream in(&file);
    QString line = in.readLine(); // Read the first line (header)
    // qDebug() << "Header Line 1:" << line;
    line = in.readLine(); // Read the second line (header)
    // qDebug() << "Header Line 2:" << line;

    bool isConnected = false;
    int maxSignalStrength = 0;

    while (!line.isNull()) {
        // qDebug() << "Reading Line:" << line;
        QStringList tokens = line.split(' ', Qt::SkipEmptyParts);
        if (tokens.size() >= 4) {
            QString signalStr = tokens.at(3);
            signalStr.remove('.');
            int signalStrength = signalStr.toInt();
            // qDebug() << "Interface:" << tokens.at(0) << "Signal Strength:" << signalStrength << "dBm";
            if (signalStrength < maxSignalStrength) {
                maxSignalStrength = signalStrength;
                isConnected = true;
            }
        }
        line = in.readLine();
    }

    // qDebug() << "Final Connection Status:" << isConnected;
    // qDebug() << "Highest Signal Strength:" << maxSignalStrength << "dBm";

    file.close();
    return std::make_tuple(isConnected, maxSignalStrength);
}
std::tuple<unsigned long, unsigned long> MainWindow::readNetworkFile() {
    QFile file("/proc/net/dev");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open /proc/net/dev";
        return std::make_tuple(0, 0); // Return default values if file cannot be opened
    }

    QTextStream in(&file);
    QString line = in.readLine();
    unsigned long receivedBytes = 0, transmittedBytes = 0;

    while (!line.isNull()) {
        QStringList tokens = line.split(' ', Qt::SkipEmptyParts);
        if (tokens.size() >= 10) {
            // Assuming the format is consistent with received bytes at index 1 and transmitted bytes at index 9
            receivedBytes += tokens[1].toULong() ;
            transmittedBytes += tokens[9].toULong() ;
        }
        line = in.readLine();
    }

    file.close();

    return std::make_tuple(receivedBytes, transmittedBytes);
}



// Hàm để kiểm tra và cập nhật biểu đồ
void MainWindow::check_network() {
    try {
        unsigned long receivedBytes, transmittedBytes;
        std::tie(receivedBytes, transmittedBytes) = readNetworkFile();

        // Tính toán throughput
        // Tính toán throughput (chú ý đơn vị là Kilobits)
        unsigned long receivedThroughput = (receivedBytes - lastReceivedBytes) * 8 / 2000;
        unsigned long transmittedThroughput = (transmittedBytes - lastTransmittedBytes) * 8 / 2000;


        static int networkIter = 0;
        receivedSeries->append(networkIter, receivedThroughput);
        transmittedSeries->append(networkIter, transmittedThroughput);
        networkIter++;
        if (receivedSeries->count() > 10) receivedSeries->remove(0);
        if (transmittedSeries->count() > 10) transmittedSeries->remove(0);

        networkChart->removeSeries(receivedSeries);
        networkChart->removeSeries(transmittedSeries);
        networkChart->addSeries(receivedSeries);
        networkChart->addSeries(transmittedSeries);
        networkChart->createDefaultAxes();

        // Cập nhật giá trị cuối cùng
        lastReceivedBytes = receivedBytes;
        lastTransmittedBytes = transmittedBytes;
        ui->label_4->setText("Ethernet throughput: <span style=\"color:yellow;\">Received " + QString::number(receivedThroughput) + " Kbps</span>  <span style=\"color:cyan;\">Send  " + QString::number(transmittedThroughput) + " Kbps</span>");
    } catch (const std::runtime_error &e) {
        QMessageBox::critical(this, "Error", e.what());
        this->close();
    }
}
void MainWindow::showApphistoryWidget()
{
    // Hiển thị trang chứa processesWidget
    ui->stackedWidget_2->setCurrentIndex(2);
    displayAppHistory();
}

void MainWindow::displayAppHistory() {
    QMap<QString, QMap<QString, QString>> appHistory = getTopData();

    ui->appHistoryTable->setRowCount(appHistory.size());
    ui->appHistoryTable->setColumnCount(6); // Now 6 columns: App Name, User, Status, %CPU, %RAM, Time
    ui->appHistoryTable->setHorizontalHeaderLabels({"App Name", "Time", "Status", "User", "%CPU", "%RAM"});

    int row = 0;
    QMapIterator<QString, QMap<QString, QString>> i(appHistory);
    while (i.hasNext()) {
        i.next();
        ui->appHistoryTable->setItem(row, 0, new QTableWidgetItem(i.key()));
        ui->appHistoryTable->setItem(row, 3, new QTableWidgetItem(i.value()["User"]));
        ui->appHistoryTable->setItem(row, 2, new QTableWidgetItem(i.value()["Status"]));
        ui->appHistoryTable->setItem(row, 4, new QTableWidgetItem(i.value()["%CPU"]));
        ui->appHistoryTable->setItem(row, 5, new QTableWidgetItem(i.value()["%RAM"]));
        ui->appHistoryTable->setItem(row, 1, new QTableWidgetItem(i.value()["Time"]));

        // Adjust column widths as needed
        ui->appHistoryTable->setColumnWidth(0, 150);
        ui->appHistoryTable->setColumnWidth(1, 160);
        ui->appHistoryTable->setColumnWidth(2, 80);
        ui->appHistoryTable->setColumnWidth(3, 160);
        ui->appHistoryTable->setColumnWidth(4, 155);
        ui->appHistoryTable->setColumnWidth(5, 155);
        row++;
    }
}

QMap<QString, QMap<QString, QString>> MainWindow::getTopData() {
    QProcess process;
    process.start("top", QStringList() << "-b" << "-n" << "1");
    process.waitForFinished(-1);

    QString output(process.readAllStandardOutput());
    QStringList lines = output.split("\n");

    QMap<QString, QMap<QString, QString>> appData;
    bool processListStarted = false;

    foreach (const QString &line, lines) {
        if (line.contains("PID USER")) {
            processListStarted = true;
            continue;
        }

        if (processListStarted && !line.trimmed().isEmpty()) {
            QStringList columns = line.simplified().split(' ');
            if (columns.size() > 11 && columns[1] != "root" && columns[1] != "colord" && columns[1] != "syslog" && !columns[11].contains('-') && !columns[11].contains('+')) {
                QString processName = columns.at(11);
                QString cpuTime = columns.at(10);
                QString cpuUsage = columns.at(8); // %CPU
                QString ramUsage = columns.at(9); // %RAM
                QString user = columns.at(1);      // User
                QString status = columns.at(7);    // Process Status

                if (!appData.contains(processName) || appData[processName]["Time"] < cpuTime) {
                    appData[processName] = {{"%CPU", cpuUsage}, {"%RAM", ramUsage}, {"Time", cpuTime}, {"User", user}, {"Status", status}};
                }
            }
        }
    }

    return appData;
}
void MainWindow::updateAppHistory() {
    displayAppHistory(); // Call the function to update the App History table
}





