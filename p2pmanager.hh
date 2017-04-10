#ifndef P2PAPP_P2PMANAGER_HH
#define P2PAPP_P2PMANAGER_HH

#include <QByteArray>
#include <QList>
#include <QObject>
#include <QTimer>
#include <QUdpSocket>
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
        SEQNUM
    };


    P2PManager(Client *client);

    QByteArray userName() const;

    void setMessageKeys();
    bool isLocalHostAddress(const QHostAddress &address);
    void sendBroadcastMessage(const QString &message);

    signals:
        void newMessage(const QString &from, const QString &message);
        void newParticipant(const QString &username);
        void participantLeft(const QString &username);

private slots:
    void sendBroadcastGreeting();
    void readBroadcastMessage();

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
};

#endif