#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <BannerWidget.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_normal_clicked() {
    BannerWidget* w = BannerWidget::normal("This is a NORMAL banner", true, -1, this);
    connect(ui->close, &QPushButton::clicked, w, &BannerWidget::close);
}

void MainWindow::on_info_clicked() {
    BannerWidget* w = BannerWidget::information("This is an INFORMATION banner", true, -1, this);
    connect(ui->close, &QPushButton::clicked, w, &BannerWidget::close);
}

void MainWindow::on_critical_clicked() {
    BannerWidget* w = BannerWidget::critical("This is a CRITICAL banner", true, -1, this);
    connect(ui->close, &QPushButton::clicked, w, &BannerWidget::close);
}

void MainWindow::on_inverted_clicked() {
    BannerWidget* w = BannerWidget::inverted("This is an INVERTED banner", true, -1, this);
    connect(ui->close, &QPushButton::clicked, w, &BannerWidget::close);
}

void MainWindow::on_warning_clicked() {
    BannerWidget* w = BannerWidget::warning("This is a WARNING banner", true, -1, this);
    connect(ui->close, &QPushButton::clicked, w, &BannerWidget::close);
}
