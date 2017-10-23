#ifndef COCOAVIEWS_COCOAPROPERTIESMODELFACTORY_H
#define COCOAVIEWS_COCOAPROPERTIESMODELFACTORY_H

#include <memory>
#include <string>
#include "CocoaViews/UnknownTypeException/UnknownTypeException.h"

class CNVisitable;
@class CocoaPropertiesModel;

class CocoaPropertiesModelFactory;
typedef std::shared_ptr<CocoaPropertiesModelFactory> CocoaPropertiesModelFactoryPtr;

class CocoaPropertiesModelFactory {
public:
    virtual ~CocoaPropertiesModelFactory() {}
protected:
    CocoaPropertiesModelFactory() {}

public:
    virtual CocoaPropertiesModel* makeCocoaPropertiesModel(std::shared_ptr<CNVisitable> visitable) = 0;
};

#endif //COCOAVIEWS_COCOAPROPERTIESMODELFACTORY_H