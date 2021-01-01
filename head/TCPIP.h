#ifndef TCPIP_H
#define TCPIP_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class TCPIP; }
QT_END_NAMESPACE

#include "regexp.h"
#include "server/server.h"
#include "client/client.h"
#include "localip.h"

enum class Mode { NONE, SERVER, CLIENT };

class TCPIP : public QWidget
{
	Q_OBJECT

public:
	TCPIP(QWidget* parent = nullptr);
	Mode getMode() { return m; }
	void send(Mode m,const QString& msg);
	~TCPIP();
private:
	Ui::TCPIP* ui;
	RegExp re;

	Mode m = Mode::NONE;
	Server* server;
	Client* client;

	void createServer();
	void createClient();


private slots:
	void setClientData();
	void setServerData();

signals:
	void sendCurrIP();
	void sendData(const QString& msg);
};

#endif
