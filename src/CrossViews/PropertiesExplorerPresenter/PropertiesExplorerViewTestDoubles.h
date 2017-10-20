#ifndef CROSSVIEWS_PROPERTIESEXPLORERVIEW_TESTDOUBLES_H
#define CROSSVIEWS_PROPERTIESEXPLORERVIEW_TESTDOUBLES_H

#include "PropertiesExplorerView.h"

class PropertiesExplorerViewDummy;
typedef std::shared_ptr<PropertiesExplorerViewDummy> PropertiesExplorerViewDummyPtr;
class PropertiesExplorerViewDummy : public PropertiesExplorerView {
public:
    static PropertiesExplorerViewDummyPtr getNewInstance() {
        return PropertiesExplorerViewDummyPtr(new PropertiesExplorerViewDummy());
    }
    virtual ~PropertiesExplorerViewDummy() {}
protected:
    PropertiesExplorerViewDummy() {}

public:
    virtual void displayPropertiesFor(CNVisitablePtr visitable) override {}
    virtual void displayEmptyProperties() override {}
    void accept(CNVisitorPtr visitor) override {}
};

class PropertiesExplorerViewSpy;
typedef std::shared_ptr<PropertiesExplorerViewSpy> PropertiesExplorerViewSpyPtr;
class PropertiesExplorerViewSpy : public PropertiesExplorerViewDummy {
public:
    static PropertiesExplorerViewSpyPtr getNewInstance() {
        return PropertiesExplorerViewSpyPtr(new PropertiesExplorerViewSpy());
    }
    virtual ~PropertiesExplorerViewSpy() {}
protected:
    PropertiesExplorerViewSpy() {}

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

#endif //CROSSVIEWS_PROPERTIESEXPLORERVIEW_TESTDOUBLES_H
