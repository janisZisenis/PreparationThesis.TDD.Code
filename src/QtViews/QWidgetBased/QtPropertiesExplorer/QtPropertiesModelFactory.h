#ifndef QTVIEWS_QTPROPERTIESMODELFACTORY_H
#define QTVIEWS_QTPROPERTIESMODELFACTORY_H

#include <memory>
#include <string>
#include "QtViews/UnknownTypeException/UnknownTypeException.h"

class CNVisitable;
class QtPropertiesModel;

class QtPropertiesModelFactory;
typedef std::shared_ptr<QtPropertiesModelFactory> QtPropertiesModelFactoryPtr;

class QtPropertiesModelFactory {
public:
    virtual ~QtPropertiesModelFactory() {}
protected:
    QtPropertiesModelFactory() {}

public:
    virtual QtPropertiesModel* makeQtPropertiesModel(std::shared_ptr<CNVisitable> visitable) = 0;
};

#endif //QTLVICE_QTPROPERTIESMODELFACTORY_H