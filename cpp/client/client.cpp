#include "../../head/client/client.h"

Client::Client(QObject *parent):QTcpSocket(parent)
{

}

bool Client::openClient(const QString &ip, qint16 port)
{
  connectToHost(ip,port,QTcpSocket::ReadWrite);
  if(waitForConnected(1000)) receive();
  else                       return false;
  return true;
}

void Client::receive()
{
  connect(this,&QTcpSocket::readyRead,[this]{
      QString msg;
      msg = readAll();
      emit rec(msg);
    });

//  QString msg = readAll();
//  emit rec(msg);
}

void Client::send(const QString &msg,const QString& flag)
{
  QString tmp = msg+flag;
  write(tmp.toUtf8());
}
