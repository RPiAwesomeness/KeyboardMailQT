#ifndef MESSAGE_HPP
#define MESSAGE_HPP
#include <iostream>
#include <QString>
#include <QList>
#include <smtp/src/SmtpMime>

class Message {
public:
  Message(QString displayName, QString email, QString username, QString password);
  ~Message();


  MimeMessage createMessage();
  MimeMessage createMessage(QString subject, QString contents, QList<QString> recipients);

  bool sendMessage(MimeMessage &message) const;
  bool sendMessage() const;
  bool clientConfigured() const;
  bool setupSmtp(QString path, int port, SmtpClient::ConnectionType connType);

  void setContents(QString contents), setSubject(QString subject);
  void setRecipients(QList<QString> recipients);
  void setAuth(QString username, QString password);

  QString getContents() const;
  QString getSubject() const;

  QList<QString> getRecipients() const;

private:
  QString displayName, username, password;
  QString contents, subject;

  bool configured;

  EmailAddress *sender = nullptr;
  SmtpClient *client = nullptr;
  MimeMessage *message = nullptr;

  QList<QString> recipients;
};

#endif // MESSAGE_HPP

