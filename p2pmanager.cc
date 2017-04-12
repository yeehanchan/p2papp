#include <QtNetwork>

#include "client.hh"
#include "p2pmanager.hh"

static const qint32 RumorTimeOut = 2000;

P2PManager::P2PManager(Client *client) : QObject(client)
{
    this->client = client;
    this->rmtimer = new QTimer(this);

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

    connect(client, SIGNAL(rumorReady(QString)), this, SLOT(rumorMongering(QString)));
    connect(&broadcastSocket, SIGNAL(readyRead()), this, SLOT(readBroadcastMessage()));
    connect(rmtimer, SIGNAL(timeout()), this, SLOT(rumorTimeOutHandler()));

    broadcastSocket.bind();
    client->setNickName(broadcastSocket.localPort());

    sendBroadcastGreeting();

}

void P2PManager::setMessageKeys() {
    messageKeys << "ChatText" << "Greeting" << "GreetingReply" << "Origin" << "SeqNum" << "Want";
}


void P2PManager::sendBroadcastGreeting() {


    QMap<QString, QVariant> map;
    map.insert(messageKeys[GREETING], "hello world");
    map.insert(messageKeys[ORIGIN], client->nickName());

    bool validBroadcastAddresses = true;
//    foreach (QHostAddress address, broadcastAddresses){
//
//        for(int port = broadcastSocket.myPortMin; port < broadcastSocket.myPortMax; port++){
//            if(port != broadcastSocket.localPort()) {
//                if (broadcastSocket.sendMessage(map, QHostAddress::LocalHost, port) == -1) {
//                    validBroadcastAddresses = false;
//                    break;
//                }
//            }
//        }
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
    map.insert(messageKeys[SEQNUM], client->seqno);

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

    QString origin;
    quint16 seqnum;
    QString message;
    quint16 senderwant;
    quint16 iwant;
    QString key;
    for(int i = 0; i < map.size(); i++) {
        key = map.keys()[i];

        if (key == messageKeys[GREETING]) {
            mtype = GREETING;
        } else if (key == messageKeys[GREETING_REPLY]) {
            mtype = GREETING_REPLY;
        } else if (key == messageKeys[CHATTEXT]) {
            mtype = CHATTEXT;
            message = map[key].toString();
        } else if (key == messageKeys[ORIGIN]) {
            origin = map[key].toString();
        } else if (key == messageKeys[SEQNUM]) {
            seqnum = map[key].toInt();
        } else if(key == messageKeys[WANT]){
            mtype = WANT;
        }
    }


    if(mtype == GREETING){
        qDebug() << "received greeting from: " << senderPort;

        if(!client->isPeer(origin,senderPort)){
            client->addPeer(origin, senderPort);
            emit newParticipant(origin);


        }

        // send greeting back
        QMap<QString, QVariant> reply;
        reply.insert(messageKeys[GREETING_REPLY],"hello peer");
        reply.insert(messageKeys[ORIGIN], client->nickName());
        broadcastSocket.sendMessage(reply, senderIp, senderPort);
    }

    if(mtype == GREETING_REPLY){
        qDebug() << "received greeting reply from: " << senderPort;

        if(!client->isPeer(origin,senderPort)){
            client->addPeer(origin, senderPort);
            emit newParticipant(origin);
        }
    }

    if(mtype == CHATTEXT){
        qDebug() << "rev a chattext message:" << message <<" from " << origin;

        client->addMessageToHistory(origin,seqnum,message);
        if(seqnum == client->getClockByOrigin(origin) + 1){
            client->updateVectorClock(origin);
            emit newMessage(origin, message);
        }

        sendStatus(origin, senderIp, senderPort);

    }

    if(mtype == WANT){

        origin = map[messageKeys[WANT]].toMap().keys()[0];
        senderwant = map[messageKeys[WANT]].toMap().values()[0].toInt();
        iwant = client->getClockByOrigin(origin)+1;

        qDebug() << "sender want "<<senderwant << " from "<<origin;

        if(senderwant > iwant){
            qDebug() << "sender knows" << senderwant-1 <<" i knows "<<iwant-1;
            sendStatus(origin, senderIp, senderPort);
        }
        else if(senderwant < iwant){
            for(int i = senderwant; i < iwant; i++){
                qDebug() << "send " << origin << "'s rumors " << i << ":"<< client->getMessage(origin,i) << " to " << senderPort;
                sendMessageToHost(origin,i,senderIp,senderPort);
            }

        }else{
            qDebug() << "sender and i know the same thing";
        }
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

bool P2PManager::sendStatus(const QString &origin, QHostAddress &addr, quint16 &port) {
    QMap<QString, QVariant> map;
    QMap<QString, QVariant> nested;
    quint16 want = client->getClockByOrigin(origin)+1;
    nested.insert(origin, QVariant(want));
    QVariant v(nested);
    map.insert(messageKeys[WANT], v);

    if(!broadcastSocket.sendMessage(map,addr,port)){
        qDebug() << "send status failed";
        return false;
    };

    return true;
}

bool P2PManager::sendMessageToHost(const QString &origin, const quint16 seqno, QHostAddress &addr, quint16 &port) {
    QMap<QString, QVariant> map;
    map.insert(messageKeys[CHATTEXT], client->getMessage(origin, seqno));
    map.insert(messageKeys[ORIGIN], origin);
    map.insert(messageKeys[SEQNUM], seqno);

    if(broadcastSocket.sendMessage(map, addr, port) == -1){
        return false;
    }

    return true;

}

quint16 P2PManager::randNeighbor() {
    quint16 rd;
    quint16 left = qMax(broadcastSocket.myPortMin, broadcastSocket.localPort()-1);
    quint16 right = qMin(broadcastSocket.localPort()+1, broadcastSocket.myPortMax);

    while(1){
        rd = left + (rand() % (int)(right - left + 1));
        if(rd != broadcastSocket.localPort()){
            break;
        }
    }

    return rd;


}




void P2PManager::rumorMongering(const QString &origin) {

    quint16 nport = randNeighbor();
    QHostAddress host = QHostAddress::LocalHost;
    qDebug() << "start rumormongering to neighbor: " << nport;

    sendStatus(origin,host,nport);

    rmtimer->start(RumorTimeOut);
}

void P2PManager::rumorTimeOutHandler() {
    rmtimer->stop();
    qDebug() << "TIMEOUT: peer not responding or synced.";
    //either stop or pick another machine
}