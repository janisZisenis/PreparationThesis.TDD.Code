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
    void accept(CNVisitorPtr visitor) override {}
    };
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
};
#endif //CROSSVIEWS_PROPERTIESEXPLORERVIEW_TESTDOUBLES_H
