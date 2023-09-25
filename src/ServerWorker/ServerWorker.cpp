#include "ServerWorker.h"

ServerWorker::ServerWorker(IMainWindow &iMainWindow) : iMainWindow(iMainWindow){}

ServerWorker::~ServerWorker()
{
    this->createOfflineStatus(iMainWindow.getCurrentUserId());
    std::cerr<<"~ServerWorker()";
}

bool ServerWorker::init()
{
    if (socket == nullptr)
    {
        socket = new QTcpSocket(this);
    }

    if (socket == nullptr)
        return false;


    connect(socket, SIGNAL(readyRead()), this, SLOT(slotReadyRead()));
    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);

    connectToHost();

    return true;
}



void ServerWorker::slotReadyRead()
{
    QByteArray dataArray = socket->readAll();

    qDebug()<<"socket->readAll() "<<socket->socketDescriptor();

    jsonDocument = QJsonDocument::fromBinaryData(dataArray);

    if(jsonDocument.isObject() && !jsonDocument.isEmpty())
    {
        if(jsonDocument.object().value("result").toString() == "changeUserStatus")
        {
            emit signalChangeUserStatus(jsonDocument);
            qDebug()<<jsonDocument;
        }
        if(jsonDocument.object().value("result").toString() == "dialogList")
        {
            emit signalDialogList(jsonDocument);
        }

        if (jsonDocument.object().value("result").toString() == "addNewUser" &&
                jsonDocument.object().value("status").toString() == "true")
        {
           emit signalShowLoginPage();
        }
        else
        {
           emit signalSignUpError();
        }

        if (jsonDocument.object().value("result").toString() == "checkUser" &&
                jsonDocument.object().value("status").toString() == "true")
        {
            emit signalEnterSuccess(jsonDocument.object().
                                    value("currentUserId").toString());
        }

        if(jsonDocument.object().value("result").toString() == "userNamesList")
        {
            emit signalUserNamesList(jsonDocument);
        }

        if(jsonDocument.object().value("result").toString() == "incommingMessage")
        {
            emit signalIncommingMessage(jsonDocument);
        }

        if(jsonDocument.object().value("result").toString() == "messagesHistory")
        {
            emit signalMessagesHistory(jsonDocument);
        }
    }
    else
    {
        std::cerr<<"jsonDocument is empty or not object";
    }
}



void ServerWorker::connectToHost()
{
    socket->connectToHost("127.0.0.1", 5555);
    if(socket->isWritable())
    std::cout<<"Connected!"<<std::endl;
    qDebug()<<"socketDescriptor"<<socketDescriptor();
}

void ServerWorker::createOnlineStatus(const QString &authorId)
{
    std::cerr<<"createOnlineStatus"<<std::endl;
    QJsonObject onlineStatus;
    onlineStatus.insert("query", "createUserStatus");
    onlineStatus.insert("userStatus", "1");
    onlineStatus.insert("authorId", authorId);
    jsonDocument.setObject(onlineStatus);

    socket->write(jsonDocument.toBinaryData());
    socket->waitForBytesWritten(500);
}

void ServerWorker::createOfflineStatus(const QString &authorId)
{
    QJsonObject offlineStatus;
    offlineStatus.insert("query", "createUserStatus");
    offlineStatus.insert("userStatus", "0");
    offlineStatus.insert("authorId", authorId);
    jsonDocument.setObject(offlineStatus);

    socket->write(jsonDocument.toBinaryData());
    socket->waitForBytesWritten(500);
}



void ServerWorker::getUsersList(const QString &authorId)
{
    QJsonObject userNamesList;
    userNamesList.insert("query", "usersList");
    userNamesList.insert("authorId", authorId);
    jsonDocument.setObject(userNamesList);

    socket->write(jsonDocument.toBinaryData());
    socket->waitForBytesWritten(500);
}



void ServerWorker::getMessagesHistory(const QString &authorId,
                                      const QString &dialogId,
                                      const QString &recipientId)
{
    QJsonObject query;
    query.insert("query", "getMessagesHistory");//query
    query.insert("authorId", authorId);
    query.insert("dialogId", dialogId);
    query.insert("recipientId", recipientId);//history, socket
    jsonDocument.setObject(query);

    socket->write(jsonDocument.toBinaryData());
    socket->waitForBytesWritten(500);

    qDebug()<<"getMessagesHistory dialogId "<< dialogId;
}

void ServerWorker::getDialogList(const QString &userId)
{
    QJsonObject query;
    query.insert("query", "dialogList");
    query.insert("authorId", userId);

    jsonDocument.setObject(query);

    socket->write(jsonDocument.toBinaryData());
    socket->waitForBytesWritten(500);

    qDebug()<<"getDialogList";
}



void ServerWorker::addNewUser(const QVariant &login, const QVariant &password)
{
    QJsonObject addNewUser;
    addNewUser.insert("query", "addNewUser");
    addNewUser.insert("login", login.toString());
    addNewUser.insert("password", password.toString());
    jsonDocument.setObject(addNewUser);

    socket->write(jsonDocument.toBinaryData());
    socket->waitForBytesWritten(500);
}



void ServerWorker::checkUser(const QVariant &login, const QVariant &password)
{
    QJsonObject checkUser;
    checkUser.insert("query", "checkUser");
    checkUser.insert("login", login.toString());
    checkUser.insert("password", password.toString());
    jsonDocument.setObject(checkUser);

    socket->write(jsonDocument.toBinaryData());
    socket->waitForBytesWritten(500);
}



void ServerWorker::slotSendMessage(const QVariant &dialogId,
                                   const QVariant &currentUserId,
                                   const QVariant &recipientId,
                                   const QVariant &message)
{
    jsonDocument = jsonWorker->createJsonMessage(dialogId.toString(),
                                                 currentUserId.toString(),
                                                 recipientId.toString(),
                                                 message.toString());

    qDebug()<<"ServerWorker::slotSendMessage"<<jsonDocument;

    socket->write(jsonDocument.toBinaryData());
    socket->waitForBytesWritten(500);
}
