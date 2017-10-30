#ifndef CROSSNATIVE_TRANSACTIONAPPEARANCE_TESTDOUBLES_H
#define CROSSNATIVE_TRANSACTIONAPPEARANCE_TESTDOUBLES_H

#include "CNTransActionAppearance.h"

class CNTransActionAppearanceDummy;
typedef std::shared_ptr<CNTransActionAppearanceDummy> CNTransActionAppearanceDummyPtr;
class CNTransActionAppearanceDummy : public CNTransActionAppearance {
public:
    static CNTransActionAppearanceDummyPtr getNewInstance() {
        return CNTransActionAppearanceDummyPtr(new CNTransActionAppearanceDummy());
    }
    virtual ~CNTransActionAppearanceDummy() {};
protected:
    CNTransActionAppearanceDummy() {};

public:
    virtual bool isAccessible() override {
        return false;
    }
    virtual CNActionStates getState() override {
        return OFF;
    }
    virtual std::string getTitle() override {
        return std::string();
    }
};


class CNTransActionAppearanceStub;
typedef std::shared_ptr<CNTransActionAppearanceStub> CNTransActionAppearanceStubPtr;
class CNTransActionAppearanceStub : public CNTransActionAppearanceDummy {
public:
    static CNTransActionAppearanceStubPtr getNewInstance() {
        return CNTransActionAppearanceStubPtr(new CNTransActionAppearanceStub());
    }
    virtual ~CNTransActionAppearanceStub() {};
protected:
    CNTransActionAppearanceStub() {};

public:
    virtual void setIsAccessible(bool accessible) {
        this->accessible = accessible;
    }
    virtual bool isAccessible() override {
        return accessible;
    }

    virtual void setState(CNActionStates state) {
        this->state = state;
    }
    virtual CNActionStates getState() override {
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
    CNActionStates state = OFF;
    std::string title = std::string();
};

#endif //CROSSNATIVE_TRANSACTIONAPPEARANCE_TESTDOUBLES_H