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
    void setNickName(quint16 port);
    QString nickName();
//    bool isPeer(const QString sender, const QHostAddress addr);
    bool isPeer(const QString &sender, const quint16 port);
//    void addPeer(const QString sender, const QHostAddress addr);
    void addPeer(const QString &sender, const quint16 port);
    void getPeers(QHash<QString, quint16> &peers);
    void addMessageToHistory(const QString &origin, quint16 seqno, const QString &message);
    QString getMessage(const QString &origin, const quint16 seqno);
    void updateVectorClock(const QString &origin);
    quint16 getClockByOrigin(const QString &origin);
    bool isSelf(QString &origin);

    quint16 seqno;

    signals:
    void rumorReady(const QString &origin);


private:

    QString nickname;
    //keep username and port, only for local testing
    QHash<QString, quint16> peers;
//    QHash<QString, QHostAddress> peers;
    QMap<QString, QVariant>messages;
    QMap<QString, quint16>vectorclock;
};



#endif // P2PAPP_CLIENT_HH
