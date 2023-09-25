#include "DialogModel.h"

DialogModel::DialogModel(QObject *parent)
    : QAbstractListModel(parent){}

int DialogModel::rowCount(const QModelIndex &parent) const {
    if (parent.isValid())
        return 0;
    return dialogList.count();
}

QVariant DialogModel::data(const QModelIndex &index, int role) const {

    if (!index.isValid())
        return QVariant();

    const structDialog &dialogs = dialogList.at(index.row());

    //structure data distribution by model roles
    switch (role) {
    case dialogIdRole:
        return dialogs.dialogId;

    case dialogNameRole:
        return dialogs.dialogName;

    case userStatusRole:
        return dialogs.userStatus;

    case lastMessageRole:
        return dialogs.lastMessage;

    case lastMessageTimeRole:
        return dialogs.lastMessageTime;

    case userStatus:
        return dialogs.userStatus;

    default:
        return QVariant();
    }
}

//adding dialogs to the model
void DialogModel::addDialogToModel(const structDialog &dialog)
{
    dialogList.push_front(dialog);
    qDebug()<<"model"<<rowCount();
}

void DialogModel::updateUserStatus(const structDialog &_dialog)
{
    int rowIndex = 0;
    for(auto &i:dialogList)
    {
        rowIndex+=1;
        if (i.dialogId == _dialog.dialogId)
        {
            qDebug()<<"rowIndex"<<rowIndex;
            qDebug()<<"_dialog.dialogId"<<_dialog.dialogId;
            qDebug()<<"_dialog.userStatus" <<_dialog.userStatus;
            dialogList[rowIndex-1].userStatus =  _dialog.userStatus;
            //i.userStatus = _dialog.userStatus;
            break;
        }
    }

    const QModelIndex startIndex = index(rowIndex-1, 0);
    const QModelIndex endIndex = index(rowIndex-1, 0);

    emit dataChanged(startIndex, endIndex, QVector<int>() << userStatusRole);

}

void DialogModel::updateLastMessage(const QString &_dialogId,
                                    const QString &_lastMessage,
                                    const QString &_lastMessageTime)
{
    for(auto &i:dialogList)
    {
        if (i.dialogId == _dialogId)
        {
            i.lastMessage = _lastMessage;
            i.lastMessageTime = _lastMessageTime;
        }
    }
}

void DialogModel::resetModel()
{
    beginResetModel();
    dialogList.clear();
    endResetModel();
}

//naming roles in QML
QHash<int, QByteArray> DialogModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[dialogIdRole] = "dialogId";
    roles[dialogNameRole] = "dialogName";
    roles[userStatusRole] = "userStatus";
    roles[lastMessageRole] = "lastMessage";
    roles[lastMessageTimeRole] = "lastMessageTime";
    roles[userStatus] = "userStatus";
    return roles;
}


