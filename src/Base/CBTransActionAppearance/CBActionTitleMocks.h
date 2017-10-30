#ifndef CODEBASE_ACTIONTITLE_MOCKS_H
#define CODEBASE_ACTIONTITLE_MOCKS_H

#include "CBActionTitle.h"

class CBActionTitleDummy;
typedef std::shared_ptr<CBActionTitleDummy> CBActionTitleDummyPtr;
class CBActionTitleDummy : public CBActionTitle {
public:
    static CBActionTitleDummyPtr getNewInstance() {
        return CBActionTitleDummyPtr(new CBActionTitleDummy());
    }
    virtual ~CBActionTitleDummy() {}
protected:
    CBActionTitleDummy() {}

public:
    virtual std::string getTitle() override { return ""; };
};

class CBActionTitleStub;
typedef std::shared_ptr<CBActionTitleStub> CBActionTitleStubPtr;
class CBActionTitleStub : public CBActionTitleDummy {
public:
    static CBActionTitleStubPtr getNewInstance() {
        return CBActionTitleStubPtr(new CBActionTitleStub());
    }
    virtual ~CBActionTitleStub() {}
protected:
    CBActionTitleStub() {}

public:
    virtual std::string getTitle() override { return title; };
    virtual void setTitle(std::string title) {
        this->title = title;
    }

private:
    std::string title;
};

#endif //CODEBASE_ACTIONTITLE_MOCKS_H