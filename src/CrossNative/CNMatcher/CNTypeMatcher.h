#ifndef CROSSNATIVE_VISITINGMATCHER_H
#define CROSSNATIVE_VISITINGMATCHER_H

#include <CrossNative/CrossNative_EXPORT.h>
#include "CNMatcher.h"

class CNVisitor;

class CNTypeMatcher;
typedef std::shared_ptr<CNTypeMatcher> CNTypeMatcherPtr;

class CrossNative_EXPORT CNTypeMatcher : public CNMatcher {
public:
    static CNTypeMatcherPtr getNewInstance(std::shared_ptr<CNVisitor> identifying);
    virtual ~CNTypeMatcher();
protected:
    CNTypeMatcher(std::shared_ptr<CNVisitor> identifying);

public:
    virtual bool matches(std::shared_ptr<CNComponent> component) override;
};

#endif //CROSSNATIVE_VISITINGMATCHER_H
