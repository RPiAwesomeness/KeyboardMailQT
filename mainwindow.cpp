#include "mainwindow.hpp"
#include "ui_mainwindow.h"

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

void MainWindow::on_pushButton_released()
{
  // Grab the message contents
  ui->textEdit->toPlainText();
  // Grab the recipient email
  ui->lineEdit->text();
  // Send both to email creation function
  // Profit!
}

void MainWindow::on_actionQuit_triggered()
{
  QApplication::quit();
}
