#include "message.hpp"

#include <smtp/src/SmtpMime>
#include <vector>

Message::Message(QString displayName, QString email, QString uname, QString pass)
  : sender(new EmailAddress(email, displayName)),
    username(uname),
    password(pass)
{
  MimeMessage message;
  message.setSender(sender);

  SmtpClient client("smtp.gmail.com", 465, SmtpClient::SslConnection);
  client.setUser(username);
  client.setPassword(password);
}

Message::~Message() {
  qDeleteAll(recipients);

  if (sender) {
    delete sender;
  }
}

void Message::createMessage(QString subject, const QString &text, QList<EmailAddress*> recipients) {
  message.setSubject(subject);

  foreach (EmailAddress* recipient, recipients) {
    message.addRecipient(recipient);
  }

  MimeText contents;
  contents.setText(text);

  message.addPart(&contents);
}


void Message::createMessage(QString subject, const QString &text) {
  message.setSubject(subject);

  MimeText contents;
  contents.setText(text);

  message.addPart(&contents);
}

void Message::createMessage(QString subject, const QString &text, QString recipients) {
  message.setSubject(subject);

  MimeText contents;
  contents.setText(text);

  message.addPart(&contents);

  foreach (QString recipient, recipients.split(',')) {
   message.addRecipient(new EmailAddress(recipient, "foo"));
  }
}

bool Message::sendMessage() {

  qInfo() << clientConfigured();

  // The SMTP client hasn't been configured, don't continue
  if (!clientConfigured()) {
    return false;
  }

  // Chain the different client functions with short-circuit logic
  if (client.connectToHost() && client.login()) {
    try {
      client.sendMail(message);
    } catch (...) {
      qInfo() << "stuff went down";
    }
    client.quit();
    return true;
  } else {
    client.quit();
    return false;
  }
}

bool Message::clientConfigured() const {
//  qInfo() << client.
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

void Message::setRecipients(QString recipients) {
  QStringList peeps = recipients.split(',');
  foreach (QString foo, peeps) {
    this->recipients.append(new EmailAddress(foo, "foo"));
  }
}

void Message::addRecipient(EmailAddress* recipient) {
  recipients.append(recipient);
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
