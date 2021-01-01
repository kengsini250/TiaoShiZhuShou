#include "../head/localip.h"

LocalIp::LocalIp()
{
  allIpInfo = QNetworkInterface::allAddresses();
  for(int i=0;i<allIpInfo.size();i++){
      if((allIpInfo.at(i)!= QHostAddress::LocalHost)&&
         (allIpInfo.at(i).protocol()==QAbstractSocket::IPv4Protocol))
        {
          QString tmp = allIpInfo.at(i).toString();
          QString tmep=tmp.mid(0,3);
          if(QString::compare(tmep,"192") == 0)
            ipaddr = tmp;
        }
    }
}
