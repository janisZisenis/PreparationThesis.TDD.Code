#ifndef CROSSNATIVE_VISITINGMATCHER_H
#define CROSSNATIVE_VISITINGMATCHER_H

#include <CrossNative/CrossNative_EXPORT.h>
#include "CNMatcher.h"

class CNVisitor;

class CNTypeMatcher;
typedef std::shared_ptr<CNTypeMatcher> CNTypeMatcherPtr;

class CrossNative_EXPORT CNTypeMatcher : public CNMatcher {
public:
    static CNTypeMatcherPtr getNewInstance(std::shared_ptr<CNVisitor> matching);
    virtual ~CNTypeMatcher();
protected:
    CNTypeMatcher(std::shared_ptr<CNVisitor> matching);

public:
    virtual bool matches(std::shared_ptr<CNComponent> component) override;

private:
    std::shared_ptr<CNVisitor> matching;
};

#endif //CROSSNATIVE_VISITINGMATCHER_H
