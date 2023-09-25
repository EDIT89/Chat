#include "SearchUsersPage.h"

SearchUsersPage::SearchUsersPage(PagesTypes type, IMainWindow &iMainWindow,
                         std::shared_ptr<IQmlEngine> iengine,
                         std::shared_ptr<ServerWorker> &serverWorker,
                         QObject *parent)

    : QObject(parent), type(type),
      iMainWindow(iMainWindow),
      iengine(iengine),
      serverWorker(serverWorker){
    Q_ASSERT(this->iengine);
    Q_ASSERT(this->serverWorker);
}

SearchUsersPage::~SearchUsersPage()
{
    std::cout << "~SearchUsersPage()" << std::endl;
}

bool SearchUsersPage::init() { //QML component creation
    if (currentObject == nullptr) {

        currentObject = this->iengine->createComponent(SEARCH_USERS_PAGE_QML_PATH);

        if (currentObject == nullptr)
            return false;

        //Init model
        if(!initSearchUsersModel())
            return false;

        qDebug() << "SearchUsersPage init";
        //connecting signals and slots to this component

        connect(currentObject, SIGNAL(userNameClicked(QVariant, QVariant)), this,
                SLOT(slotUserNameClicked(QVariant, QVariant)));
        connect(serverWorker.get(), SIGNAL(signalUserNamesList(QJsonDocument)),
                this, SLOT(slotSetUserNamesList(QJsonDocument)));
        connect(currentObject, SIGNAL(backButton_Clicked()), this,
                SLOT(slotBackButtonClicked()));


        serverWorker->getUsersList(iMainWindow.getCurrentUserId());


    }

    return true;
}

QObject *SearchUsersPage::getComponent() { return currentObject; }



bool SearchUsersPage::initSearchUsersModel()// Userlist creation
{
    if (searchUsersModel == nullptr) {
        searchUsersModel = std::make_shared<SearchUsersModel>();
        return true;
    }
    return false;
}


//username click handling
void SearchUsersPage::slotUserNameClicked(const QVariant &userId,
                                      const QVariant &recipientName)
{
    iMainWindow.setRecipientId(userId.toString());
    iMainWindow.setRecipientName(recipientName.toString());
    std::cerr<<"setRecipientId(userId.toString());"<<
               iMainWindow.getRecipientId().toStdString()<<std::endl;
    std::cerr<<"setRecipientName(userId.toString());"<<
               iMainWindow.getRecipientName().toStdString()<<std::endl;
    iMainWindow.showNextPage(CONVERSATION_PAGE);
}
//processing a user list request
void SearchUsersPage::slotSetUserNamesList(const QJsonDocument &jsonUserNamesList)
{
    QList<structUsers> userNamesList =
    jsonWorker->getUserListFromJsonDocument(jsonUserNamesList);

    for(auto &i: userNamesList)
    {
        searchUsersModel->addToModel(i);
    }

    this->currentObject->setProperty("searchUsersModel",
                                     QVariant::fromValue(searchUsersModel.get()));

    qDebug()<<userNamesList.count();
}

//backButton click handling
void SearchUsersPage::slotBackButtonClicked()
{
    searchUsersModel->resetModel();
    iMainWindow.showPreviousPage();
}
