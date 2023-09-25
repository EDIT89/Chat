#include "DialogPage.h"

DialogPage::DialogPage(PagesTypes type, IMainWindow &iMainWindow,
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

DialogPage::~DialogPage()
{
    std::cout << "~DialogPage" << std::endl;
}

bool DialogPage::init() { //QML component creation
    if (currentObject == nullptr) {

        currentObject = this->iengine->createComponent(DIALOG_PAGE_QML_PATH);

        if (currentObject == nullptr)
            return false;

        //Init model
        if(!initDialogModel())
            return false;

        qDebug() << "contactPageinit";
        //connecting signals and slots to this component

        connect(currentObject, SIGNAL(dialogClicked(QVariant, QVariant)), this,
                SLOT(slotDialogClicked(QVariant, QVariant)));
        connect(serverWorker.get(), SIGNAL(signalDialogList(QJsonDocument)),
                this, SLOT(slotSetDialogList(QJsonDocument)));
        connect(currentObject, SIGNAL(backButton_Clicked()), this,
                SLOT(slotBackButtonClicked()));
        connect(currentObject, SIGNAL(searchUsersButton_Clicked()), this,
                SLOT(slotSearchUsersButtonClicked()));

        connect(serverWorker.get(), SIGNAL(signalChangeUserStatus(QJsonDocument)),
                this, SLOT(slotUpdateUserStatus(QJsonDocument)));


        serverWorker->getDialogList(iMainWindow.getCurrentUserId());

        std::cerr<<"currentDialogId"<<iMainWindow.getCurrentDialogId().toStdString();

    }

    return true;
}

QObject *DialogPage::getComponent() { return currentObject; }



bool DialogPage::initDialogModel()// Userlist creation
{
    if (dialogModel == nullptr) {
        dialogModel = std::make_shared<DialogModel>();
        return true;
    }
    return false;
}

void DialogPage::slotUpdateUserStatus(const QJsonDocument &newUserStatus)
{
    qDebug()<<"slotUpdateUserStatus";
    dialogModel->updateUserStatus(jsonWorker->getNewUserStatus(newUserStatus));
}


//dialog click handling
void DialogPage::slotDialogClicked(const QVariant &dialogId,
                                   const QVariant &recipientName)
{
    qDebug()<<"slotDialogClicked"<<dialogId.toString();
    iMainWindow.setCurrentDialogId(dialogId.toString());
    iMainWindow.setRecipientName(recipientName.toString());
    iMainWindow.showNextPage(CONVERSATION_PAGE);
}


//processing a user list request
void DialogPage::slotSetDialogList(const QJsonDocument &jsonDialogList)
{
    QList<structDialog> dialogList =
    jsonWorker->getDialogListFromJsonDocument(jsonDialogList);

    for(auto &i:dialogList)
    {
        dialogModel->addDialogToModel(i);
    }

    this->currentObject->setProperty("dialogModel",
                                     QVariant::fromValue(dialogModel.get()));

    qDebug()<<dialogList.count();
}


//backButton click handling
void DialogPage::slotBackButtonClicked()
{
    dialogModel->resetModel();
    iMainWindow.showPreviousPage();
}



void DialogPage::slotSearchUsersButtonClicked()
{
    iMainWindow.showNextPage(SEARCH_USERS_PAGE);
    std::cout<<"slotSearchUsersButtonClicked"<<std::endl;
}
