//
// Created by Yeehan Chan on 4/7/17.
//

#ifndef P2PAPP_NETSOCKET_HH
#define P2PAPP_NETSOCKET_HH

#include <QtNetwork>
#include <QUdpSocket>
#include <QDataStream>
#include <QMap>
#include <QString>
#include <QVariant>

class NetSocket : public QUdpSocket
{
    Q_OBJECT

public:

    NetSocket();

    // Bind this socket to a P2Papp-specific default port.
    bool bind();

    bool sendMessage(const QMap<QString, QVariant> &map, QHostAddress addr, quint16 port);
    bool revMessage(QMap<QString, QVariant> &map, QHostAddress &senderIp, quint16 &senderPort);


public:
    int myPortMin, myPortMax;

};





#endif //P2PAPP_NETSOCKET_HH
