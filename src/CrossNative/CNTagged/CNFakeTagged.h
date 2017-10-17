#ifndef CROSSNATIVE_FAKETAGGED_H
#define CROSSNATIVE_FAKETAGGED_H

#include "CNTagged.h"

class CNFakeTagged;
typedef std::shared_ptr<CNFakeTagged> CNFakeTaggedPtr;

class CNFakeTagged : public CNTagged {
public:
    static CNFakeTaggedPtr getNewInstance(std::string tag) {
        return CNFakeTaggedPtr(new CNFakeTagged(tag));
    }
    virtual ~CNFakeTagged() {}
protected:
    CNFakeTagged(std::string tag) : tag(tag) {}

public:
    virtual std::string getTag() override {
        return tag;
    }

private:
    std::string tag;
};

#endif //CROSSNATIVE_FAKETAGGED_H
