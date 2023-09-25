#include "SearchUsersModel.h"

SearchUsersModel::SearchUsersModel(QObject *parent)
    : QAbstractListModel(parent){}



int SearchUsersModel::rowCount(const QModelIndex &parent) const {
  if (parent.isValid())
    return 0;
  return userNamesList.count();
}



QVariant SearchUsersModel::data(const QModelIndex &index, int role) const {

  if (!index.isValid())
  return QVariant();

  const structUsers &user = userNamesList.at(index.row());

  //structure data distribution by model roles
  switch (role) {
  case userIdRole:
    return user.userId;

  case loginRole:
    return user.login;

  default:
  return QVariant();
  }
}


//adding users to the model
void SearchUsersModel::addToModel(const structUsers &user)
{
  userNamesList.push_back(user);
  qDebug()<<"model"<<rowCount();
}

void SearchUsersModel::resetModel()
{
    beginResetModel();
    userNamesList.clear();
    endResetModel();
}

//naming roles in QML
QHash<int, QByteArray> SearchUsersModel::roleNames() const {
  QHash<int, QByteArray> roles;
  roles[userIdRole] = "userId";
  roles[loginRole] = "login";
  return roles;
}
