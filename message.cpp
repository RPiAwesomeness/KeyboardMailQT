#include "message.hpp"

#include <smtp/src/SmtpMime>
#include <vector>

Message::Message(QString mDisplayName, QString mEmail, QString mUsername, QString mPassword) {
  sender = new EmailAddress(mEmail, mDisplayName);
  username = mUsername;
  password = mPassword;

  MimeMessage message;
}

Message::~Message() {
  qDeleteAll(recipients);
}

void Message::createMessage(QString subject, QString text, QList<EmailAddress*> recipients) {
  message.setSender(sender);
  message.setSubject(subject);
  qInfo() << recipients;
  for (int i = 0; i < recipients.count(); i++) {
    message.addRecipient(recipients[i]);
  }

  MimeText contents;
  contents.setText(text);

  message.addPart(&contents);

  configured = true;
}

bool Message::sendMessage() {

  qInfo() << clientConfigured();

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

  qInfo() << password;

  return true;
}

void Message::setContents(QString contents) {
  contents = contents;
}

void Message::setSubject(QString subject) {
  subject = subject;
}

void Message::setRecipients(QList<EmailAddress*> recipients) {
  recipients = recipients;
}

void Message::addRecipient(EmailAddress* recipient) {
  recipients.append(recipient);
}

void Message::setAuth() {
  qInfo() << username << password;
  client->setUser(username);
  client->setPassword(password);
}

QString Message::getContents() const {
  return contents;
}

QString Message::getSubject() const {
  return subject;
}

QList<EmailAddress*> Message::getRecipients() const {
  return recipients;
}
