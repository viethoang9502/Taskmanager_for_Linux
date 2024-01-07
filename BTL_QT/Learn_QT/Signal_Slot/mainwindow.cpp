#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->horizontalScrollBar, SIGNAL(valueChanged(int)), ui->spinBox, SLOT(setValue(int)));
    connect(ui->spinBox, SIGNAL(valueChanged(int)), ui->horizontalScrollBar, SLOT(setValue(int)));

    connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(close()));
    disconnect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(close()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    this->close();
}

