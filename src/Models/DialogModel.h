#ifndef DIALOGMODEL_H
#define DIALOGMODEL_H


#include <QAbstractListModel>
#include <QDateTime>
#include <memory>

#include "ServerWorker/ServerWorker.h"
#include "Structures/Structures.h"

class DialogModel : public QAbstractListModel {
  Q_OBJECT

public:
  explicit DialogModel(QObject *parent = nullptr);

  enum Roles {
    dialogIdRole = Qt::UserRole + 1,
    dialogNameRole,
    userStatusRole,
    lastMessageRole,
    lastMessageTimeRole,
    userStatus
  };

  int rowCount(const QModelIndex &parent = QModelIndex()) const override;

  QVariant data(const QModelIndex &index,
                int role = Qt::DisplayRole) const override;

  void addDialogToModel(const structDialog &dialog);
  void updateUserStatus(const structDialog &_dialog);

  void updateLastMessage(const QString &_dialogId,
                         const QString &_lastMessage,
                         const QString &_lastMessageTime);
  void resetModel();

public slots:



protected:
  virtual QHash<int, QByteArray> roleNames() const override;

private:
  QList<structDialog> dialogList;
};


#endif // DIALOGMODEL_H
