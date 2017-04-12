//
// Created by Yeehan Chan on 4/7/17.
//

#include <QApplication>
#include <QDebug>
#include <QtGui>

#include "chatdialog.hh"

ChatDialog::ChatDialog()
{

    ui.setupUi(this);
    p2pmanager = new P2PManager(&client);

    // Register a callback on the textline's returnPressed signal
    // so that we can send the message entered by the user.
    connect(ui.textline, SIGNAL(returnPressed()), this, SLOT(gotReturnPressed()));
    connect(p2pmanager, SIGNAL(newMessage(QString,QString)), this, SLOT(appendMessage(QString,QString)));
    connect(p2pmanager, SIGNAL(newParticipant(QString)), this, SLOT(newParticipant(QString)));

    myNickName = client.nickName();
    newParticipant(myNickName);
    QTimer::singleShot(10 * 1000, this, SLOT(showInformation()));

}


void ChatDialog::appendMessage(const QString &from, const QString &message)
{
    if (from.isEmpty() || message.isEmpty())
        return;

    QTextTableFormat tableFormat;
    QTextCursor cursor(ui.textview->textCursor());
    cursor.movePosition(QTextCursor::End);
    QTextTable *table = cursor.insertTable(1, 2, tableFormat);
    table->cellAt(0, 0).firstCursorPosition().insertText('<' + from + "> ");
    table->cellAt(0, 1).firstCursorPosition().insertText(message);
    QScrollBar *bar = ui.textview->verticalScrollBar();
    bar->setValue(bar->maximum());
}






void ChatDialog::gotReturnPressed()
{
    // Initially, just echo the string locally.
    // Insert some networking code here...
    qDebug() << "FIX: send message to other peers: " << ui.textline->text();
    QString text = ui.textline->text();
    if (text.isEmpty())
        return;

    if (text.startsWith(QChar('/'))) {
        QColor color = ui.textview->textColor();
        ui.textview->setTextColor(Qt::red);
        ui.textview->append(tr("! Unknown command: %1").arg(text.left(text.indexOf(' '))));
        ui.textview->setTextColor(color);

    } else {
        client.seqno++;
        client.addMessageToHistory(client.nickName(), client.seqno, text);
        client.updateVectorClock(client.nickName());
        p2pmanager->sendBroadcastMessage(text);
        appendMessage(myNickName, text);
    }

    ui.textline->clear();
}

void ChatDialog::newParticipant(const QString &nick)
{
    if (nick.isEmpty())
        return;

    QColor color = ui.textview->textColor();
    ui.textview->setTextColor(Qt::gray);
    ui.textview->append(tr("* %1 has joined").arg(nick));
    ui.textview->setTextColor(color);
    ui.userlist->addItem(nick);
}


void ChatDialog::showInformation()
{

}


void ChatDialog::participantLeft(const QString &nick)
{
    if (nick.isEmpty())
        return;

    QList<QListWidgetItem *> items = ui.userlist->findItems(nick,
                                                           Qt::MatchExactly);
    if (items.isEmpty())
        return;

    delete items.at(0);
    QColor color = ui.textview->textColor();
    ui.textview->setTextColor(Qt::gray);
    ui.textview->append(tr("* %1 has left").arg(nick));
    ui.textview->setTextColor(color);
}
