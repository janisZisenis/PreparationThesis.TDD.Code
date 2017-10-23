#ifndef COCOAVIEWS_COCOASOLUTIONITEMFACTORY_H
#define COCOAVIEWS_COCOASOLUTIONITEMFACTORY_H

#include <memory>
#include <string>

#include "CocoaViews/UnknownTypeException/UnknownTypeException.h"

class CNVisitable;
@class CocoaSolutionItem;

class CocoaSolutionItemFactory;
typedef std::shared_ptr<CocoaSolutionItemFactory> CocoaSolutionItemFactoryPtr;

class CocoaSolutionItemFactory {
public:
    virtual ~CocoaSolutionItemFactory () {}
protected:
    CocoaSolutionItemFactory() {}

public:
    virtual CocoaSolutionItem* makeCocoaSolutionItem(std::shared_ptr<CNVisitable> visitable) = 0;
};

#endif //COCOAVIEWS_COCOASOLUTIONITEMFACTORY_H