//
// Created by Yeehan Chan on 4/7/17.
//

#ifndef P2PAPP_CHATDIALOG_HH
#define P2PAPP_CHATDIALOG_HH

#include <QDialog>
#include <QTextEdit>
#include <QLineEdit>
#include <QListWidget>

#include "ui_chatdialog.h"
#include "client.hh"
#include "p2pmanager.hh"

class ChatDialog : public QDialog
{
    Q_OBJECT

public:
    ChatDialog();


public slots:
    void appendMessage(const QString &from, const QString &message);


private slots:
    void gotReturnPressed();
    void newParticipant(const QString &nick);
    void participantLeft(const QString &nick);
    void showInformation();


private:
    Ui::ChatDialog ui;
    Client client;
    P2PManager *p2pmanager;
    QString myNickName;
};




#endif //WORK_CHATDIALOG_HH


