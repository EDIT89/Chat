#ifndef QMLENGINE_H
#define QMLENGINE_H

#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QQmlContext>

#include <memory>

#include "IQmlEngine.h"

class QmlEngine : public QObject, public IQmlEngine {
  Q_OBJECT
public:
  QmlEngine(std::shared_ptr<QQmlApplicationEngine> engine,
            QObject *parent = nullptr);

protected:
  QObject *createComponent(std::string path);

private:
  std::shared_ptr<QQmlApplicationEngine> engine;
};

#endif // QMLENGINE_H
