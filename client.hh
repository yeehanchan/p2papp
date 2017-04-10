#ifndef P2PAPP_CLIENT_HH
#define P2PAPP_CLIENT_HH


#include <QAbstractSocket>
#include <QHash>
#include <QHostAddress>
#include <QObject>



class Client : public QObject
{
    Q_OBJECT

public:
    Client();
    void setNickName(int port);
    QString nickName();
//    bool isPeer(const QString sender, const QHostAddress addr);
    bool isPeer(const QString sender, const quint16 port);
//    void addPeer(const QString sender, const QHostAddress addr);
    void addPeer(const QString sender, const quint16 port);
    void getPeers(QHash<QString, quint16> &peers);

    signals:
    void readyJoin();


private:

    QString nickname;
    //keep username and port, only for local testing
    QHash<QString, quint16> peers;
//    QHash<QString, QHostAddress> peers;

};



#endif // P2PAPP_CLIENT_HH
