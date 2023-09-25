#include "ConversationPage.h"
#include "Structures/Structures.h"

ConversationPage::ConversationPage(PagesTypes type, IMainWindow &iMainWindow,
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



ConversationPage::~ConversationPage()
{
    iMainWindow.setCurrentDialogId("");
    iMainWindow.setRecipientId("");
    std::cerr<<"ConversationPage::~ConversationPage() setCurrentDialogId()"<<iMainWindow.getCurrentDialogId().toStdString()<<std::endl;
    std::cerr<<"~ConversationPage()"<<std::endl;
}



bool ConversationPage::init() {
    if (currentObject == nullptr) {

        currentObject = this->iengine->createComponent(CONVERSATION_PAGE_QML_PATH);

        if (currentObject == nullptr)
            return false;

        if(!initConversationModel())
            return false;

        qDebug() << "conversationPageinit";

        connect(currentObject, SIGNAL(activeFocusChanged(QVariant)), this,
                SLOT(slotactiveFocusChanged(QVariant)));

        connect(currentObject, SIGNAL(backButton_Clicked()), this,
                SLOT(slotBackButtonClicked()));

        connect(currentObject, SIGNAL(sendMessageButtonClicked(QVariant,
                                                               QVariant,
                                                               QVariant,
                                                               QVariant)),
                serverWorker.get(), SLOT(slotSendMessage(QVariant,
                                                         QVariant,
                                                         QVariant,
                                                         QVariant)));

        connect(serverWorker.get(), SIGNAL(signalIncommingMessage(QJsonDocument)),
                this, SLOT(slotSetMessage(QJsonDocument)));

        connect(serverWorker.get(), SIGNAL(signalMessagesHistory(QJsonDocument)),
                this, SLOT(slotSetMessagesHistory(QJsonDocument)));

        currentObject->setProperty("dialog_Name",QVariant::fromValue(iMainWindow.getRecipientName()));
        currentObject->setProperty("currentUserId",QVariant::fromValue(iMainWindow.getCurrentUserId()));
        currentObject->setProperty("recipientId",QVariant::fromValue(iMainWindow.getRecipientId()));
        currentObject->setProperty("dialogId1",QVariant::fromValue(iMainWindow.getCurrentDialogId()));

        serverWorker->getMessagesHistory(iMainWindow.getCurrentUserId(),
                                         iMainWindow.getCurrentDialogId(),
                                         iMainWindow.getRecipientId());



    }

    return true;
}



QObject *ConversationPage::getComponent(){return currentObject;}



bool ConversationPage::initConversationModel()
{
    if (conversationModel == nullptr) {
        conversationModel = std::make_shared<ConversationModel>(this->iMainWindow);
        return true;
    }
    return false;
}



void ConversationPage::slotSetMessage(const QJsonDocument &jsonMessageDocument)
{

    conversationModel->addToModel(jsonWorker->getStructData(jsonMessageDocument,
                                                            iMainWindow.getCurrentUserId()));

    this->currentObject->setProperty("conversationModel",
                                     QVariant::fromValue(conversationModel.get()));

    QMetaObject::invokeMethod(currentObject, "moveToMessage");
}


//download message history
void ConversationPage::slotSetMessagesHistory(const QJsonDocument &jsonDocument)
{

    QList<structData> dataList = jsonWorker->getMessagesHistoryList(jsonDocument,
                                                                    iMainWindow.getCurrentUserId());

    for(auto &i: dataList)
    {
        conversationModel->addToModel(i);
    }

    this->currentObject->setProperty("conversationModel",
                                     QVariant::fromValue(conversationModel.get()));

    //move to last message (QML function)
    QMetaObject::invokeMethod(currentObject, "moveToMessage");
    qDebug()<<"ConversationPage::slotSetMessagesHistory";

}

void ConversationPage::slotactiveFocusChanged(const QVariant &focus)
{
    if(!focus.toBool())
        this->~ConversationPage();
}



void ConversationPage::slotBackButtonClicked()
{
    iMainWindow.showPreviousPage();
}
