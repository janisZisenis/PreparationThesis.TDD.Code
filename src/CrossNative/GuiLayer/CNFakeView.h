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

        }
        void next() override {
            throw CNNotInitializedIteratorException();
        }
        bool isDone() override {
            return false;
        }
        CNViewPtr current() override {
            throw CNNotInitializedIteratorException();
            return nullptr;
        }
    private:
        std::vector<CNViewPtr> views;
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