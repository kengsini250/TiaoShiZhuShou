#include "../head/mainwindow.h"
#include "ui_mainwindow.h"

#include "../head/CRLF.hpp"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  ui->toolBox->removeItem(0);
  ui->toolBox->removeItem(0);
  tcpip = new TCPIP(this);
  ui->toolBox->addItem(tcpip,"TCP/IP");
  serial = new Serial(this);
  ui->toolBox->addItem(serial,"Serial");

  //main UI
  connect(ui->clearPushButton, &QAbstractButton::clicked, [this] {ui->outputTextBrowser->clear(); });
  connect(ui->actionExit, &QAction::triggered, this, &QMainWindow::close);

  //tcpip output
  connect(tcpip, &TCPIP::sendData, [this] (const QString& msg){
      ui->outputTextBrowser->append(msg);
      });
  //serial output
  connect(serial,&Serial::sendData,[this](const QString& msg){
      ui->outputTextBrowser->append(msg);
  });

  connect(ui->sendPushButton,&QAbstractButton::clicked,[this]{
      //Tcp IP
      QString msg = ui->inputLineEdit->text();
      if(tcpip->getMode() == Mode::SERVER){
          if(ui->CRCheck->isChecked()) tcpip->send(Mode::SERVER,msg+CR);
          else if(ui->LFCheck->isChecked()) tcpip->send(Mode::SERVER,msg+LF);
          else if(ui->LFCheck->isChecked()&&ui->CRCheck->isChecked()) tcpip->send(Mode::SERVER,msg+CRLF);
          else tcpip->send(Mode::SERVER,msg);
        }
      if(tcpip->getMode() == Mode::CLIENT){
          if(ui->CRCheck->isChecked()) tcpip->send(Mode::CLIENT,msg+CR);
          else if(ui->LFCheck->isChecked()) tcpip->send(Mode::CLIENT,msg+LF);
          else if(ui->LFCheck->isChecked()&&ui->CRCheck->isChecked()) tcpip->send(Mode::CLIENT,msg+CRLF);
          else tcpip->send(Mode::CLIENT,msg);
        }

        //Serial
      if (serial->openFlag == true) {
          if (ui->CRCheck->isChecked()) serial->send((msg + CR).toUtf8());
          else if (ui->LFCheck->isChecked()) serial->send((msg + LF).toUtf8());
          else if (ui->LFCheck->isChecked() && ui->CRCheck->isChecked()) serial->send((msg + CRLF).toUtf8());
          else serial->send(msg.toUtf8());
      }

      ui->inputLineEdit->clear();
    });
    
  //Serial
}

MainWindow::~MainWindow()
{
  delete ui;
  delete tcpip;
  delete serial;
}
