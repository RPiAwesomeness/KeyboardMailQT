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

  if (sender) {
    delete sender;
  }
  if (client) {
    delete client;
  }
}

void Message::createMessage(QString subject, QString text, QList<EmailAddress*> recipients) {
  message.setSender(sender);
  message.setSubject(subject);
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
  if (client->connectToHost() && client->login()) {
    try {
      client->sendMail(message);
    } catch (...) {
      qInfo() << "stuff went down";
    }
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
  this->client = new SmtpClient(path, port, connType);

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

MimeText* Message::getContents() {
  return &contents;
}

QString Message::getSubject() const {
  return subject;
}

QList<EmailAddress*> Message::getRecipients() const {
  return recipients;
}
