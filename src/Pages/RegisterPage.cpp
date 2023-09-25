#include "RegisterPage.h"


#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QVariant>
#include <iostream>
#include <qcryptographichash.h>
#include <windows.h>


RegisterPage::RegisterPage(PagesTypes type, IMainWindow &iMainWindow,
                           std::shared_ptr<IQmlEngine> iengine,
                          std::shared_ptr<ServerWorker> serverWorker,
                           QObject *parent)
    : QObject(parent), type(type), iMainWindow(iMainWindow), iengine(iengine),
      serverWorker(serverWorker) {
    Q_ASSERT(this->iengine);
    Q_ASSERT(this->serverWorker);
}



RegisterPage::~RegisterPage()
{
    std::cerr<<"~RegisterPage()";
    //delete currentObject;
}

bool RegisterPage::init()
{
    if (currentObject == nullptr) {
        currentObject = this->iengine->createComponent(REGISTER_PAGE_QML_PATH);
        if (currentObject == nullptr)
            return false;

        qDebug()<<"RegisterPage::init() ";
        connect(currentObject, SIGNAL(backButtonClicked()), this,
                SLOT(slotBackButtonClicked()));

        connect(currentObject, SIGNAL(registerButtonClicked(QVariant, QVariant, QVariant)), this,
            SLOT(slotSignUpButtonClicked(QVariant, QVariant, QVariant)));

        connect(serverWorker.get(), SIGNAL(signalShowLoginPage()), this,
                SLOT(slotBackButtonClicked()));
    }
    return true;
}



QObject *RegisterPage::getComponent() { return currentObject; }

void RegisterPage::slotBackButtonClicked() {
    iMainWindow.showPreviousPage();
}


//add new user
void RegisterPage ::slotSignUpButtonClicked(const QVariant &login,
                                              const QVariant &password,
                                              const QVariant &passwordConfirm)
{
    if(!login.toString().isEmpty() && !password.toString().isEmpty() &&
            !passwordConfirm.toString().isEmpty())
    {
        serverWorker->addNewUser(login, password);
    }
    else
    {
        MessageBox(nullptr, L"Login or password is empty", L"Error", MB_OK);
    }
}
