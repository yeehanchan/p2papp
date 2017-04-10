#include <QtNetwork>

#include "client.hh"
#include "p2pmanager.hh"


P2PManager::P2PManager(Client *client) : QObject(client)
{
    this->client = client;

    QStringList envVariables;
    envVariables << "USERNAME.*" << "USER.*" << "USERDOMAIN.*"
                 << "HOSTNAME.*" << "DOMAINNAME.*";

    QStringList environment = QProcess::systemEnvironment();
    foreach (QString string, envVariables) {
        int index = environment.indexOf(QRegExp(string));
        if (index != -1) {
            QStringList stringList = environment.at(index).split('=');
            if (stringList.size() == 2) {
                username = stringList.at(1).toUtf8();
                break;
            }
        }
    }

    if (username.isEmpty())
#ifndef Q_OS_SYMBIAN
        username = "unknown";
#else
    username = "QtS60";
#endif

    setMessageKeys();

    updateAddresses();

    connect(&broadcastSocket, SIGNAL(readyRead()), this, SLOT(readBroadcastMessage()));

    broadcastSocket.bind();
    client->setNickName(broadcastSocket.localPort());

    sendBroadcastGreeting();

}

void P2PManager::setMessageKeys() {
    messageKeys << "ChatText" << "Greeting" << "GreetingReply" << "Origin" << "SeqNum";
}


void P2PManager::sendBroadcastGreeting() {


    QMap<QString, QVariant> map;
    map.insert(messageKeys[GREETING], "hello world");
    map.insert(messageKeys[ORIGIN], client->nickName());

    bool validBroadcastAddresses = true;
//    foreach (QHostAddress address, broadcastAddresses){
//
//        if (broadcastSocket.sendMessage(map, QHostAddress::LocalHost, port) == -1) {
//            validBroadcastAddresses = false;
//            break;
//        }
//
//    }


    // For local testing
    for(int port = broadcastSocket.myPortMin; port < broadcastSocket.myPortMax; port++){
        if(port != broadcastSocket.localPort()) {
            if (broadcastSocket.sendMessage(map, QHostAddress::LocalHost, port) == -1) {
                validBroadcastAddresses = false;
                break;
            }
        }
    }

    if (!validBroadcastAddresses)
        updateAddresses();

}

QByteArray P2PManager::userName() const
{
    return username;
}


bool P2PManager::isLocalHostAddress(const QHostAddress &address)
{
    foreach (QHostAddress localAddress, ipAddresses) {
        if (address == localAddress)
            return true;
    }
    return false;
}

void P2PManager::sendBroadcastMessage(const QString &message)
{


    QMap<QString, QVariant> map;
    map.insert(messageKeys[CHATTEXT], message);
    map.insert(messageKeys[ORIGIN], client->nickName());

    bool validBroadcastAddresses = true;
//    foreach (QHostAddress address, broadcastAddresses){
//
//        if (broadcastSocket.sendMessage(map, QHostAddress::LocalHost, port) == -1) {
//            validBroadcastAddresses = false;
//            break;
//        }
//
//    }


    // For local testing
    QHash<QString, quint16> peers;
    client->getPeers(peers);
    for(int i = 0; i < peers.size(); i++){
        int port = peers.values()[i];
        if(port != broadcastSocket.localPort()) {
            if (broadcastSocket.sendMessage(map, QHostAddress::LocalHost, port) == -1) {
                validBroadcastAddresses = false;
                break;
            }
        }
    }

    if (!validBroadcastAddresses)
        updateAddresses();

}



void P2PManager::readBroadcastMessage()
{

    while (broadcastSocket.hasPendingDatagrams()) {
        QMap<QString,QVariant> map;
        QHostAddress senderIp;
        quint16 senderPort;

        if (broadcastSocket.revMessage(map, senderIp, senderPort) == -1)
            continue;

        processDatagram(map, senderIp, senderPort);

    }

}


void P2PManager::processDatagram(QMap<QString, QVariant> &map, QHostAddress &senderIp, quint16 &senderPort) {

    QString sender;
    int seqnum;
    QString key;
    for(int i = 0; i < map.size(); i++) {
        key = map.keys()[i];

        if (key == messageKeys[GREETING]) {
            mtype = GREETING;
        } else if (key == messageKeys[GREETING_REPLY]) {
            mtype = GREETING_REPLY;
        } else if (key == messageKeys[CHATTEXT]) {
            mtype = CHATTEXT;
        } else if (key == messageKeys[ORIGIN]) {
            sender = map[key].toString();
        } else if (key == messageKeys[SEQNUM]) {
            seqnum = map[key].toInt();
        }
    }


    if(mtype == GREETING){
        qDebug() << "received greeting from: " << senderPort;

        if(!client->isPeer(sender,senderPort)){
            client->addPeer(sender, senderPort);
            emit newParticipant(sender);


        }

        QMap<QString, QVariant> reply;
        reply.insert(messageKeys[GREETING_REPLY],"hello peer");
        reply.insert(messageKeys[ORIGIN], client->nickName());
        broadcastSocket.sendMessage(reply, senderIp, senderPort);
    }

    if(mtype == GREETING_REPLY){
        qDebug() << "received greeting reply from: " << senderPort;

        client->addPeer(sender,senderPort);
        emit newParticipant(sender);
    }

    if(mtype == CHATTEXT){
        QString message = map[messageKeys[CHATTEXT]].toString();
        emit newMessage(sender, message);

    }

}

void P2PManager::updateAddresses()
{
    broadcastAddresses.clear();
    ipAddresses.clear();
    foreach (QNetworkInterface interface, QNetworkInterface::allInterfaces()) {
        foreach (QNetworkAddressEntry entry, interface.addressEntries()) {
            QHostAddress broadcastAddress = entry.broadcast();
            if (broadcastAddress != QHostAddress::Null && entry.ip() != QHostAddress::LocalHost) {
                broadcastAddresses << broadcastAddress;
                ipAddresses << entry.ip();
            }
        }
    }
}