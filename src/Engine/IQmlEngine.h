#ifndef IQMLENGINE_H
#define IQMLENGINE_H

#include <QObject>

class IQmlEngine {
public:
  virtual QObject *createComponent(std::string path) = 0;
  virtual ~IQmlEngine() {}
};
#endif // IQMLENGINE_H
