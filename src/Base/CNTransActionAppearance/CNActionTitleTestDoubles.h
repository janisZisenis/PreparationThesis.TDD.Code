#ifndef CROSSNATIVE_ACTIONTITLE_TESTDOUBLES_H
#define CROSSNATIVE_ACTIONTITLE_TESTDOUBLES_H

#include "CNActionTitle.h"

class CNActionTitleDummy;
typedef std::shared_ptr<CNActionTitleDummy> CNActionTitleDummyPtr;
class CNActionTitleDummy : public CNActionTitle {
public:
    static CNActionTitleDummyPtr getNewInstance() {
        return CNActionTitleDummyPtr(new CNActionTitleDummy());
    }
    virtual ~CNActionTitleDummy() {}
protected:
    CNActionTitleDummy() {}

public:
    virtual std::string getTitle() override { return ""; };
};

class CNActionTitleStub;
typedef std::shared_ptr<CNActionTitleStub> CNActionTitleStubPtr;
class CNActionTitleStub : public CNActionTitleDummy {
public:
    static CNActionTitleStubPtr getNewInstance() {
        return CNActionTitleStubPtr(new CNActionTitleStub());
    }
    virtual ~CNActionTitleStub() {}
protected:
    CNActionTitleStub() {}

public:
    virtual std::string getTitle() override { return title; };
    virtual void setTitle(std::string title) {
        this->title = title;
    }

private:
    std::string title;
};

#endif //CROSSNATIVE_ACTIONTITLE_TESTDOUBLES_H