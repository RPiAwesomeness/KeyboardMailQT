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
  SmtpClient smtp("smtp.gmail.com", 465, SmtpClient::SslConnection);

  smtp.setUser(acctUsername);
  smtp.setPassword(acctPassword);

  MimeMessage message;

  message.addRecipient(new EmailAddress("keyboardmailtesting@gmail.com", "foo"));
  message.setSender(new EmailAddress(acctUsername, "test"));
  message.setSubject("KeyboardMailTesting test");

  MimeText text;
  text.setText("Hi!");

  message.addPart(&text);

  smtp.connectToHost();
  smtp.login();
  smtp.sendMail(message);
  smtp.quit();
}

void MainWindow::on_actionQuit_triggered()
{
  QApplication::quit();
}
