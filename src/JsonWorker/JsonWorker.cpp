#include "JsonWorker.h"

JsonWorker::JsonWorker(IMainWindow &iMainWindow)
    : iMainWindow(iMainWindow) {}

structDialog JsonWorker::getNewUserStatus(const QJsonDocument &jsonDocument)
{
    structDialog newUserStatus;
    if(!jsonDocument.isEmpty())
    {
        newUserStatus.dialogId = jsonDocument.object().value("dialogId").toString();
        if(jsonDocument.object().value("userStatus").toString() == "1")
        {
            newUserStatus.userStatus = true;
        }
        else
        {
            newUserStatus.userStatus = false;
        }

    }
    return newUserStatus;
}

//
QList<structUsers> JsonWorker::getUserListFromJsonDocument(const QJsonDocument &jsonDocument)
{
    QList<structUsers> userList;
    if(!jsonDocument.isEmpty() && jsonDocument.object().value("data").isObject())
    {
        QJsonObject data = jsonDocument.object().value("data").toObject();
        structUsers users;
        QJsonObject::Iterator i;
        for(i = data.begin(); i != data.end(); ++i)
        {
            users.userId = i.key();
            users.login = i.value().toString();
            userList.push_back(users);
        }
    }
    return userList;
}

QList<structDialog> JsonWorker::getDialogListFromJsonDocument(const QJsonDocument &jsonDocument)
{
    QList<structDialog> dialogList;
    structDialog dialogStructure;
    QJsonArray jsonArray;

    if(!jsonDocument.isEmpty())
    {
        jsonArray = jsonDocument.object().value("dialogArray").toArray();

        if(!jsonArray.isEmpty())
        {
            for(int i = 0; i < jsonArray.count(); i++)
            {
                QString dateTime =
                        QDateTime::fromString(jsonArray.at(i).toObject().value("timestamp").toString(),
                                              "dd.MM.yyyy hh:mm:ss.zzz").toString("hh:mm");
                dialogStructure.dialogId = jsonArray.at(i).toObject().value("dialogId").toString();
                dialogStructure.dialogName = jsonArray.at(i).toObject().value("dialogName").toString();
                dialogStructure.lastMessage = jsonArray.at(i).toObject().value("message").toString();
                dialogStructure.lastMessageTime = dateTime;
                if(jsonArray.at(i).toObject().value("userStatus").toString() == "1")
                {
                    dialogStructure.userStatus = true;
                }
                else
                {
                    dialogStructure.userStatus = false;
                }
                dialogList.push_back(dialogStructure);
            }
        }
    }
    return dialogList;
}



//converting the user's message to json
QJsonDocument JsonWorker::createJsonMessage(const QString &dialogId,
                                            const QString &currentUserId,
                                            const QString &recipientId,
                                            const QString &message)
{
    QJsonDocument jsonMessageDocument;
    QJsonObject jsonMessage;
    jsonMessage.insert("query", "sendMessage");
    jsonMessage.insert("dialogId", dialogId);
    jsonMessage.insert("authorId", currentUserId);
    jsonMessage.insert("recipientId", recipientId);
    jsonMessage.insert("message", message);
    jsonMessageDocument.setObject(jsonMessage);

    return  jsonMessageDocument;
}


//unpacking the message into a data structure
structData JsonWorker::getStructData(const QJsonDocument &jsonMessageDocument,
                                     const QString currentUserId)
{
    structData messageData;
    QString dateTime =
            QDateTime::fromString(jsonMessageDocument.object().value("timestamp").toString(),
                                  "dd.MM.yyyy hh:mm:ss.zzz").toString("hh:mm");
    qDebug()<<"dateTime"<<dateTime;
    messageData.dialogId = jsonMessageDocument.object().value("dialogId").toString();
    messageData.userId = jsonMessageDocument.object().value("authorId").toString();
    messageData.incommingData = jsonMessageDocument.object().value("message").toString();
    messageData.timestamp = dateTime;
    if(jsonMessageDocument.object().value("authorId").toString() == currentUserId)
    {
        messageData.rightSide = true;
    }
    else
    {
        messageData.rightSide = false;
    }

    return messageData;
}


//unpacking the messagesArray into a QList
QList<structData> JsonWorker::getMessagesHistoryList(const QJsonDocument &jsonDocument,
                                                     const QString &currentUserId)
{
    QList<structData> dataList;
    structData messageData;
    QJsonArray jsonArray;

    if(!jsonDocument.isEmpty())
    {
        jsonArray = jsonDocument.object().value("messagesArray").toArray();

        if(!jsonArray.isEmpty())
        {
            for(int i = 0; i < jsonArray.count(); i++)
            {
                QString dateTime =
                        QDateTime::fromString(jsonArray.at(i).toObject().value("timestamp").toString(),
                                              "dd.MM.yyyy hh:mm:ss.zzz").toString("hh:mm");
                messageData.dialogId = jsonArray.at(i).toObject().value("dialogId").toString();
                messageData.userId = jsonArray.at(i).toObject().value("userId").toString();
                messageData.incommingData = jsonArray.at(i).toObject().value("message").toString();
                messageData.timestamp = dateTime;
                if(jsonArray.at(i).toObject().value("userId").toString() == currentUserId)
                {
                    messageData.rightSide = true;
                }
                else
                {
                    messageData.rightSide = false;
                }
                dataList.push_back(messageData);
            }
        }
    }
    return dataList;
}

bool JsonWorker::checkCurrentDialog(const QString &dialogId)
{
    if(dialogId == iMainWindow.getCurrentDialogId())
        return true;
    return false;
}







