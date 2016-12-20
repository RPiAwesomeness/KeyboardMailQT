#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "message.hpp"
#include <QString>
#include "smtp/src/SmtpMime"

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
  QString msgContents = ui->textEdit->toPlainText();
  // Grab the recipient email
  QString recipients = ui->lineEdit->text();
  qInfo() << "Contents:" << msgContents;
  qInfo() << "Recipients:" << recipients;
  // Generate the message from this
  Message message("KeyboardMailQt", "keyboardmailtesting@gmail.com", "keyboardmailtesting@gmail.com", "k3yb0ardMa!l");

  EmailAddress recipient("keyboardmailtesting@gmail.com");

  message.addRecipient(recipient);

  message.setSubject("Foo bar test");
  message.setContents(msgContents);

  message.sendMessage();
  // Profit!
}

void MainWindow::on_actionQuit_triggered()
{
  QApplication::quit();
}
