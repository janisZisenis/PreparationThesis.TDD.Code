#ifndef CROSSNATIVE_TAGMATCHER_H
#define CROSSNATIVE_TAGMATCHER_H

#include <string>
#include <CrossNative/CrossNative_EXPORT.h>
#include <CrossNative/CNTagged/CNTaggedVisitor.h>
#include <CrossNative/CNVisitor/CNVisitor.h>
#include "CrossNative/CNMatcher/CNMatcher.h"

class CNTagMatcher;
typedef std::shared_ptr<CNTagMatcher> CNTagMatcherPtr;

class CrossNative_EXPORT CNTagMatcher : public CNMatcher {
private:
    class CNTagIdentifier;
    typedef std::shared_ptr<CNTagIdentifier> CNTagIdentifierPtr;
    class CNTagIdentifier : public CNVisitor, public CNTaggedVisitor {
    public:
        static CNTagIdentifierPtr getNewInstance();
        virtual ~CNTagIdentifier();
    private:
        CNTagIdentifier();

    public:
        virtual void visit(std::shared_ptr<CNTagged> tagged) override;
        virtual std::string getIdentifiedTag();

    private:
        std::string identifiedTag;
    };

public:
    static CNTagMatcherPtr getNewInstance(std::string tag);
    virtual ~CNTagMatcher();
protected:
    CNTagMatcher(std::string tag);

public:
    virtual bool matches(std::shared_ptr<CNVisitable> visitable) override;

private:
    std::string tag;
};

#endif //CROSSNATIVE_TAGMATCHER_H
