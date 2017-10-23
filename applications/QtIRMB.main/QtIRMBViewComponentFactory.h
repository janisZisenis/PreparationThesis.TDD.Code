#ifndef QTIRMB_QTIRMBVIEWCOMPONENTFACTORY_H
#define QTIRMB_QTIRMBVIEWCOMPONENTFACTORY_H

#include <QtViews/QtViewComponentFactory/QtViewComponentFactory.h>

class QtIRMBViewComponentFactory;
typedef std::shared_ptr<QtIRMBViewComponentFactory> QtIRMBViewComponentFactoryPtr;

class QtIRMBViewComponentFactory : public QtViewComponentFactory {
public:
    static QtIRMBViewComponentFactoryPtr getNewInstance();
    virtual ~QtIRMBViewComponentFactory();
private:
    QtIRMBViewComponentFactory();
};

#endif //QTIRMB_QTIRMBVIEWCOMPONENTFACTORY_H