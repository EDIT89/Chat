#ifndef DIALOGPAGE_H
#define DIALOGPAGE_H

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
#include "Models/DialogModel.h"
#include "JsonWorker/JsonWorker.h"

#include "PagesModal.h"

#define DIALOG_PAGE_QML_PATH "qrc:/Qml/Pages/DialogPage.qml"

class DialogPage : public QObject {
  Q_OBJECT

public:
  explicit DialogPage(PagesTypes type, IMainWindow &iMainWindow,
                     std::shared_ptr<IQmlEngine> iengine,
                     std::shared_ptr<ServerWorker> &serverWorker,
                     QObject *parent = nullptr);
  ~DialogPage();

  bool init();

  QObject *getComponent();

private:
  bool initDialogModel();
  PagesTypes type;
  IMainWindow &iMainWindow;
  std::shared_ptr<IQmlEngine> iengine{nullptr};
  std::shared_ptr<ServerWorker> serverWorker{nullptr};
  std::shared_ptr<DialogModel> dialogModel{nullptr};
  std::shared_ptr<JsonWorker> jsonWorker{nullptr};
  QObject *currentObject{nullptr};
  QMessageBox messageBox;


public slots:

  void slotUpdateUserStatus(const QJsonDocument &newUserStatus);
  void slotDialogClicked(const QVariant &dialogId,
                           const QVariant &recipientName);
  void slotSetDialogList(const QJsonDocument &jsonDialogList);
  void slotBackButtonClicked();
  void slotSearchUsersButtonClicked();


};

#endif // DIALOGPAGE_H

