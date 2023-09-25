QT += quick
QT += widgets
QT += quickcontrols2
QT += core network

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        Models\DialogModel.cpp \
        Models\ConversationModel.cpp \
        Pages\ConversationPage.cpp \
        Pages\DialogPage.cpp \
        JsonWorker\JsonWorker.cpp \
        Pages\LoginPage.cpp \
        Pages\MainWindowClass.cpp \
        Engine\QmlEngine.cpp \
        Pages\RegisterPage.cpp \
        Models\SearchUsersModel.cpp \
        Pages\SearchUsersPage.cpp \
        ServerWorker\ServerWorker.cpp \
        main.cpp




RESOURCES += \
    Resources.qrc

HEADERS += \
    Models\DialogModel.h \
    Models\ConversationModel.h \
    Pages\ConversationPage.h \
    Pages\DialogPage.h \
    Pages\IMainWindow.h \
    Engine\IQmlEngine.h \
    JsonWorker\JsonWorker.h \
    Pages\LoginPage.h \
    Pages\MainWindowClass.h \
    PagesModal.h \
    Engine\QmlEngine.h \
    Pages\RegisterPage.h \
    Models\SearchUsersModel.h \
    Pages\SearchUsersPage.h \
    ServerWorker\ServerWorker.h \
    Structures\Structures.h


# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
target.path = $$[PWD]
!isEmpty(target.path): INSTALLS += target
