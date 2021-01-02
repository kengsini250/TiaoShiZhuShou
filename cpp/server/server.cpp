#include "../../head/server/server.h"

Server::Server(QWidget *parent):QTcpServer(parent)
{
}

void Server::open(qint16 p)
{
  listen(QHostAddress::Any, p);
}

void Server::send(const QString &msg,const QString& flag)
{
  QString tmp = msg+flag;
  currentClient->write(tmp.toUtf8());
}

void Server::incomingConnection(qintptr socketID)
{
  currentClient = new QTcpSocket(this);
  currentClient->setSocketDescriptor(socketID);
  emit Text("new client " + QString::number(socketID));

  //-------------------new Client------------------------------
  connect(currentClient,&QTcpSocket::readyRead,[this]{
      QString msg;
      msg = currentClient->readAll();
      emit Text(msg);
    });
  connect(currentClient,&QTcpSocket::disconnected,[this,socketID]{
      QString str = QString::number(socketID)+ " disconnect\n";
      emit Text(str);
    });
}
