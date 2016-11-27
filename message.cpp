#include "message.hpp"

#include <smtp/src/SmtpMime>
#include <vector>

Message::Message(QString displayName, QString email, QString username, QString password) {
  sender = new EmailAddress(email, displayName);
  username = username;
  password = password;
}

// Create the message with the data within the Message object
MimeMessage* Message::createMessage() {
  MimeMessage* message = new MimeMessage;

  message->setSender(sender);
  message->setSubject(subject);
  for (u_int i = 0; i < sizeof(recipients); i++) {
    message->addRecipient(recipients[i]);
  }

  MimeText mimeText;
  mimeText.setText(contents);

  message->addPart(&mimeText);

  messageIsPrepared = true;

  return message;
}

MimeMessage* Message::createMessage(QString subject, QString text, QList<EmailAddress*> recipients) {
  MimeMessage* message = new MimeMessage;

  message->setSender(sender);
  message->setSubject(subject);
  for (u_int i = 0; i < sizeof(recipients); i++) {
    message->addRecipient(recipients[i]);
  }

  MimeText contents;
  contents.setText(text);

  message->addPart(&contents);

  return message;
}

bool Message::sendMessage() {
  // The SMTP client hasn't been configured/message hasn't been created, don't continue
  if (!clientConfigured() || !messageIsPrepared) {
    return false;
  }

  // Chain the different client functions with short-circuit logic
  if (client->connectToHost() && client->login() && client->sendMail(message)) {
    client->quit();
    return true;
  }

  client->quit();
  return false;
}

bool Message::sendMessage(MimeMessage &message) {

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

void Message::setAuth(QString username, QString password) {
  username = username;
  password = password;
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
