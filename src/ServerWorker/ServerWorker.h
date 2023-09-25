#ifndef SERVERWORKER_H
#define SERVERWORKER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <memory>
#include <QDataStream>
#include <iostream>
#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonArray>


#include "Structures\Structures.h"
#include "JsonWorker\JsonWorker.h"
#include "Pages\IMainWindow.h"



class ServerWorker: public QTcpServer
{
     Q_OBJECT
public:
    ServerWorker(IMainWindow &iMainWindow);
    ~ServerWorker();
    bool init();
    void connectToHost();
    void createOnlineStatus(const QString &authorId);
    void createOfflineStatus(const QString &authorId);
    void getUsersList(const QString &authorId);
    void getMessagesHistory(const QString &authorId,
                            const QString &dialogId,
                            const QString &recipientId);
    void getDialogList(const QString &userId);
    void addNewUser(const QVariant &login, const QVariant &password);

public slots:
    void slotReadyRead();
    void checkUser(const QVariant &login, const QVariant &password);
    void slotSendMessage(const QVariant &dialogId,
                         const QVariant &currentUserId,
                         const QVariant &recipientId,
                         const QVariant &message);

signals:
    void signalChangeUserStatus(const QJsonDocument &jsonDocument);
    void signalDialogList(const QJsonDocument &jsonDocument);
    void signalSignUpError();
    void signalShowLoginPage();
    void signalEnterSuccess(const QString &userId);
    void signalUserNamesList(const QJsonDocument &jsonDocument);
    void signalIncommingMessage(const QJsonDocument &jsonDocument);
    void signalMessagesHistory(const QJsonDocument &jsonDocument);


private:

    QTcpSocket *socket{nullptr};
    QByteArray dataArray;
    QJsonDocument jsonDocument;
    QJsonParseError jsonError;
    IMainWindow &iMainWindow;
    std::shared_ptr<JsonWorker> jsonWorker{nullptr};

};

#endif // SERVERWORKER_H
