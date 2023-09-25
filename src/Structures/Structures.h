#ifndef STRUCTURES_H
#define STRUCTURES_H
#include <QString>

//User data
struct structUsers {
    structUsers(){}

    structUsers(const QString &userId,
                const QString &login,
                const bool &userStatus)
        : userId(userId),
          login(login),
          userStatus(userStatus){}

    QString userId;
    QString login;
    bool userStatus;
};

struct structDialog{

    structDialog(){};
    structDialog(const QString &dialogId,
                 const QString &dialogName,
                 const bool &userStatus,
                 const QString &lastMessage,
                 const QString &lastMessageTime)
        : dialogId(dialogId),
          dialogName(dialogName),
          userStatus(userStatus),
          lastMessage(lastMessage),
          lastMessageTime(lastMessageTime){};

    QString dialogId;
    QString dialogName;
    bool userStatus;
    QString lastMessage;
    QString lastMessageTime;
};

//Message data
struct structData {

    structData(){};
    structData(const QString &dialogId,
               const QString &userId,
               const QString &incommingData,
               const QString &timestamp,
               const bool &rightSide)
        : dialogId(dialogId),
          userId(userId),
          incommingData(incommingData),
          timestamp(timestamp),
          rightSide(rightSide){}

    QString dialogId;
    QString userId;
    QString incommingData;
    QString timestamp;
    bool rightSide;
};

#endif // STRUCTURES_H
