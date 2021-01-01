#ifndef LOCALIP_H
#define LOCALIP_H

#include <QHostAddress>
#include <QNetworkInterface>
#include <QList>

class LocalIp
{
public:
  LocalIp();
  QString ipaddr;
  QString vm_ipaddr;
private:
  QList<QHostAddress> allIpInfo;
};

#endif // LOCALIP_H
