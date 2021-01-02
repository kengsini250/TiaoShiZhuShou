#ifndef SERIAL_H
#define SERIAL_H

#include <QWidget>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QByteArray>


QT_BEGIN_NAMESPACE
namespace Ui { class Serial; }
QT_END_NAMESPACE

class Serial : public QWidget
{
	Q_OBJECT
public:
	bool openFlag = false;
	Serial(QWidget* parent = nullptr);
	void send(const QByteArray& msg);
private:
	Ui::Serial* ui;

	QSerialPort serialPort;
    QSerialPortInfo info;
	QByteArray data;

	void createSerial();
private slots:
	void setData();
	void getData();

signals:
	void sendData(const QString& msg);
};

#endif
