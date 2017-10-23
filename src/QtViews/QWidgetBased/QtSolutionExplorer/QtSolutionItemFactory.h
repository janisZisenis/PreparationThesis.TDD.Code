#ifndef QTVIEWS_QTSOLUTIONITEMFACTORY_H
#define QTVIEWS_QTSOLUTIONITEMFACTORY_H

#include <memory>
#include <string>
#include "QtViews/UnknownTypeException/UnknownTypeException.h"


class CNVisitable;
class QtSolutionItem;

class QtSolutionItemFactory;
typedef std::shared_ptr<QtSolutionItemFactory> QtSolutionItemFactoryPtr;

class QtSolutionItemFactory {
public:
    virtual ~QtSolutionItemFactory () {}
protected:
    QtSolutionItemFactory() {}

public:
    virtual std::shared_ptr<QtSolutionItem> makeQtSolutionItem(std::shared_ptr<CNVisitable> visitable) = 0;

};

#endif //QTVIEWS_QTSOLUTIONITEMFACTORY_H