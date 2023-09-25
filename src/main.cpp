#include <QApplication>
#include "Pages\MainWindowClass.h"

#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QString>

#include <iostream>
#include <memory>

#include "Engine\QmlEngine.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  QQmlApplicationEngine engine;

  std::shared_ptr<QQmlApplicationEngine> enginePtr =
      std::make_shared<QQmlApplicationEngine>(&engine);

  std::shared_ptr<IQmlEngine> iqmlEngine =
      std::make_shared<QmlEngine>(enginePtr);

  std::shared_ptr<MainwindowClass> mainWindowClass =
      std::make_shared<MainwindowClass>(iqmlEngine);

  if (!mainWindowClass->init()) {
    std::cerr << "Error while initing MainWindow object" << std::endl;
    QApplication::exit(-1);
  }

  setlocale(LC_ALL, "RU");

  int ret = app.exec();
  return ret;
}
