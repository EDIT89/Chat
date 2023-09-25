#include "MainWindowClass.h"
#include <QQmlProperty>
#include <iostream>




MainwindowClass ::MainwindowClass(std::shared_ptr<IQmlEngine> iengine,
                                  QObject *parent)
    : QObject(parent), iengine(iengine) {
    Q_ASSERT(this->iengine);

}

MainwindowClass::~MainwindowClass() {
    std::cerr << "MainWindowClass destructor" << std::endl;
    serverWorker->~ServerWorker();
    delete currentObject;
}

bool MainwindowClass::init() {

    currentObject = iengine->createComponent("qrc:/Qml/main.qml");

    if (currentObject == nullptr)
        return false;

    //init  classes
    if(!initJsonWorker())
        return false;

    if(!initServerWorker())
        return false;

    //Init Pages
    if(!initMainPage(LOGIN_PAGE))
        return false;

    connect(currentObject, SIGNAL(setPreviousPage(QVariant)), this,
            SLOT(slotSetPreviousPage(QVariant)));

    connect(currentObject, SIGNAL(setPageToBeDeleted(QVariant)), this,
            SLOT(slotSetPageToBeDeleted(QVariant)));

    return true;
}


void MainwindowClass::killPage(const PagesTypes &page)
{
    switch (page)
    {
    case LOGIN_PAGE:
        qDebug()<<"killPage LOGIN_PAGE";
        loginPage = nullptr;
        break;

    case REGISTER_PAGE:
        qDebug()<<"killPage REGISTER_PAGE";
        registerPage = nullptr;
        break;

    case DIALOG_PAGE:
        qDebug()<<"killPage DIALOG_PAGE";
        dialogPage = nullptr;
        break;

    case SEARCH_USERS_PAGE:
        qDebug()<<"killPage SEARCH_USERS_PAGE";
        searchUsersPage = nullptr;
        break;

    case CONVERSATION_PAGE:
        qDebug()<<"killPage CONVERSATION_PAGE";
        conversationPage = nullptr;
        break;

    default:
        return;
        break;
    }
}

PagesTypes MainwindowClass::getPreviousPage()
{
    pagesSatck.removeLast();
    qDebug()<<"MainwindowClass::getPreviousPage"<<pagesSatck;
    return pagesSatck.last();
}


void MainwindowClass::slotSetPreviousPage(const QVariant &page)
{
    QMap<PagesTypes,QVariant>::Iterator it;

    for(auto it = pagesPaths.begin(); it != pagesPaths.end(); ++it)
    {
        if(it.value() == page)
        {
            this->previousPage = it.key();
            qDebug()<<"previousPage"<<previousPage;
            break;
        }
    }
}



void MainwindowClass::slotSetPageToBeDeleted(const QVariant &page)
{
    QMap<PagesTypes,QVariant>::Iterator it;

    for(auto it = pagesPaths.begin(); it != pagesPaths.end(); ++it)
    {
        if(it.value() == page)
        {
            this->pageToBeDeleted = it.key();
            qDebug()<<"pageToBeDeleted"<<pageToBeDeleted;
            break;
        }
    }
}



void MainwindowClass::showNextPage(const PagesTypes &page)
{
    this->initPage(page);
    pagesSatck.push_back(page);
    qDebug()<<"pagesStackALl"<<pagesSatck;
    QMetaObject::invokeMethod(
                currentObject, "showNextPage",
                Q_ARG(QVariant, QVariant::fromValue(getPage(page))));
    qDebug()<<"pagesStackcount"<<pagesSatck.count();
    this->killPage(pagesSatck.at(pagesSatck.count()-2));
}



void MainwindowClass::showPreviousPage()
{
    PagesTypes newPreviousPage = getPreviousPage();
    this->initPage(newPreviousPage);
    QMetaObject::invokeMethod(currentObject, "showPreviousPage",
                              Q_ARG(QVariant, QVariant::fromValue(getPage(newPreviousPage))));

    this->killPage(pageToBeDeleted);
}



bool MainwindowClass::initPage(const PagesTypes &page)
{
    switch (page)
    {
    case LOGIN_PAGE:
        qDebug()<<"MainwindowClass::initPage LOGIN_PAGE";
        return initLoginPage();
        break;

    case REGISTER_PAGE:
        qDebug()<<"MainwindowClass::initPage REGISTER_PAGE";
        return initRegisterPage();
        break;

    case DIALOG_PAGE:
        qDebug()<<"MainwindowClass::initPage DIALOG_PAGE";
        return initDialogPage();
        break;

    case SEARCH_USERS_PAGE:
        qDebug()<<"MainwindowClass::initPage SEARCH_USERS_PAGE";
        return initSearchUsersPage();
        break;

    case CONVERSATION_PAGE:
        qDebug()<<"MainwindowClass::initPage CONVERSATION_PAGE";
        return initConversationPage();
        break;

    default:
        return false;
        break;
    }
}

