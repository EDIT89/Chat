#include "QmlEngine.h"

#include <iostream>

QmlEngine::QmlEngine(std::shared_ptr<QQmlApplicationEngine> engine,
                     QObject *parent)
    : QObject(parent), engine(engine) {}


QObject *QmlEngine::createComponent(std::string path)
{
  QQmlComponent component(this->engine.get(), QString::fromStdString(path));
  QObject *object = component.create();
  if( object == nullptr )
  {
    for( const auto &error : component.errors() )
    {
        std::cerr << "Qml engine error: " << error.toString().toStdString() << std::endl;
    }
  }
  return object;
}
