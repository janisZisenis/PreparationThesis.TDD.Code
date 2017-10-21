#ifndef CROSSNATIVE_FAKECOMPONENT_H
#define CROSSNATIVE_FAKECOMPONENT_H

#include "CNComponent.h"
#include <vector>

class CNFakeComponentVisitor;
typedef std::shared_ptr<CNFakeComponentVisitor> CNFakeComponentVisitorPtr;
class CNFakeComponent;
typedef std::shared_ptr<CNFakeComponent> CNFakeComponentPtr;

class CNFakeComponentVisitor {
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
    virtual  ~CNFakeComponent() {}

protected:
    CNFakeComponent() {}

public:
    virtual bool isParentOf(CNComponentPtr component) override {
        return findPosition(component) > -1;
    }
    virtual int getChildCount() override {
        return (int)children.size();
    }
    virtual CNComponentPtr getChild(int childPos) override {
        if(!isValidChildPosition(childPos))
            throw CNInvalidChildPositionException();

        return children[childPos];
    }

    virtual void add(std::shared_ptr<CNComponent> component) override {
        addToChildren(component);
    }
    virtual void remove(std::shared_ptr<CNComponent> component) override {
        if(!isParentOf(component))
            throw CNChildNotFoundException();

        removeFromChildren(findPosition(component));
    }
    virtual void insert(std::shared_ptr<CNComponent> component, int childPos) override {
        if(!isValidInsertingPosition(childPos))
            throw CNInvalidInsertingPositionException();

        insertToChildren(component, childPos);
    }
    virtual void remove(int childPos) override {
        if(!isValidChildPosition(childPos))
            throw CNInvalidChildPositionException();

        removeFromChildren(childPos);
    }

    virtual void accept(CNVisitorPtr visitor) override {
        CNFakeComponentVisitorPtr v = std::dynamic_pointer_cast<CNFakeComponentVisitor>(visitor);
        if(!v) throw CNVisitableVisitorMismatchException();
        v->visit(me());
    }
private:
    virtual bool isValidInsertingPosition(int childPos) {
        return childPos <= children.size();
    }
    virtual bool isValidChildPosition(int childPos) {
        return childPos < children.size();
    }
    virtual void addToChildren(CNComponentPtr component) {
        children.push_back(component);
    }
    virtual void insertToChildren(CNComponentPtr component, int childPos) {
        children.insert(children.begin()+ childPos, component);
    }
    virtual void removeFromChildren(int childPos) {
        children.erase(children.begin() + childPos);
    }
    virtual int findPosition(CNComponentPtr component) {
        std::vector<CNComponentPtr>::iterator it;
        it = std::find(children.begin(), children.end(), component);
        return it == children.end() ? -1 : (int)(it - children.begin());
    }

    virtual CNFakeComponentPtr me() {
        return this->shared_from_this();
    }
private:
    std::vector<CNComponentPtr> children;
};

class CNFakeComponentVisitorSpy;
typedef std::shared_ptr<CNFakeComponentVisitorSpy> CNFakeComponentVisitorSpyPtr;
class CNFakeComponentVisitorSpy : public CNVisitor, public CNFakeComponentVisitor {
public:
    static CNFakeComponentVisitorSpyPtr getNewInstance() {
        return CNFakeComponentVisitorSpyPtr(new CNFakeComponentVisitorSpy());
    }
    virtual ~CNFakeComponentVisitorSpy() {}
protected:
    CNFakeComponentVisitorSpy() {}
public:
    void visit(CNFakeComponentPtr fakeComponent) override {
        visited = fakeComponent;
    }
    virtual CNFakeComponentPtr getVisited() {
        return visited;
    }

private:
    CNFakeComponentPtr visited;
};

#endif //CROSSNATIVE_FAKECOMPONENT_H