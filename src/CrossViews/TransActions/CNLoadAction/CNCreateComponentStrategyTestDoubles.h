#ifndef CROSSNATIVE_CREATECOMPONENTSTRATEGY_TESTDOUBLES_H
#define CROSSNATIVE_CREATECOMPONENTSTRATEGY_TESTDOUBLES_H

#include "CNCreateComponentStrategy.h"

class CNCreateComponentStrategyDummy;
typedef std::shared_ptr<CNCreateComponentStrategyDummy> CNCreateComponentStrategyDummyPtr;
class CNCreateComponentStrategyDummy : public CNCreateComponentStrategy {
public:
    static CNCreateComponentStrategyDummyPtr getNewInstance() {
        return CNCreateComponentStrategyDummyPtr(new CNCreateComponentStrategyDummy());
    }
    virtual ~CNCreateComponentStrategyDummy() {}
protected:
    CNCreateComponentStrategyDummy() {}

public:
    virtual std::shared_ptr<CNComponent> createComponent() { 
        return nullptr; 
    };
};

class CNCreateComponentStrategyStub;
typedef std::shared_ptr<CNCreateComponentStrategyStub> CNCreateComponentStrategyStubPtr;
class CNCreateComponentStrategyStub : public CNCreateComponentStrategyDummy {
public:
    static CNCreateComponentStrategyStubPtr getNewInstance() {
        return CNCreateComponentStrategyStubPtr(new CNCreateComponentStrategyStub());
    }
    virtual ~CNCreateComponentStrategyStub() {}
protected:
    CNCreateComponentStrategyStub() {}

public:
    virtual void setCNComponent(std::shared_ptr<CNComponent> component) {
       created = component;
    }
    virtual std::shared_ptr<CNComponent> createComponent() {
        return created;
    };

private:
    std::shared_ptr<CNComponent> created;
};

class CNCreateComponentStrategySaboteur;
typedef std::shared_ptr<CNCreateComponentStrategySaboteur> CNCreateComponentStrategySaboteurPtr;
class CNCreateComponentStrategySaboteur : public CNCreateComponentStrategyDummy {
public:
    static CNCreateComponentStrategySaboteurPtr getNewInstance() {
        return CNCreateComponentStrategySaboteurPtr(new CNCreateComponentStrategySaboteur());
    }
    virtual ~CNCreateComponentStrategySaboteur() {}
protected:
    CNCreateComponentStrategySaboteur() {}

public:
    virtual std::shared_ptr<CNComponent> createComponent() {
        throw CreationCanceledException();
    };
};

#endif //CROSSNATIVE_CREATECOMPONENTSTRATEGY_TESTDOUBLES_H
