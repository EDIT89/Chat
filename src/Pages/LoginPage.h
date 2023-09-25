#ifndef LOGINPAGE_H
#define LOGINPAGE_H

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

#include "PagesModal.h"

#define LOGIN_PAGE_QML_PATH "qrc:/Qml/Pages/LoginPage.qml"

class LoginPage : public QObject {
  Q_OBJECT

public:
  explicit LoginPage(PagesTypes type, IMainWindow &iMainWindow,
                     std::shared_ptr<IQmlEngine> iengine,
                     std::shared_ptr<ServerWorker> &serverWorker,
                     QObject *parent = nullptr);
  ~LoginPage();

  bool init();
  QObject *getComponent();

public slots:
  void slotSignInButtonClicked(const QVariant &login,
                               const QVariant &password);
  void slotSignUpButtonClicked();
  void slotShowNextPage(const QString &userId);

private:
  PagesTypes type;
  IMainWindow &iMainWindow;
  std::shared_ptr<IQmlEngine> iengine{nullptr};
  std::shared_ptr<ServerWorker> serverWorker{nullptr};
  QObject *currentObject{nullptr};
  QMessageBox messageBox;



};

#endif // LOGINPAGE_H

