#ifndef CROSSNATIVE_FAKEHIERARCHYNODE_H
#define CROSSNATIVE_FAKEHIERARCHYNODE_H

#include "CNHierarchyNode.h"
#include <vector>

class CNFakeHierarchyNodeVisitor;
typedef std::shared_ptr<CNFakeHierarchyNodeVisitor> CNFakeHierarchyNodeVisitorPtr;
class CNFakeHierarchyNode;
typedef std::shared_ptr<CNFakeHierarchyNode> CNFakeHierarchyNodePtr;

class CNFakeHierarchyNodeVisitor {
public:
    virtual ~CNFakeHierarchyNodeVisitor() {}
protected:
    CNFakeHierarchyNodeVisitor() {}

public:
    virtual void visit(CNFakeHierarchyNodePtr fakeHierarchyNode) = 0;
};

class CNFakeHierarchyNode : public CNHierarchyNode, public std::enable_shared_from_this<CNFakeHierarchyNode> {
public:
    static CNFakeHierarchyNodePtr getNewInstance() {
        return CNFakeHierarchyNodePtr(new CNFakeHierarchyNode());
    }
    virtual  ~CNFakeHierarchyNode() {}

protected:
    CNFakeHierarchyNode() {}

public:
    virtual bool isParentOf(CNHierarchyNodePtr node) override {
        return findPosition(node) > -1;
    }
    virtual int getChildCount() override {
        return (int)children.size();
    }
    virtual CNHierarchyNodePtr getChild(int childPos) override {
        if(!isValidChildPosition(childPos))
            throw CNInvalidChildPositionException();

        return children[childPos];
    }

    virtual void add(std::shared_ptr<CNHierarchyNode> node) override {
        addToChildren(node);
    }
    virtual void remove(std::shared_ptr<CNHierarchyNode> node) override {
        if(!isParentOf(node))
            throw CNChildNotFoundException();

        removeFromChildren(findPosition(node));
    }
    virtual void insert(std::shared_ptr<CNHierarchyNode> node, int childPos) override {
        if(!isValidInsertingPosition(childPos))
            throw CNInvalidInsertingPositionException();

        insertToChildren(node, childPos);
    }
    virtual void remove(int childPos) override {
        if(!isValidChildPosition(childPos))
            throw CNInvalidChildPositionException();

        removeFromChildren(childPos);
    }

    virtual void accept(CNVisitorPtr visitor) override {
        CNFakeHierarchyNodeVisitorPtr v = std::dynamic_pointer_cast<CNFakeHierarchyNodeVisitor>(visitor);
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
    virtual void addToChildren(CNHierarchyNodePtr node) {
        children.push_back(node);
    }
    virtual void insertToChildren(CNHierarchyNodePtr node, int childPos) {
        children.insert(children.begin()+ childPos, node);
    }
    virtual void removeFromChildren(int childPos) {
        children.erase(children.begin() + childPos);
    }
    virtual int findPosition(CNHierarchyNodePtr node) {
        std::vector<CNHierarchyNodePtr>::iterator it;
        it = std::find(children.begin(), children.end(), node);
        return it == children.end() ? -1 : (int)(it - children.begin());
    }

    virtual CNFakeHierarchyNodePtr me() {
        return this->shared_from_this();
    }
private:
    std::vector<CNHierarchyNodePtr> children;
};

class CNFakeHierarchyNodeVisitorSpy;
typedef std::shared_ptr<CNFakeHierarchyNodeVisitorSpy> CNFakeHierarchyNodeVisitorSpyPtr;
class CNFakeHierarchyNodeVisitorSpy : public CNVisitor, public CNFakeHierarchyNodeVisitor {
public:
    static CNFakeHierarchyNodeVisitorSpyPtr getNewInstance() {
        return CNFakeHierarchyNodeVisitorSpyPtr(new CNFakeHierarchyNodeVisitorSpy());
    }
    virtual ~CNFakeHierarchyNodeVisitorSpy() {}
protected:
    CNFakeHierarchyNodeVisitorSpy() {}
public:
    void visit(CNFakeHierarchyNodePtr fakeHierarchyNode) override {
        visited = fakeHierarchyNode;
    }
    virtual CNFakeHierarchyNodePtr getVisited() {
        return visited;
    }

private:
    CNFakeHierarchyNodePtr visited;
};

#endif //CROSSNATIVE_FAKEHIERARCHYNODE_H