#ifndef IMAINWINDOW_H
#define IMAINWINDOW_H

#include <QObject>

#include "Pages/PagesModal.h"

class IMainWindow {
public:

  virtual void showNextPage(const PagesTypes &page) = 0;
  virtual void showPreviousPage() = 0;


  virtual bool initDialogPage() = 0;
  virtual bool initConversationPage() = 0;
  virtual bool initSearchUsersPage() = 0;
  virtual bool initRegisterPage() = 0;
  //virtual bool initLoginPage() = 0;

  virtual void setCurrentUserId(const QString &userId) = 0;
  virtual QString getCurrentUserId() = 0;
  virtual void setCurrentDialogId(const QString &dialogId) = 0;
  virtual QString getCurrentDialogId() = 0;
  virtual void setRecipientId(const QString &userId) = 0;
  virtual QString getRecipientId() = 0;
  virtual void setRecipientName(const QString &userName) = 0;
  virtual QString getRecipientName() = 0;

  virtual ~IMainWindow() {}

private:
};

#endif // IMAINWINDOW_H
