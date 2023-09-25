#ifndef CONVERSATIONPAGE_H
#define CONVERSATIONPAGE_H


#include <QDebug>
#include <QQmlComponent>
#include <QVariant>
#include <iostream>
#include <qcryptographichash.h>
#include <memory>
#include <QMessageBox>
#include <QMetaObject>

// Interfaces
#include "IMainWindow.h"
#include "Engine/IQmlEngine.h"
#include "ServerWorker/ServerWorker.h"
#include "JsonWorker/JsonWorker.h"
#include "Models/ConversationModel.h"

#include "PagesModal.h"

#define CONVERSATION_PAGE_QML_PATH "qrc:/Qml/Pages/ConversationPage.qml"

class ConversationPage : public QObject {
  Q_OBJECT

public:
  explicit ConversationPage(PagesTypes type, IMainWindow &iMainWindow,
                     std::shared_ptr<IQmlEngine> iengine,
                     std::shared_ptr<ServerWorker> &serverWorker,
                     QObject *parent = nullptr);

  ~ConversationPage();

  bool init();

  QObject *getComponent();

public slots:
  void slotSetMessage(const QJsonDocument &jsonMessageDocument);
  void slotSetMessagesHistory(const QJsonDocument &jsonDocument);
  void slotactiveFocusChanged(const QVariant &focus);

private:
  bool initConversationModel();
  PagesTypes type;
  IMainWindow &iMainWindow;
  std::shared_ptr<IQmlEngine> iengine{nullptr};
  std::shared_ptr<ServerWorker> serverWorker{nullptr};
  std::shared_ptr<ConversationModel> conversationModel{nullptr};
  std::shared_ptr<JsonWorker> jsonWorker{nullptr};
  QObject *currentObject{nullptr};
  QMessageBox messageBox;



signals:
  void signalSendMessage(const QVariant &message);


public slots:
  void slotBackButtonClicked();

};

#endif // CONVERSATIONPAGE_H
