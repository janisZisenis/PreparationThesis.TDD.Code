#ifndef CODEBASE_TRANSACTIONAPPEARANCE_TESTDOUBLES_H
#define CODEBASE_TRANSACTIONAPPEARANCE_TESTDOUBLES_H

#include "CBTransActionAppearance.h"

class CBTransActionAppearanceDummy;
typedef std::shared_ptr<CBTransActionAppearanceDummy> CBTransActionAppearanceDummyPtr;
class CBTransActionAppearanceDummy : public CBTransActionAppearance {
public:
    static CBTransActionAppearanceDummyPtr getNewInstance() {
        return CBTransActionAppearanceDummyPtr(new CBTransActionAppearanceDummy());
    }
    virtual ~CBTransActionAppearanceDummy() {};
protected:
    CBTransActionAppearanceDummy() {};

public:
    virtual bool isAccessible() override {
        return false;
    }
    virtual CBActionStates getState() override {
        return OFF;
    }
    virtual std::string getTitle() override {
        return std::string();
    }
};


class CBTransActionAppearanceStub;
typedef std::shared_ptr<CBTransActionAppearanceStub> CBTransActionAppearanceStubPtr;
class CBTransActionAppearanceStub : public CBTransActionAppearanceDummy {
public:
    static CBTransActionAppearanceStubPtr getNewInstance() {
        return CBTransActionAppearanceStubPtr(new CBTransActionAppearanceStub());
    }
    virtual ~CBTransActionAppearanceStub() {};
protected:
    CBTransActionAppearanceStub() {};

public:
    virtual void setIsAccessible(bool accessible) {
        this->accessible = accessible;
    }
    virtual bool isAccessible() override {
        return accessible;
    }

    virtual void setState(CBActionStates state) {
        this->state = state;
    }
    virtual CBActionStates getState() override {
        return state;
    }

    virtual void setTitle(std::string title) {
        this->title = title;
    }
    virtual std::string getTitle() override {
        return title;
    }

private:
    bool accessible = false;
    CBActionStates state = OFF;
    std::string title = std::string();
};

#endif //CODEBASE_TRANSACTIONAPPEARANCE_TESTDOUBLES_H