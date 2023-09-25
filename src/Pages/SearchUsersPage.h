#ifndef SEARCHUSERSPAGE_H
#define SEARCHUSERSPAGE_H


#include <QDebug>
#include <QQmlComponent>
#include <QVariant>
#include <iostream>
#include <qcryptographichash.h>
#include <memory>
#include <QMessageBox>

// Interfaces
#include "IMainWindow.h"
#include "Engine/IQmlEngine.h"
#include "ServerWorker/ServerWorker.h"
#include "Models/SearchUsersModel.h"
#include "JsonWorker/JsonWorker.h"

#include "PagesModal.h"

#define SEARCH_USERS_PAGE_QML_PATH "qrc:/Qml/Pages/SearchUsersPage.qml"

class SearchUsersPage : public QObject {
  Q_OBJECT

public:
  explicit SearchUsersPage(PagesTypes type, IMainWindow &iMainWindow,
                     std::shared_ptr<IQmlEngine> iengine,
                     std::shared_ptr<ServerWorker> &serverWorker,
                     QObject *parent = nullptr);
  ~SearchUsersPage();

  bool init();

  QObject *getComponent();

private:
  bool initSearchUsersModel();
  PagesTypes type;
  IMainWindow &iMainWindow;
  std::shared_ptr<IQmlEngine> iengine{nullptr};
  std::shared_ptr<ServerWorker> serverWorker{nullptr};
  std::shared_ptr<SearchUsersModel> searchUsersModel{nullptr};
  std::shared_ptr<JsonWorker> jsonWorker{nullptr};
  QObject *currentObject{nullptr};
  QMessageBox messageBox;


public slots:

  void slotUserNameClicked(const QVariant &userId,
                           const QVariant &recipientName);
  void slotSetUserNamesList(const QJsonDocument &jsonUserNamesList);
  void slotBackButtonClicked();


};

#endif // SEARCHUSERSPAGE_H
