#ifndef CROSSNATIVE_HIERARCHY_H
#define CROSSNATIVE_HIERARCHY_H

#include <memory>

#include "CrossNative/CNHierarchyNode/CNComposableHierarchyNode.h"
#include "CNHierarchyIndex.h"

#include "CrossNative/CNIterator/Iterators/CNLevelOrderIterator.h"
#include "CrossNative/CNIterator/Iterators/CNPostOrderIterator.h"
#include "CrossNative/CNIterator/Iterators/CNPreOrderIterator.h"

#include "CNInvalidInsertingPositionException.h"
#include "CNInvalidChildPositionException.h"
#include "CrossNative/CNComponent/CNChildNotFoundException.h"
#include "CNIndexOutOfBoundsException.h"

enum TraversalOrder { PreOrder, PostOrder, LevelOrder };

class CNComponent;

class CNHierarchy;
typedef std::shared_ptr<CNHierarchy> CNHierarchyPtr;

class CNHierarchy {
public:
    static CNHierarchyPtr getNewInstance() {
        return CNHierarchyPtr(new CNHierarchy());
    }
    virtual ~CNHierarchy() {}
protected:
    CNHierarchy() {}

public:
    virtual CNIteratorPtr begin(TraversalOrder order = PreOrder) {
        return nullptr;
    }

    virtual void add(std::shared_ptr<CNComponent> component, CNHierarchyIndex parentIndex) {
//        findComponent(parentIndex)->add(makeComponent(content));
    }
    virtual void remove(std::shared_ptr<CNComponent> component, CNHierarchyIndex parentIndex) {
//        std::shared_ptr<CNComponent> parent = findComponent(parentIndex);
//
//        for(int i = 0; i < parent->getChildCount(); i++)
//            if(parent->getChild(i)->getContent() == content) {
//                parent->remove(parent->getChild(i));
//                break;
//            }
    }

    virtual void insert(std::shared_ptr<CNComponent> component, CNHierarchyIndex parentIndex, int childPos) {
//        findComponent(parentIndex)->insert(makeComponent(content), childPos);
    }
    virtual void remove(CNHierarchyIndex parentIndex, int childPos) {
//        ComponentPtr parent = findComponent(parentIndex);
//        parent->remove(parent->getChild(childPos));
    }

    virtual int getChildCountFor(CNHierarchyIndex index) {
//        return findComponent(index)->getChildCount();
        return 0;
    }
    virtual std::shared_ptr<CNComponent> retrieve(CNHierarchyIndex index) {
//        if(!index.isValid()) throw IndexOutOfBoundsException();
//        return findComponent(index)->getContent();
        return nullptr;
    }

private:
    virtual CNIteratorPtr makeIterator(TraversalOrder order) {
        if(order == PostOrder) return CNPostOrderIterator::getNewInstance(root);
        if(order == LevelOrder) return CNLevelOrderIterator::getNewInstance(root);
        return CNPreOrderIterator::getNewInstance(root);
    }
    virtual std::shared_ptr<CNComponent> findComponent(CNHierarchyIndex index) {
        std::shared_ptr<CNComponent> parent = root;

//        for(int i = 0; i < index.depth(); i++) {
//            if(index[i] >= parent->getChildCount()) throw CNIndexOutOfBoundsException();
//            parent = parent->getChild(index[i]);
//        }
//        return parent;
        return nullptr;
    };

    std::shared_ptr<CNComponent> root;
};

#endif //CROSSNATIVE_HIERARCHY_H
