#ifndef CROSSNATIVE_PROPERTIESEXPLORERVIEW_TESTDOUBLES_H
#define CROSSNATIVE_PROPERTIESEXPLORERVIEW_TESTDOUBLES_H

#include "CNPropertiesExplorerView.h"

class CNPropertiesExplorerViewDummy;
typedef std::shared_ptr<CNPropertiesExplorerViewDummy> CNPropertiesExplorerViewDummyPtr;
class CNPropertiesExplorerViewDummy : public CNPropertiesExplorerView {
public:
    static CNPropertiesExplorerViewDummyPtr getNewInstance() {
        return CNPropertiesExplorerViewDummyPtr(new CNPropertiesExplorerViewDummy());
    }
    virtual ~CNPropertiesExplorerViewDummy() {}
protected:
    CNPropertiesExplorerViewDummy() {}

public:
    virtual void displayPropertiesFor(CNVisitablePtr visitable) override {}
    virtual void displayEmptyProperties() override {}
    void accept(CNVisitorPtr visitor) override {}
};

class CNPropertiesExplorerViewSpy;
typedef std::shared_ptr<CNPropertiesExplorerViewSpy> CNPropertiesExplorerViewSpyPtr;
class CNPropertiesExplorerViewSpy : public CNPropertiesExplorerViewDummy {
public:
    static CNPropertiesExplorerViewSpyPtr getNewInstance() {
        return CNPropertiesExplorerViewSpyPtr(new CNPropertiesExplorerViewSpy());
    }
    virtual ~CNPropertiesExplorerViewSpy() {}
protected:
    CNPropertiesExplorerViewSpy() {}

public:
    virtual void displayPropertiesFor(CNVisitablePtr visitable) override {
        displayed = visitable;
    }
    virtual CNVisitablePtr getDisplayed() {
        return displayed;
    }

    virtual void displayEmptyProperties() override {
        displaysEmptyProperties = true;
    }
    virtual bool getDisplaysEmptyProperties() {
        return displaysEmptyProperties;
    }


    virtual void accept(CNVisitorPtr visitor) override {
        accepted = visitor;
    }
    virtual CNVisitorPtr getAccepted() {
        return accepted;
    }
private:
    CNVisitorPtr accepted;
    CNVisitablePtr displayed;
    bool displaysEmptyProperties = false;
};

#endif //CROSSNATIVE_PROPERTIESEXPLORERVIEW_TESTDOUBLES_H
