#include "../head/TCPIP.h"
#include "ui_tcpip.h"

TCPIP::TCPIP(QWidget* parent) :QWidget(parent)
, ui(new Ui::TCPIP)
{
	ui->setupUi(this);

	LocalIp ipAddr;
	ui->localIpLabel->setText(ipAddr.ipaddr);

	//server
	connect(ui->createButton, &QAbstractButton::clicked, this, &TCPIP::setServerData);
	connect(ui->serverStopButton, &QAbstractButton::clicked, [this] {
		ui->tabClient->setEnabled(true);
		ui->createButton->setEnabled(true);
		ui->serverPortLineEdit->setEnabled(1);
		});

	//client
	connect(ui->connectButton, &QAbstractButton::clicked, this, &TCPIP::setClientData);
	connect(ui->clientStopButton, &QAbstractButton::clicked, [this] {
		ui->tabServer->setEnabled(true);
		ui->connectButton->setEnabled(true);
		ui->ipLineEdit->setEnabled(1);
		ui->clientPortLineEdit->setEnabled(1);
		});
}

void TCPIP::send(Mode m, const QString& msg)
{
	switch (m) 
    {
    case Mode::NONE:break;
	case Mode::CLIENT:
		client->send(msg);
		break;
	case Mode::SERVER:
		server->send(msg);
		break;
	}
}

TCPIP::~TCPIP()
{
	delete ui;
}

void TCPIP::createServer()
{
  server = new Server(this);
  m = Mode::SERVER;
  sendData("listen " + ui->serverPortLineEdit->text());
  server->open(ui->serverPortLineEdit->text().toShort());

  connect(server, &Server::Text, [this](const QString& msg) {
	  sendData(msg);
	  });
}

void TCPIP::createClient()
{
	client = new Client();
    m = Mode::CLIENT;
    client->openClient(ui->ipLineEdit->text(),ui->clientPortLineEdit->text().toShort());
	connect(client, &Client::rec, [this](const QString& msg) {
		sendData(msg);
		});
}

void TCPIP::setServerData()
{
	ui->tabClient->setEnabled(false);
	ui->createButton->setEnabled(false);
	ui->serverPortLineEdit->setEnabled(0);

	ui->serverPortLineEdit->setValidator(re.PORT());
	createServer();
}

void TCPIP::setClientData()
{
	ui->tabServer->setEnabled(false);
	ui->connectButton->setEnabled(false);
	ui->ipLineEdit->setEnabled(0);
	ui->clientPortLineEdit->setEnabled(0);

    ui->clientPortLineEdit->setValidator(re.PORT());
    ui->ipLineEdit->setValidator(re.IP());
	createClient();
}
