#ifndef CROSSNATIVE_GUILAYER_H
#define CROSSNATIVE_GUILAYER_H

#include <memory>
#include <vector>
#include <CrossNative/CrossNative_EXPORT.h>
#include <stack>

class CNView;
class CNIterator;
class CNMatcher;

class CNGuiLayer;
typedef std::shared_ptr<CNGuiLayer> CNGuiLayerPtr;

class CrossNative_EXPORT CNGuiLayer {
private:
    class PreOrderIterator;
    typedef std::shared_ptr<PreOrderIterator> PreOrderIteratorPtr;
    class PreOrderIterator {
    public:
        static PreOrderIteratorPtr getNewInstance(std::shared_ptr<CNView> root);
        virtual ~PreOrderIterator();
    private:
        PreOrderIterator(std::shared_ptr<CNView> root);

    public:
        virtual void first();
        virtual void next();
        virtual bool isDone();
        virtual std::shared_ptr<CNView> current();
    private:
        virtual void pushChildrenOf(std::shared_ptr<CNView> parent);
        virtual void moveCurrent();

    private:
        std::stack< std::shared_ptr<CNIterator> > iterators;
        std::shared_ptr<CNView> root;
    };

    virtual PreOrderIteratorPtr makeHierarchyIterator(std::shared_ptr<CNView> root);

public:
    static CNGuiLayerPtr getNewInstance();
    virtual ~CNGuiLayer();

protected:
    CNGuiLayer();

public:
    virtual void loadTopLevel(std::shared_ptr<CNView> view);
    virtual void load(std::shared_ptr<CNView> view, std::shared_ptr<CNMatcher> machter);

private:
    virtual std::shared_ptr<CNView> findMatchingViewInHierarchy(std::shared_ptr<CNMatcher> matcher,
                                                                std::shared_ptr<CNView> root);
    virtual std::shared_ptr<CNView> findMatchingView(std::shared_ptr<CNMatcher> matcher);
    virtual std::shared_ptr<CNView> findMatchingInChildren(std::shared_ptr<CNMatcher> matcher, std::shared_ptr<CNView> parent);
    virtual bool isMatching(std::shared_ptr<CNMatcher> matcher, std::shared_ptr<CNView> view);

private:
    std::vector< std::shared_ptr<CNView> > viewHierarchies;

    std::shared_ptr<CNView> pendingView;
};


#endif //CROSSNATIVE_GUILAYER_H