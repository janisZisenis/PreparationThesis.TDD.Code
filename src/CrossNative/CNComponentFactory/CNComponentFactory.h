#ifndef CROSSNATIVE_COMPONENTFACTORY_H
#define CROSSNATIVE_COMPONENTFACTORY_H

#include <memory>

class CNComponent;
class CNComposer;
class CNVisitable;

class CNComponentFactory;
typedef std::shared_ptr<CNComponentFactory> CNComponentFactoryPtr;

class CNComponentFactory {
public:
    static CNComponentFactoryPtr getNewInstance();
    virtual ~CNComponentFactory();
private:
    CNComponentFactory();

public:
    virtual std::shared_ptr<CNComponent> makeCNComposable(std::shared_ptr<CNVisitable> visitable,
                                                          std::shared_ptr<CNComposer> composer);
};


#endif //CROSSNATIVE_COMPONENTFACTORY_H