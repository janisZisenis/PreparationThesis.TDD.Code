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
    virtual void setTitle(std::string title) override {}
    virtual void accept(CNVisitorPtr visitor) override {}
    virtual void setListener(std::shared_ptr<MenuEntryListener> listener) override {}

    virtual void check() override {}
    virtual void uncheck() override {}

    virtual void enable() override {}
    virtual void disable() override {}
};

class MenuEntryViewSpy;
typedef std::shared_ptr<MenuEntryViewSpy> MenuEntryViewSpyPtr;
class MenuEntryViewSpy : public MenuEntryViewDummy {
public:
    static MenuEntryViewSpyPtr getNewInstance() {
        return MenuEntryViewSpyPtr(new MenuEntryViewSpy());
    }
    virtual ~MenuEntryViewSpy() {}
protected:
    MenuEntryViewSpy() {}

public:
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

    virtual void enable() override {
        enabled = true;
    }
    virtual bool wasEnabled() {
        return enabled;
    }

    virtual void disable() override {
        disabled = true;
    }
    virtual bool wasDisabled() {
        return disabled;
    }


private:
    bool checked = false;
    bool unchecked = false;

    bool enabled = false;
    bool disabled = false;

    bool newAccessbility = false;
    CBActionStates newState = OFF;
    std::string newTitle = std::string();
    CNVisitorPtr accepted;
};

#endif //CROSSVIEWS_MENUENTRYVIEW_TESTDOUBLES_H
