#ifndef CROSSNATIVE_MENUENTRYVIEW_TESTDOUBLES_H
#define CROSSNATIVE_MENUENTRYVIEW_TESTDOUBLES_H

#include "CNMenuEntryView.h"

class CNMenuEntryViewDummy;
typedef std::shared_ptr<CNMenuEntryViewDummy> CNMenuEntryViewDummyPtr;
class CNMenuEntryViewDummy : public CNMenuEntryView {
public:
    static CNMenuEntryViewDummyPtr getNewInstance() {
        return CNMenuEntryViewDummyPtr(new CNMenuEntryViewDummy());
    }
    virtual ~CNMenuEntryViewDummy() {}
protected:
    CNMenuEntryViewDummy() {}

public:
    virtual void setTitle(std::string title) override {}
    virtual void accept(CNVisitorPtr visitor) override {}
    virtual void setListener(std::shared_ptr<CNMenuEntryListener> listener) override {}

    virtual void check() override {}
    virtual void uncheck() override {}

    virtual void enable() override {}
    virtual void disable() override {}
};

class CNMenuEntryViewSpy;
typedef std::shared_ptr<CNMenuEntryViewSpy> CNMenuEntryViewSpyPtr;
class CNMenuEntryViewSpy : public CNMenuEntryViewDummy {
public:
    static CNMenuEntryViewSpyPtr getNewInstance() {
        return CNMenuEntryViewSpyPtr(new CNMenuEntryViewSpy());
    }
    virtual ~CNMenuEntryViewSpy() {}
protected:
    CNMenuEntryViewSpy() {}

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
    CNTransActionStateValues newState = OFF;
    std::string newTitle = std::string();
    CNVisitorPtr accepted;
};

#endif //CROSSNATIVE_MENUENTRYVIEW_TESTDOUBLES_H
