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
  // Generate the message from this
  SmtpClient smtp("smtp.gmail.com", 465, SmtpClient::SslConnection);

  smtp.setUser("keyboardmailtesting@gmail.com");
  smtp.setPassword("k3yb0ardMa!l");

  MimeMessage message;

  message.addRecipient(new EmailAddress("keyboardmailtesting@gmail.com", "foo"));
  message.setSender(new EmailAddress("keyboardmailtesting@gmail.com", "test"));
  message.setSubject("KeyboardMailTesting test");

  MimeText text;
  text.setText("Hi!");

  message.addPart(&text);

  smtp.connectToHost();
  smtp.login();
  bool success = smtp.sendMail(message);
  smtp.quit();

  qInfo() << success;

//  Message message("KeyboardMailQt", "keyboardmailtesting@gmail.com", "keyboardmailtesting@gmail.com", "k3yb0ardMa!l");
//  message.setupSmtp("smtp.gmail.com", 465, SmtpClient::SslConnection);
//  message.setAuth();

//  EmailAddress *recipient = new EmailAddress(recipients, "test");
//  message.addRecipient(recipient);

//  QString foo = "foo bar test";

//  message.createMessage(foo, msgContents, message.getRecipients());

//  qDebug() << "Configured:" << message.clientConfigured();

//  bool success = message.sendMessage();
//  qDebug() << "Success:" << success;
  // Profit!
}

void MainWindow::on_actionQuit_triggered()
{
  QApplication::quit();
}
