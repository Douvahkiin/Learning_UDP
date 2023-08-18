#ifndef WIDGET_H
#define WIDGET_H

#include <QUdpSocket>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;
    QUdpSocket *udpSocket;
    unsigned short port;

private slots:
    void readPendingDatagrams();
    void broadcastData(const QByteArray &data);
    void sendData(const QByteArray &data, QHostAddress targetAddress);
    void on_broadcastButton_clicked();
    void on_sendButton_clicked();
};
#endif // WIDGET_H
