#include "message.hpp"

#include <smtp/src/SmtpMime>
#include <vector>

Message::Message(QString displayName, QString email, QString username, QString password) {
  sender = new EmailAddress(email, displayName);
  username = username;
  password = password;
}

// Create the message with the data within the Message object
MimeMessage Message::createMessage() {
  MimeMessage message;

  message.setSender(sender);
  message.setSubject(this->subject);
  for (u_int i = 0; i < sizeof(recipients); i++) {
    message.addRecipient(recipients[i]);
  }

  MimeText mimeText;
  mimeText.setText(&this->contents);

  message.addPart(&mimeText);

  return message;
}

MimeMessage Message::createMessage(QString subject, QString text, QList<QString> recipients) {
  MimeMessage message;

  message.setSender(this->sender);
  message.setSubject(subject);
  for (u_int i = 0; i < sizeof(recipients); i++) {
    message.addRecipient(recipients[i]);
  }

  MimeText contents;
  contents.setText(text);

  message.addPart(&contents);

  return message;
}

bool Message::sendMessage() const {
  // The SMTP client hasn't been configured/message hasn't been created, don't continue
  if (!clientConfigured() || !message) {
    return false;
  }

  // Chain the different client functions with short-circuit logic
  if (client->connectToHost() && client->login() && client->sendMail(message)) {
    client->quit();
    return true;
  } else {
    client->quit();
    return false;
  }
}

bool Message::sendMessage(MimeMessage &message) const {

  // The SMTP client hasn't been configured, don't continue
  if (!clientConfigured()) {
    return false;
  }

  // Chain the different client functions with short-circuit logic
  if (client->connectToHost() && client->login() && client->sendMail(message)) {
    client->quit();
    return true;
  } else {
    client->quit();
    return false;
  }
}

bool Message::clientConfigured() const {
  return configured;
}

bool Message::setupSmtp(QString path, int port, SmtpClient::ConnectionType connType) {
  SmtpClient client(path, port, connType);
  this->client = &client;
  return true;
}

void Message::setContents(QString contents) {
  this->contents = contents;
}

void Message::setSubject(QString subject) {
  this->subject = subject;
}

void Message::setRecipients(QList<QString> recipients) {
  this->recipients = recipients;
}

void Message::setAuth(QString username, QString password) {
  this->username = username;
  this->password = password;
}

QString Message::getContents() const {
  return this->contents;
}

QString Message::getSubject() const {
  return this->subject;
}

QList<QString> Message::getRecipients() const {
  return this->recipients;
}
