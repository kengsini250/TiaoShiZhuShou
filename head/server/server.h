#ifndef SERVER_H
#define SERVER_H

#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QWidget>
#include <QString>

class Server : public QTcpServer
{
  Q_OBJECT
public:
  Server()=delete;
  Server(QWidget* parent = nullptr);
  void open(qint16 p);
  void send(const QString& msg,const QString& flag = "\n");
protected:
  void incomingConnection(qintptr socketID)override;
private:
  QTcpSocket* currentClient;
Q_SIGNALS:
  void Text(const QString& msg);
};

#endif // SERVER_H
