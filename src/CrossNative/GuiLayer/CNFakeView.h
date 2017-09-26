#ifndef CROSSNATIVE_FAKEVIEW_H
#define CROSSNATIVE_FAKEVIEW_H

#include "CNView.h"
#include "CNIterator.h"

class CNFakeView;
typedef std::shared_ptr<CNFakeView> CNFakeViewPtr;

class CNFakeView : public CNView {
private:
    class Iterator;
    typedef std::shared_ptr<Iterator> IteratorPtr;
    class Iterator : public CNIterator {
    public:
        static IteratorPtr getNewInstance(std::vector<CNViewPtr> views) {
            return IteratorPtr(new Iterator(views));
        }
        virtual ~Iterator() {}
    private:
        Iterator(std::vector<CNViewPtr> views) : views(views) {}

    public:
        void first() override {
            initialized = true;

            it = views.begin();
        }
        void next() override {
            if(!initialized) throw CNNotInitializedIteratorException();

            it++;
        }
        bool isDone() override {
            if(!initialized) throw CNNotInitializedIteratorException();

            return false;
        }
        CNViewPtr current() override {
            if(!initialized) throw CNNotInitializedIteratorException();
            if(it >= views.end()) throw CNNotIteratorOutOfBoundsException();

            return it >= views.end() ? nullptr : *it;
        }
    private:
        bool initialized = false;
        std::vector<CNViewPtr> views;
        std::vector<CNViewPtr>::iterator it;
    };

public:
    static CNFakeViewPtr getNewInstance() {
        return CNFakeViewPtr(new CNFakeView());
    }
    virtual ~CNFakeView() {};
protected:
    CNFakeView() {};

public:
    virtual void add(CNViewPtr view) {
        children.push_back(view);
    }

    virtual CNViewPtr getChild(int position) {
        return nullptr;
    }
    virtual int getChildCount() {
        return 0;
    }
    virtual CNIteratorPtr makeIterator() {
        return Iterator::getNewInstance(children);
    }

private:
    std::vector<CNViewPtr> children;
};


#endif //CROSSNATIVE_FAKEVIEW_H