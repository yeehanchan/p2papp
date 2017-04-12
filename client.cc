#include <QtNetwork>

#include "client.hh"

Client::Client() {
    seqno = 0;
}

bool Client::isPeer(const QString &sender, const quint16 port) {
    if(peers.contains(sender) && peers[sender] == port){
        return true;
    }
    return false;
}



void Client::addPeer(const QString &sender, const quint16 port) {
    peers.insert(sender,port);
}



void Client::getPeers(QHash<QString, quint16> &peers) {
    peers = this->peers;
}



void Client::setNickName(quint16 port) {
    port = port;
    nickname =  QHostInfo::localHostName()+ ":" +
            QString::number(port) + "@" + QString::number(qrand());
}



QString Client::nickName() {
    return nickname;
}


void Client::addMessageToHistory(const QString &origin, const quint16 seqno, const QString &message) {

    QMap<QString,QVariant>innermap = messages[origin].toMap();
    QVariant m(message);
    innermap.insert(QString::number(seqno),m);
    qDebug() << "insert "<<message << " with key "<<seqno;
    QVariant v(innermap);
    messages[origin] = innermap;

    emit rumorReady(origin);
}



QString Client::getMessage(const QString &origin, const quint16 seqno) {
    QMap<QString, QVariant> innermap = messages[origin].toMap();
    return innermap[QString::number(seqno)].toString();
}



void Client::updateVectorClock(const QString &origin) {

    vectorclock[origin]++;
}



quint16 Client::getClockByOrigin(const QString &origin) {
    return vectorclock[origin];
}



bool Client::isSelf(QString &origin) {
    return (origin==nickname) ? true : false;
}

