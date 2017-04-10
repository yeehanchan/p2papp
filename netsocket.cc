//
// Created by Yeehan Chan on 4/7/17.
//


#include <unistd.h>
#include <QMap>
#include <QDebug>
#include <QByteArray>
#include "netsocket.hh"


NetSocket::NetSocket()
{
    // Pick a range of four UDP ports to try to allocate by default,
    // computed based on my Unix user ID.
    // This makes it trivial for up to four P2Papp instances per user
    // to find each other on the same host,
    // barring UDP port conflicts with other applications
    // (which are quite possible).
    // We use the range from 32768 to 49153 for this purpose.
    myPortMin = 32768 + (getuid() % 4096)*4;
    myPortMax = myPortMin + 5;
}


bool NetSocket::bind()
{
    // Try to bind to each of the range myPortMin..myPortMax in turn.
    for (int p = myPortMin; p <= myPortMax; p++) {
        if (QUdpSocket::bind(QHostAddress::Any, p)) {
            qDebug() << "bound to UDP port " << p;
            return true;
        }
    }

    qDebug() << "Oops, no ports in my default range " << myPortMin
             << "-" << myPortMax << " available";
    return false;
}


// serialize message map into bytearray and send it
bool NetSocket::sendMessage(const QMap<QString, QVariant> &map, QHostAddress addr, quint16 port) {
    QByteArray datagram;
    QDataStream outStream(&datagram, QIODevice::WriteOnly);
    outStream << map;


    if(writeDatagram(datagram, addr, port) == -1){
        qDebug() << "send fail ";
        return false;
    }

    return true;
}


// receive datagram and deserialize it
bool NetSocket::revMessage(QMap<QString, QVariant> &map, QHostAddress &senderIp, quint16 &senderPort) {

    QByteArray datagram;

    datagram.resize(pendingDatagramSize());
    if(readDatagram(datagram.data(), datagram.size(), &senderIp, &senderPort) == -1){
        qDebug() << "rev fail ";
        return false;
    }

    QDataStream inStream(&datagram, QIODevice::ReadOnly);
    inStream >> map;

    return true;
}