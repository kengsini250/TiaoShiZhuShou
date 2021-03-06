#include "../../head/serial/serial.h"
#include "ui_serial.h"

#define DEBUG
#ifdef DEBUG
#include <QDebug>
#endif // DEBUG

#define WAITTIME 100

Serial::Serial(QWidget* parent):QWidget(parent)
, ui(new Ui::Serial)
{
	ui->setupUi(this);

    auto allPort = QSerialPortInfo::availablePorts();
    for(auto p=allPort.begin();p!=allPort.end();p++){
        ui->portComboBox->addItem((*p).portName());
    }

	connect(ui->serialstartPushButton, &QAbstractButton::clicked, this, &Serial::setData);
	connect(ui->serialstopPushButton, &QAbstractButton::clicked, [&] {
		openFlag = false;
		serialPort.clear();
		serialPort.close();
		});
}

void Serial::send(const QByteArray& msg)
{
	serialPort.write(msg);
}

void Serial::createSerial()
{
	if (serialPort.isOpen()) {
		serialPort.clear();
		serialPort.close();
	}
	else {
		if (serialPort.open(QIODevice::ReadWrite))
		{
			openFlag = true;
			//send
			connect(&serialPort, &QIODevice::readyRead, this, &Serial::getData);
		}
		else
			sendData("Serial open false !");
	}
}

void Serial::getData()
{
    while (serialPort.waitForReadyRead(WAITTIME))
	{
		data += serialPort.readAll();
	}
    sendData(data);
    data.clear();
}

void Serial::setData()
{
    serialPort.setPortName(ui->portComboBox->currentText());

	int speed = ui->speedComboBox->currentText().toInt();
	serialPort.setBaudRate(speed);

	int databits = ui->dataComboBox->currentText().toInt();
	switch (databits) {
	case 8:serialPort.setDataBits(QSerialPort::Data8); break;
	case 7:serialPort.setDataBits(QSerialPort::Data7); break;
	}

	QString parity = ui->parityComboBox->currentText();
	if ("none" == parity) serialPort.setParity(QSerialPort::NoParity);
	if ("odd"  == parity) serialPort.setParity(QSerialPort::OddParity);
	if ("even" == parity) serialPort.setParity(QSerialPort::EvenParity);

	QString stopbits = ui->stopbitsComboBox->currentText();
	if ("1"   == stopbits) serialPort.setStopBits(QSerialPort::OneStop);
	if ("1.5" == stopbits) serialPort.setStopBits(QSerialPort::OneAndHalfStop);
	if ("2"   == stopbits) serialPort.setStopBits(QSerialPort::TwoStop);
	createSerial();
}
