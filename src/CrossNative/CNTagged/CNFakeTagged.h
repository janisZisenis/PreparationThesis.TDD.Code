#ifndef CROSSNATIVE_FAKETAGGED_H
#define CROSSNATIVE_FAKETAGGED_H

#include "CNTagged.h"
#include "CNTaggedVisitor.h"

class CNFakeTagged;
typedef std::shared_ptr<CNFakeTagged> CNFakeTaggedPtr;

class CNFakeTagged : public CNTagged, public std::enable_shared_from_this<CNTagged> {
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

    void accept(CNVisitorPtr visitor) override {
        CNTaggedVisitorPtr v = std::dynamic_pointer_cast<CNTaggedVisitor>(visitor);
        if(!v) throw CNVisitableVisitorMismatchException();
        v->visit(me());
    }

private:
    CNTaggedPtr me() {
        return this->shared_from_this();
    }

private:
    std::string tag;
};

#endif //CROSSNATIVE_FAKETAGGED_H
