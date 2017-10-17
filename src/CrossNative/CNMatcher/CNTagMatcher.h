#ifndef CROSSNATIVE_TAGMATCHER_H
#define CROSSNATIVE_TAGMATCHER_H

#include <CrossNative/CrossNative_EXPORT.h>
#include "CNMatcher.h"

class CNVisitor;

class CNTagMatcher;
typedef std::shared_ptr<CNTagMatcher> CNTagMatcherPtr;

class CrossNative_EXPORT CNTagMatcher : public CNMatcher {
public:
    static CNTagMatcherPtr getNewInstance();
    virtual ~CNTagMatcher();
protected:
    CNTagMatcher();

public:
    virtual bool matches(std::shared_ptr<CNVisitable> visitable) override;
};

#endif //CROSSNATIVE_TAGMATCHER_H
