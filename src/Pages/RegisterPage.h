#ifndef REGISTERPAGE_H
#define REGISTERPAGE_H

#include <QObject>
#include <QVariant>
#include <memory>

// Interfaces
#include "ServerWorker/ServerWorker.h"
#include "IMainWindow.h"
#include "Engine/IQmlEngine.h"

#include "PagesModal.h"

#define REGISTER_PAGE_QML_PATH "qrc:/Qml/Pages/RegisterPage.qml"

class RegisterPage : public QObject {
  Q_OBJECT
public:
  RegisterPage(PagesTypes type, IMainWindow &iMainWindow,
               std::shared_ptr<IQmlEngine> iengine,
               std::shared_ptr<ServerWorker> serverWorker,
               QObject *parent = nullptr);
  ~RegisterPage();

  bool init();
  QObject *getComponent();

private:
  PagesTypes type;
  IMainWindow &iMainWindow;
  std::shared_ptr<IQmlEngine> iengine{nullptr};
  std::shared_ptr<ServerWorker> serverWorker{nullptr};
  QObject *currentObject{nullptr};

public slots:
  void slotBackButtonClicked();
  void slotSignUpButtonClicked(const QVariant &login,
                                 const QVariant &password,
                                 const QVariant &passwordConfirm);
};

#endif // REGISTERPAGE_H
