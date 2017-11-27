#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <BannerWidget.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked() {
    BannerWidget* w = BannerWidget::information("Sincronizando dados...", true, -1, this);
    connect(ui->pushButton_2, &QPushButton::clicked, w, &BannerWidget::close);
}

void MainWindow::on_pushButton_3_clicked() {
    BannerWidget* w = BannerWidget::critical("Erro ao sincronizar dados!!!", true, -1, this);
    connect(ui->pushButton_2, &QPushButton::clicked, w, &BannerWidget::close);
}
