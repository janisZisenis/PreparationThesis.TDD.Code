#ifndef CROSSVIEWS_CREATECOMPONENTSTRATEGY_TESTDOUBLESH
#define CROSSVIEWS_CREATECOMPONENTSTRATEGY_TESTDOUBLESH

#include "CreateComponentStrategy.h"

class CreateComponentStrategyDummy;
typedef std::shared_ptr<CreateComponentStrategyDummy> CreateComponentStrategyDummyPtr;
class CreateComponentStrategyDummy : public CreateComponentStrategy {
public:
    static CreateComponentStrategyDummyPtr getNewInstance() {
        return CreateComponentStrategyDummyPtr(new CreateComponentStrategyDummy());
    }
    virtual ~CreateComponentStrategyDummy() {}
protected:
    CreateComponentStrategyDummy() {}

public:
    virtual std::shared_ptr<CNComponent> createComponent() { 
        return nullptr; 
    };
};

class CreateComponentStrategyStub;
typedef std::shared_ptr<CreateComponentStrategyStub> CreateComponentStrategyStubPtr;
class CreateComponentStrategyStub : public CreateComponentStrategyDummy {
public:
    static CreateComponentStrategyStubPtr getNewInstance() {
        return CreateComponentStrategyStubPtr(new CreateComponentStrategyStub());
    }
    virtual ~CreateComponentStrategyStub() {}
protected:
    CreateComponentStrategyStub() {}

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

class CreateComponentStrategySaboteur;
typedef std::shared_ptr<CreateComponentStrategySaboteur> CreateComponentStrategySaboteurPtr;
class CreateComponentStrategySaboteur : public CreateComponentStrategyDummy {
public:
    static CreateComponentStrategySaboteurPtr getNewInstance() {
        return CreateComponentStrategySaboteurPtr(new CreateComponentStrategySaboteur());
    }
    virtual ~CreateComponentStrategySaboteur() {}
protected:
    CreateComponentStrategySaboteur() {}

public:
    virtual std::shared_ptr<CNComponent> createComponent() {
        throw CreationCanceledException();
    };
};

#endif //CROSSVIEWS_CREATECOMPONENTSTRATEGY_TESTDOUBLESH
