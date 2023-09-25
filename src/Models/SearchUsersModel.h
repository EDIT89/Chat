#ifndef SEARCHUSERSMODEL_H
#define SEARCHUSERSMODEL_H


#include <QAbstractListModel>
#include <QDateTime>
#include <memory>

#include "ServerWorker/ServerWorker.h"
#include "Structures/Structures.h"

class SearchUsersModel : public QAbstractListModel {
  Q_OBJECT

public:
  explicit SearchUsersModel(QObject *parent = nullptr);

  enum Roles {
    userIdRole = Qt::UserRole + 1,
    loginRole
  };

  int rowCount(const QModelIndex &parent = QModelIndex()) const override;

  QVariant data(const QModelIndex &index,
                int role = Qt::DisplayRole) const override;

  void addToModel(const structUsers &user);
  void resetModel();

public slots:



protected:
  virtual QHash<int, QByteArray> roleNames() const override;

private:
  QList<structUsers> userNamesList;
};
#endif // SEARCHUSERSMODEL_H
