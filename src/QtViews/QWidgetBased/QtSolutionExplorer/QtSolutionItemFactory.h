#ifndef QTVIEWS_QTSOLUTIONITEMFACTORY_H
#define QTVIEWS_QTSOLUTIONITEMFACTORY_H

#include <memory>
#include <string>

class UnknownTypeException : public std::exception {
    const char *what() const throw() override {
        return std::string("The given subtype of the CNVisitable is unknown").c_str();
    }
};

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