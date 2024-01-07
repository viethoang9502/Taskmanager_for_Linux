#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QProcess>
#include <QMainWindow>
#include <QStackedWidget>
#include <tuple>
#include <QMainWindow>
#include <QTime>
#include <QTimer>
#include <QFile>
#include <QIODevice>
#include <QtCharts>
#include <QMessageBox>


QT_BEGIN_NAMESPACE
namespace Ui { class Taskmanager; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{

    Q_OBJECT

public slots:
    void updateTable();


public:
    ~MainWindow();
    void DisplayProcesses();
    explicit MainWindow(QWidget *parent = nullptr);
    QTimer *timer;
    QLineSeries *series;
    QLineSeries *memorySeries;
    QLineSeries *wifiSeries;
    QLineSeries *receivedSeries;
    QLineSeries *transmittedSeries;
    QList<QPair<QString, QDateTime>> readAppHistory();
private slots:
    void check_cpu();
    void check_memory();
    void check_network();
    void showProcessesWidget();
    void showApphistoryWidget();
    void showPerformanceWidget();
    void check_wifi();
private slots:
    void onTableClicked(int row, int column);
    void updateAppHistory();
    void killProcessById();
    void onTableWidgetContextMenu(const QPoint &pos);
    void displayAppHistory();
private:
    QTimer *updateAppHistoryTimer;
    QString selectedProcessId;
    Ui::Taskmanager *ui;
    unsigned long lastReceivedBytes = 0, lastTransmittedBytes = 0;
    unsigned int user, total, iter = 0;
    QChart *memoryChart;
    QChart *networkChart;
    QList<QPair<QString, QDateTime>> appHistory;
    QChartView *memoryChartView;
    QChart *wifiChart;
    QChartView *wifiChartView;
    QChartView *networkChartView;
    QChart *chart;
    QVector<double> list;
    QMap<QString, QMap<QString, QString>> getTopData();
    std::tuple<double, double> readMemoryFile();
    QChartView *chartView;
    std::tuple<unsigned long, unsigned long> readNetworkFile();
    std::tuple<unsigned int, unsigned int> readFile();
    std::tuple<bool, int> readWifiFile();
    QTimer *updateTimer;
    QProcess *killProcess;

};
#endif // MAINWINDOW_H



