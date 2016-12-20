#ifndef MESSAGE_HPP
#define MESSAGE_HPP
#include <iostream>
#include <QString>
#include <QList>
#include <smtp/src/SmtpMime>

struct MessageDetails {
  QString contents;
  QList<QString> recipient;
};

class Message {
public:
  Message(QString displayName, QString email, QString username, QString password);
  ~Message();

  MimeMessage* createMessage();
  MimeMessage* createMessage(QString subject, QString contents, QList<EmailAddress*> recipients);

  bool sendMessage(MimeMessage &message);
  bool sendMessage();
  bool clientConfigured() const;
  bool setupSmtp(QString path, int port, SmtpClient::ConnectionType connType);

  void setContents(QString contents), setSubject(QString subject);
  void addRecipient(EmailAddress& recipient);
  void setRecipients(QList<EmailAddress> recipients);
  void setAuth(QString username, QString password);

  QString getContents() const;
  QString getSubject() const;

  QList<EmailAddress> getRecipients() const;

private:
  QString displayName, username, password;
  QString contents, subject;

  bool configured = false;
  bool messageIsPrepared = false;

  EmailAddress *sender = nullptr;
  SmtpClient *client = nullptr;
  MimeMessage message;

  QList<EmailAddress> recipients;
};

#endif // MESSAGE_HPP

