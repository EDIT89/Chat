#ifndef CONVERSATIONMODEL_H
#define CONVERSATIONMODEL_H

#include <QAbstractListModel>
#include <QDateTime>
#include <memory>
#include <QDebug>
#include <QMap>
#include <QMapIterator>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonParseError>

#include "Structures\Structures.h"
#include "Pages/IMainWindow.h"

class ConversationModel : public QAbstractListModel {
  Q_OBJECT

public:
  explicit ConversationModel(IMainWindow &iMainWindow,
                             QObject *parent = nullptr);

  enum Roles {
    dialogIdRole =  Qt::UserRole + 1,
    userIdRole,
    incommingDataRole,
    timestampRole,
    rightSideRole
  };

  int rowCount(const QModelIndex &parent = QModelIndex()) const override;

  QVariant data(const QModelIndex &index,
                int role = Qt::DisplayRole) const override;

  void addToModel(const structData &data);
  void resetModel();
  bool checkDialog(const QString &dialogId,
                   const QString &recipientId);

protected:
  virtual QHash<int, QByteArray> roleNames() const override;

private:
  IMainWindow &iMainWindow;
  QList<structData> messageList;
};

#endif // CONVERSATIONMODEL_H
