#ifndef MAINWINDOWCLASS_H
#define MAINWINDOWCLASS_H
//#include <QDebug>
#include <QMetaObject>
#include <QObject>
#include <QQuickItem>
#include <memory>
#include <QCoreApplication>

#include <QTcpSocket>
#include <QTcpServer>

#include "PagesModal.h"

// Interfaces
#include "IMainWindow.h"
#include "Engine\IQmlEngine.h"

#include "Pages\LoginPage.h"
#include "Pages\RegisterPage.h"
#include "Pages\DialogPage.h"
#include "Pages\ConversationPage.h"
#include "Pages\SearchUsersPage.h"
#include "JsonWorker\JsonWorker.h"


//#define DEBUG_1

class MainwindowClass
        : public QObject,
        public IMainWindow
{
    Q_OBJECT
public:
    explicit MainwindowClass(std::shared_ptr<IQmlEngine> engine,
                             QObject *parent = nullptr);
    ~MainwindowClass();

    bool init();




protected:
    //IMainWindow
    void showNextPage(const PagesTypes &page) override;
    void showPreviousPage() override;

    bool initPage(const PagesTypes &page);

    bool initMainPage(const PagesTypes &page);
    bool initLoginPage();
    bool initRegisterPage() override;
    bool initDialogPage() override;
    bool initConversationPage() override;
    bool initSearchUsersPage() override;
    void setCurrentUserId(const QString &userId) override;
    QString getCurrentUserId() override;
    void setCurrentDialogId(const QString &dialogId) override;
    QString getCurrentDialogId() override;
    void setRecipientId(const QString &userId) override ;
    QString getRecipientId() override ;
    void setRecipientName(const QString &userName) override;
    QString getRecipientName() override;



private:
    bool initServerWorker();
    bool initJsonWorker();

    QObject * getPage(const PagesTypes &type);
    void killPage(const PagesTypes &page);

    PagesTypes getPreviousPage();

    std::shared_ptr<IQmlEngine> iengine{nullptr};
    QObject *currentObject{nullptr};
    std::shared_ptr<ServerWorker> serverWorker{nullptr};
    std::shared_ptr<LoginPage> loginPage{nullptr};
    std::shared_ptr<RegisterPage> registerPage{nullptr};
    std::shared_ptr<DialogPage> dialogPage{nullptr};
    std::shared_ptr<ConversationPage> conversationPage{nullptr};
    std::shared_ptr<SearchUsersPage> searchUsersPage{nullptr};
    std::shared_ptr<JsonWorker> jsonWorker{nullptr};

    QString currentUserId;
    QString currentDialogId;
    QString recipientId;
    QString recipientName;
    PagesTypes pageToBeDeleted;
    PagesTypes previousPage;


    QMap<PagesTypes, QVariant> pagesPaths
    {
        {LOGIN_PAGE, "qrc:/Qml/Pages/LoginPage.qml" },
        {REGISTER_PAGE, "qrc:/Qml/Pages/RegisterPage.qml" },
        {DIALOG_PAGE, "qrc:/Qml/Pages/DialogPage.qml" },
        {CONVERSATION_PAGE, "qrc:/Qml/Pages/ConversationPage.qml" },
        {SEARCH_USERS_PAGE , "qrc:/Qml/Pages/SearchUsersPage.qml"}
    };

    QList<PagesTypes> pagesSatck;


private slots:
     void slotSetPreviousPage(const QVariant &page);
     void slotSetPageToBeDeleted(const QVariant &page);

};

#endif // MAINWINDOWCLASS_H
