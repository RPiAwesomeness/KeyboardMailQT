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
  Message(QString mDisplayName, QString mEmail, QString mUsername, QString mPassword);
  ~Message();

  void createMessage(QString subject, QString contents, QList<EmailAddress*> recipients);

  bool sendMessage();
  bool clientConfigured() const;
  bool setupSmtp(QString path, int port, SmtpClient::ConnectionType connType);

  void setContents(QString contents), setSubject(QString subject);
  void addRecipient(EmailAddress* recipient);
  void setRecipients(QList<EmailAddress*> recipients);
  void setAuth();

  MimeText* getContents();
  QString getSubject() const;

  QList<EmailAddress*> getRecipients() const;

private:
  QString displayName, username, password;
  QString subject;
  MimeText contents;

  bool configured = false;
  bool messageIsPrepared = false;

  EmailAddress *sender = nullptr;
  SmtpClient *client = nullptr;
  MimeMessage message;

  QList<EmailAddress*> recipients;
};

#endif // MESSAGE_HPP

