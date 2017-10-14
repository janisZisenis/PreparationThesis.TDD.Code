#ifndef CROSSNATIVE_FAKECOMPONENT_H
#define CROSSNATIVE_FAKECOMPONENT_H

#include "CNComponent.h"

class CNFakeComponentVisitor;
typedef std::shared_ptr<CNFakeComponentVisitor> CNFakeComponentVisitorPtr;
class CNFakeComponent;
typedef std::shared_ptr<CNFakeComponent> CNFakeComponentPtr;

class CNFakeComponentVisitor : public CNVisitor {
public:
    virtual ~CNFakeComponentVisitor() {}
protected:
    CNFakeComponentVisitor() {}

public:
    virtual void visit(CNFakeComponentPtr fakeComponent) = 0;
};

class CNFakeComponent : public CNComponent, public std::enable_shared_from_this<CNFakeComponent> {
public:
    static CNFakeComponentPtr getNewInstance() {
        return CNFakeComponentPtr(new CNFakeComponent());
    }
    virtual ~CNFakeComponent() {};
protected:
    CNFakeComponent() {};

public:
    virtual void add(CNComponentPtr view) override {
        children.push_back(view);
    }
    virtual void remove(CNComponentPtr view) override {
        children.erase(std::find(children.begin(), children.end(), view));
    }
    virtual bool isParentOf(CNComponentPtr view) override {
        return std::find(children.begin(), children.end(), view) != children.end();
    }

    virtual void accept(CNVisitorPtr visitor) override {
        CNFakeComponentVisitorPtr v = std::dynamic_pointer_cast<CNFakeComponentVisitor>(visitor);
        if(!v) throw CNVisitorMismatchException();
        v->visit(me());
    }
private:
    CNFakeComponentPtr me() {
        return shared_from_this();
    }

private:
    std::vector<CNComponentPtr> children;
};


#endif //CROSSNATIVE_FAKECOMPONENT_H