bool MainwindowClass::initMainPage(const PagesTypes &page)
{
    if(this->initPage(page))
    {
        pagesSatck.push_back(page);
        qDebug()<<"pagesStackALl"<<pagesSatck;
        QMetaObject::invokeMethod(
                    currentObject, "initMainPage",
                    Q_ARG(QVariant, QVariant::fromValue(getPage(page))));
        return true;
    }
    return false;
}


QObject *MainwindowClass::getPage(const PagesTypes &type)
{
    switch (type)
    {
    case LOGIN_PAGE:
        qDebug()<<"MainwindowClass::getPage LOGIN_PAGE"<<loginPage->getComponent();
        return loginPage->getComponent();
        break;

    case REGISTER_PAGE:
        qDebug()<<"MainwindowClass::getPage REGISTER_PAGE";
        return  registerPage->getComponent();
        break;

    case DIALOG_PAGE:
        qDebug()<<"MainwindowClass::getPage DIALOG_PAGE";
        return  dialogPage->getComponent();
        break;

    case SEARCH_USERS_PAGE:
        qDebug()<<"MainwindowClass::getPage SEARCH_USERS_PAGE";
        return  searchUsersPage->getComponent();
        break;

    case CONVERSATION_PAGE:
        qDebug()<<"MainwindowClass::getPage CONVERSATION_PAGE";
        return  conversationPage->getComponent();
        break;

    default:
        return nullptr;
    }
}



//init  classes
bool MainwindowClass::initServerWorker()
{
    if (serverWorker == nullptr) {
        serverWorker = std::make_shared<ServerWorker>(*this);
        bool ret = serverWorker->init();
        if (ret) {
        }
        return ret;
    }
    return true;
}



bool MainwindowClass::initJsonWorker()
{
    if (jsonWorker == nullptr) {
        jsonWorker = std::make_shared<JsonWorker>(*this);
        return true;
    }
    return false;
}



bool MainwindowClass::initDialogPage()
{
    if (dialogPage == nullptr) {
        dialogPage = std::make_shared<DialogPage>(DIALOG_PAGE,
                                                  *this,
                                                  this->iengine,
                                                  this->serverWorker);
        bool ret = dialogPage->init();
        if (ret) {
        }
        return ret;
    }
    return true;
}



bool MainwindowClass::initConversationPage()
{
    if (conversationPage == nullptr) {
        conversationPage = std::make_shared<ConversationPage>(CONVERSATION_PAGE,
                                                              *this,
                                                              this->iengine,
                                                              this->serverWorker);
        bool ret = conversationPage->init();
        if (ret) {
        }
        return ret;
    }
    return true;
}



bool MainwindowClass::initSearchUsersPage()
{
    if (searchUsersPage == nullptr) {
        searchUsersPage = std::make_shared<SearchUsersPage>(SEARCH_USERS_PAGE,
                                                            *this,
                                                            this->iengine,
                                                            this->serverWorker);
        bool ret = searchUsersPage->init();
        if (ret) {
        }
        return ret;
    }
    return true;
}



bool MainwindowClass::initRegisterPage() {

    if (registerPage == nullptr) {
        registerPage = std::make_shared<RegisterPage>(
                    REGISTER_PAGE, *this, this->iengine, this->serverWorker);

        bool ret = registerPage->init();
        if (ret) {
        }
        return ret;
    }
    return true;
}


bool MainwindowClass::initLoginPage()
{
    if (loginPage == nullptr) {
        loginPage = std::make_shared<LoginPage>(LOGIN_PAGE,
                                                *this,
                                                this->iengine,
                                                this->serverWorker);
        bool ret = loginPage->init();
        if (ret) {
            return ret;
        }
    }
    return true;
}



void MainwindowClass::setCurrentUserId(const QString &userId)
{
    currentUserId = userId;
}



QString MainwindowClass::getCurrentUserId()
{
    return currentUserId;
}



void MainwindowClass::setCurrentDialogId(const QString &dialogId)
{
    currentDialogId = dialogId;
}



QString MainwindowClass::getCurrentDialogId()
{
    return currentDialogId;
}



void MainwindowClass::setRecipientId(const QString &userId)
{
    recipientId = userId;
}



QString MainwindowClass::getRecipientId()
{
    return recipientId;
}



void MainwindowClass::setRecipientName(const QString &userName)
{
    recipientName = userName;
}



QString MainwindowClass::getRecipientName()
{
    return recipientName;
}



