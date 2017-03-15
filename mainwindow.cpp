#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "message.hpp"
#include <QString>
#include <QSettings>
#include "smtp/src/SmtpMime"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
  loadSettings();
  ui->setupUi(this);
  saveSettings();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadSettings() {
  acctUsername = settings.value("acctUsername", "").toString();
  acctPassword = settings.value("acctPassword", "").toString();
  displayName = settings.value("displayName", "").toString();

  qInfo() << "Settings loaded!";
}

void MainWindow::saveSettings() {
  settings.setValue("acctUsername", acctUsername);
  settings.setValue("acctPassword", acctPassword);
  settings.setValue("displayName", displayName);

  qInfo() << "Settings saved!";
}

void MainWindow::on_pushButton_released()
{
  // Grab the message contents
  QString msgContents = ui->textEdit->toPlainText();
  // Grab the recipient email
  QString recipients = ui->lineEdit->text();
  // Generate the message from this
  Message message(displayName, acctUsername, acctUsername, acctPassword);
  message.setRecipients(recipients);
  message.createMessage("KeyboardMail testing", msgContents, recipients);
  message.sendMessage();
}

void MainWindow::on_actionQuit_triggered()
{
  QApplication::quit();
}
