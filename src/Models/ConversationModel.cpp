#include "ConversationModel.h"


ConversationModel::ConversationModel(IMainWindow &iMainWindow, QObject *parent)
    : QAbstractListModel(parent),iMainWindow(iMainWindow){}

int ConversationModel::rowCount(const QModelIndex &parent) const {
    if (parent.isValid())
        return 0;
    return messageList.count();
}



QVariant ConversationModel::data(const QModelIndex &index, int role) const {

    if (!index.isValid())
        return QVariant();

    const structData &data = messageList.at(index.row());

    switch (role) {

    case dialogIdRole:
        return data.dialogId;

    case userIdRole:
        return data.userId;

    case incommingDataRole:
        return data.incommingData;

    case timestampRole:
        return data.timestamp;

    case rightSideRole:
        return data.rightSide;

    default:
        return QVariant();
    }
}

void ConversationModel::addToModel(const structData &message)
{
    if(checkDialog(message.dialogId, message.userId))
    {
        beginInsertRows(QModelIndex(), 0, 0);
        messageList.push_front(message);
        endInsertRows();
    }

}


void ConversationModel::resetModel()
{
    beginResetModel();
    messageList.clear();
    endResetModel();
}

bool ConversationModel::checkDialog(const QString &dialogId,
                                    const QString &recipientId)
{
    if(dialogId==iMainWindow.getCurrentDialogId())
    {
        return true;
    }
    else if(recipientId == iMainWindow.getCurrentUserId() ||
            recipientId == iMainWindow.getRecipientId())
    {
        return true;
    }
    return false;
}



QHash<int, QByteArray> ConversationModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[dialogIdRole] = "dialogId";
    roles[userIdRole] = "userId";
    roles[incommingDataRole] = "incommingData";
    roles[timestampRole] = "timestamp";
    roles[rightSideRole] = "rightSide";
    return roles;
}
