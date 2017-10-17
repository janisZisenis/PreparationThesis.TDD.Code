#ifndef CROSSNATIVE_TAGMATCHER_H
#define CROSSNATIVE_TAGMATCHER_H

#include <string>
#include <CrossNative/CrossNative_EXPORT.h>
#include <CrossNative/CNTagged/CNTaggedVisitor.h>
#include "CNIdentifyingVisitor.h"
#include "CrossNative/CNMatcher/CNMatcher.h"

class CNTagMatcher;
typedef std::shared_ptr<CNTagMatcher> CNTagMatcherPtr;

class CrossNative_EXPORT CNTagMatcher : public CNMatcher {
private:
    class CNTagIdentifier;
    typedef std::shared_ptr<CNTagIdentifier> CNTagIdentifierPtr;
    class CNTagIdentifier : public CNIdentifyingVisitor, public CNTaggedVisitor {
    public:
        static CNTagIdentifierPtr getNewInstance(std::string tag);
        virtual ~CNTagIdentifier();
    private:
        CNTagIdentifier(std::string tag);

    public:
        virtual void visit(std::shared_ptr<CNTagged> tagged) override;
        virtual bool hasIdentified() override;

    private:
        std::string identifiedTag;
        std::string tag;
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
    CNIdentifyingVisitorPtr visitor;
};

#endif //CROSSNATIVE_TAGMATCHER_H
