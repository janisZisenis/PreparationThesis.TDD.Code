#ifndef CROSSNATIVE_TAGMATCHER_H
#define CROSSNATIVE_TAGMATCHER_H

#include <string>
#include <CrossNative/CrossNative_EXPORT.h>
#include "CNMatcher.h"

class CNVisitor;

class CNTagMatcher;
typedef std::shared_ptr<CNTagMatcher> CNTagMatcherPtr;

class CrossNative_EXPORT CNTagMatcher : public CNMatcher {
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
