#include "LoginPage.h"

LoginPage::LoginPage(PagesTypes type, IMainWindow &iMainWindow,
                     std::shared_ptr<IQmlEngine> iengine,
                     std::shared_ptr<ServerWorker> &serverWorker,
                     QObject *parent)

    : QObject(parent), type(type),
      iMainWindow(iMainWindow),
      iengine(iengine),
      serverWorker(serverWorker)
{
    Q_ASSERT(this->iengine);
    Q_ASSERT(this->serverWorker);
}

LoginPage::~LoginPage()
{
    std::cerr<<"~LoginPage()";
}


bool LoginPage::init() {
    if (currentObject == nullptr) {

        currentObject = this->iengine->createComponent(LOGIN_PAGE_QML_PATH);

        if (currentObject == nullptr)
            return false;

        qDebug() << "loginpageinit";

        connect(currentObject, SIGNAL(loginButtonClicked(QVariant, QVariant)),
                this, SLOT(slotSignInButtonClicked(QVariant, QVariant)));

        connect(currentObject, SIGNAL(signUpButtonClicked()), this,
                SLOT(slotSignUpButtonClicked()));

        connect(serverWorker.get(),SIGNAL(signalEnterSuccess(QString)), this,
                SLOT(slotShowNextPage(QString)));

    }
    return true;
}

QObject *LoginPage::getComponent() { return currentObject; }

void LoginPage::slotSignInButtonClicked(const QVariant &login,
                                        const QVariant &password)
{
    serverWorker->checkUser(login, password);
    std::cerr<<"slotSignInButtonClicked"<<std::endl;
}

void LoginPage::slotSignUpButtonClicked() {
    qDebug()<<"slotSignUpButtonClicked()";
    iMainWindow.showNextPage(REGISTER_PAGE);
}

void LoginPage::slotShowNextPage(const QString &userId)
{
    iMainWindow.setCurrentUserId(userId);
    iMainWindow.showNextPage(DIALOG_PAGE);
    qDebug()<<"currentUserId"<<iMainWindow.getCurrentUserId();
}
