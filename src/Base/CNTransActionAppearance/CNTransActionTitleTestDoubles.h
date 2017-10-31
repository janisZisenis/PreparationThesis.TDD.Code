#ifndef CROSSNATIVE_TRANSACTIONTITLE_TESTDOUBLES_H
#define CROSSNATIVE_TRANSACTIONTITLE_TESTDOUBLES_H

#include "CNTransActionTitle.h"

class CNTransActionTitleDummy;
typedef std::shared_ptr<CNTransActionTitleDummy> CNTransActionTitleDummyPtr;
class CNTransActionTitleDummy : public CNTransActionTitle {
public:
    static CNTransActionTitleDummyPtr getNewInstance() {
        return CNTransActionTitleDummyPtr(new CNTransActionTitleDummy());
    }
    virtual ~CNTransActionTitleDummy() {}
protected:
    CNTransActionTitleDummy() {}

public:
    virtual std::string getTitle() override { return ""; };
};

class CNTransActionTitleStub;
typedef std::shared_ptr<CNTransActionTitleStub> CNTransActionTitleStubPtr;
class CNTransActionTitleStub : public CNTransActionTitleDummy {
public:
    static CNTransActionTitleStubPtr getNewInstance() {
        return CNTransActionTitleStubPtr(new CNTransActionTitleStub());
    }
    virtual ~CNTransActionTitleStub() {}
protected:
    CNTransActionTitleStub() {}

public:
    virtual std::string getTitle() override { return title; };
    virtual void setTitle(std::string title) {
        this->title = title;
    }

private:
    std::string title;
};

#endif //CROSSNATIVE_TRANSACTIONTITLE_TESTDOUBLES_H