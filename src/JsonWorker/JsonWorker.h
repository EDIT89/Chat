#ifndef JSONWORKER_H
#define JSONWORKER_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonArray>
#include <memory>
#include <QVariantMap>
#include <QDebug>
#include <QDateTime>


#include "Structures/Structures.h"
#include "Pages/IMainWindow.h"

class JsonWorker: public QObject
{
public:
    JsonWorker(IMainWindow &iMainWindow);
    structDialog getNewUserStatus(const QJsonDocument &jsonDocument);
    QList<structUsers> getUserListFromJsonDocument(const QJsonDocument &jsonDocument);
    QList<structDialog> getDialogListFromJsonDocument(const QJsonDocument &jsonDocument);
    QJsonDocument createJsonMessage(const QString &dialogId,
                                    const QString &currentUserId,
                                    const QString &recipientId,
                                    const QString &message);

    structData getStructData(const QJsonDocument &jsonMessageDocument, const QString currentUserId);

    QList<structData> getMessagesHistoryList(const QJsonDocument &jsonDocument,
                                             const QString &currentUserId);

    bool checkCurrentDialog(const QString &dialogId);


public slots:

private:
IMainWindow &iMainWindow;


};

#endif // JSONWORKER_H
