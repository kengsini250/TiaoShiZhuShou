#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>

class Client : public QTcpSocket
{
  Q_OBJECT
public:
  Client(QObject *parent = nullptr);

public slots:
  bool openClient(const QString& ip,qint16 port);
  void receive();
  void send(const QString& msg,const QString& flag = "\n");
signals:
  void rec(const QString&);
};

#endif // CLIENT_H
