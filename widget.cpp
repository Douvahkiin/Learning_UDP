#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    port = 12345;

    udpSocket = new QUdpSocket(this);
    udpSocket->bind(QHostAddress::Any, port); // Bind to port

    connect(udpSocket, &QUdpSocket::readyRead, this, &Widget::readPendingDatagrams);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::readPendingDatagrams()
{
    while (udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());
        QHostAddress senderAddress;
        quint16 senderPort;
        udpSocket->readDatagram(datagram.data(), datagram.size(), &senderAddress, &senderPort);
        // Handle received data here
        // UDP can't get the destination IP address!
        QString receivedData = QString::fromUtf8(datagram);
        ui->textEditRead->append(receivedData);
        // if (senderAddress.isInSubnet(QHostAddress::Broadcast, 24)) {
        // // Received a broadcast message
        // ui->textEditReadBroadcast->append(receivedData);
        // qDebug() << "Received a broadcast message from" << senderAddress.toString();
        // } else {
        // // Received a unicast message
        // ui->textEditReadUnicast->append(receivedData);
        // qDebug() << "Received a unicast message from" << senderAddress.toString();
        // }
    }
}

void Widget::broadcastData(const QByteArray &data)
{
    udpSocket->writeDatagram(data, QHostAddress::Broadcast, port); // Broadcast data to port
}

void Widget::on_broadcastButton_clicked()
{
    // QByteArray dataToSend = "Hello, UDP!";
    QByteArray dataToSend = ui->textEditSend->toPlainText().toUtf8();
    broadcastData(dataToSend);
}

void Widget::sendData(const QByteArray &data, QHostAddress targetAddress)
{
    udpSocket->writeDatagram(data, targetAddress, port); // Broadcast data to port
}

void Widget::on_sendButton_clicked()
{
    QHostAddress targetAddress;
    if (targetAddress.setAddress(ui->textEditIP->toPlainText())) {
        sendData(ui->textEditSend->toPlainText().toUtf8(), targetAddress);
    } else {
        return;
    }
}
