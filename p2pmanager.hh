#ifndef P2PAPP_P2PMANAGER_HH
#define P2PAPP_P2PMANAGER_HH

#include <QByteArray>
#include <QList>
#include <QObject>
#include <QTimer>
#include <QUdpSocket>
#include <QTimer>
#include "netsocket.hh"




class Client;
class Connection;

class P2PManager : public QObject
{
    Q_OBJECT

public:


    enum MessageType {
        CHATTEXT = 0,
        GREETING,
        GREETING_REPLY,
        ORIGIN,
        SEQNUM,
        WANT
    };


    P2PManager(Client *client);

    QByteArray userName() const;

    void setMessageKeys();
    bool isLocalHostAddress(const QHostAddress &address);
    void sendBroadcastMessage(const QString &message);
    quint16 randNeighbor();
    bool sendStatus(const QString &origin, QHostAddress &addr, quint16 &port);
    bool sendMessageToHost(const QString &origin,const quint16 seqno, QHostAddress &addr, quint16 &port);

    signals:
        void newMessage(const QString &from, const QString &message);
        void newParticipant(const QString &username);
        void participantLeft(const QString &username);
        void rumorStop();

public slots:
    void rumorTimeOutHandler();
    void sendBroadcastGreeting();
    void readBroadcastMessage();
    void rumorMongering(const QString &origin);

private:
    void updateAddresses();
    void processDatagram(QMap<QString, QVariant> &map, QHostAddress &senderIp, quint16 &senderPort);

    Client *client;
    QList<QHostAddress> broadcastAddresses;
    QList<QHostAddress> ipAddresses;
    NetSocket broadcastSocket;
    QTimer broadcastTimer;
    QByteArray username;
    MessageType mtype;
    QList<QString> messageKeys;
    QTimer *rmtimer;
};

#endif