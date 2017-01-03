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
  Message message("KeyboardMailQt", "keyboardmailtesting@gmail.com", "keyboardmailtesting@gmail.com", "k3yb0ardMa!l");
  message.setupSmtp("smtp.gmail.com", 465, SmtpClient::SslConnection);
  message.setAuth();

  EmailAddress *recipient = new EmailAddress(recipients);
  message.addRecipient(recipient);

  message.createMessage("foo bar test", msgContents, message.getRecipients());

  qDebug() << "Configured:" << message.clientConfigured();

  bool success = message.sendMessage();
  qDebug() << "Success:" << success;
  // Profit!
}

void MainWindow::on_actionQuit_triggered()
{
  QApplication::quit();
}
