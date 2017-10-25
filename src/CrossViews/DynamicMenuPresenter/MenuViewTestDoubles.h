#ifndef CROSSVIEWS_MENUVIEW_TESTDOUBLES_H
#define CROSSVIEWS_MENUVIEW_TESTDOUBLES_H

#include "MenuView.h"

class MenuViewDummy;
typedef std::shared_ptr<MenuViewDummy> MenuViewDummyPtr;
class MenuViewDummy : public MenuView {
public:
    static MenuViewDummyPtr getNewInstance() {
        return MenuViewDummyPtr(new MenuViewDummy());
    }
    virtual ~MenuViewDummy() {}
protected:
    MenuViewDummy() {}

public:
    virtual void accept(CNVisitorPtr accept) override {}
};

class MenuViewSpy;
typedef std::shared_ptr<MenuViewSpy> MenuViewSpyPtr;
class MenuViewSpy : public MenuViewDummy {
public:
    static MenuViewSpyPtr getNewInstance() {
        return MenuViewSpyPtr(new MenuViewSpy());
    }
    virtual ~MenuViewSpy() {}
protected:
    MenuViewSpy() {}

public:
    virtual void accept(CNVisitorPtr visitor) override {
        accepted = visitor;
    }
    virtual CNVisitorPtr getAccepted() {
        return accepted;
    }

private:
    CNVisitorPtr accepted;
};

#endif //CROSSVIEWS_MENUVIEW_TESTDOUBLES_H
