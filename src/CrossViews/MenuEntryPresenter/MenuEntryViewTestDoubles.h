#ifndef CROSSVIEWS_MENUENTRYVIEW_TESTDOUBLES_H
#define CROSSVIEWS_MENUENTRYVIEW_TESTDOUBLES_H

#include "MenuEntryView.h"

class MenuEntryViewDummy;
typedef std::shared_ptr<MenuEntryViewDummy> MenuEntryViewDummyPtr;
class MenuEntryViewDummy : public MenuEntryView {
public:
    static MenuEntryViewDummyPtr getNewInstance() {
        return MenuEntryViewDummyPtr(new MenuEntryViewDummy());
    }
    virtual ~MenuEntryViewDummy() {}
protected:
    MenuEntryViewDummy() {}

public:
    virtual void setAccessibility(bool newAccessibility) override {}
    virtual void setState(CBActionStates newState) override {}
    virtual void setTitle(std::string title) override {}
    virtual void accept(CNVisitorPtr visitor) override {}

    virtual void check() override {}
    virtual void uncheck() override {}
};

class MenuEntryViewSpy;
typedef std::shared_ptr<MenuEntryViewSpy> MenuEntryViewSpyPtr;
class MenuEntryViewSpy : public MenuEntryView {
public:
    static MenuEntryViewSpyPtr getNewInstance() {
        return MenuEntryViewSpyPtr(new MenuEntryViewSpy());
    }
    virtual ~MenuEntryViewSpy() {}
protected:
    MenuEntryViewSpy() {}

public:
    virtual void setAccessibility(bool newAccessibility) override {
        this->newAccessbility = newAccessibility;
    }
    virtual bool getNewAccessibility() {
        return newAccessbility;
    }

    virtual void setState(CBActionStates newState) override {
        this->newState = newState;
    }
    virtual CBActionStates getNewState() {
        return newState;
    }

    virtual void setTitle(std::string newTitle) override {
        this->newTitle = newTitle;
    }
    virtual std::string getNewTitle() {
        return newTitle;
    }

    virtual void accept(CNVisitorPtr visitor) override {
        accepted = visitor;
    }
    virtual CNVisitorPtr getAccepted() {
        return accepted;
    }

    virtual void check() override {
        checked = true;
    }
    virtual bool wasChecked() {
        return checked;
    }

    virtual void uncheck() override {
        unchecked = true;
    }
    virtual bool wasUnchecked() {
        return unchecked;
    }


private:
    bool checked = false;
    bool unchecked = false;

    bool newAccessbility = false;
    CBActionStates newState = OFF;
    std::string newTitle = std::string();
    CNVisitorPtr accepted;
};

#endif //CROSSVIEWS_MENUENTRYVIEW_TESTDOUBLES_H