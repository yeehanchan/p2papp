#include <QtNetwork>

#include "client.hh"

Client::Client() {}

bool Client::isPeer(const QString sender, const quint16 port) {
    if(peers.contains(sender) && peers[sender] == port){
        return true;
    }
    return false;
}

void Client::addPeer(const QString sender, const quint16 port) {
    peers.insert(sender,port);
}

void Client::getPeers(QHash<QString, quint16> &peers) {
    qDebug() << "peers " << this->peers;
    peers = this->peers;
}

void Client::setNickName(int port) {
    nickname = "localhost:" + QString::number(port);
}

QString Client::nickName() {
    return nickname;
}