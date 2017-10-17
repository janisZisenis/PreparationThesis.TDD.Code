#ifndef CROSSNATIVE_VISITINGMATCHER_H
#define CROSSNATIVE_VISITINGMATCHER_H

#include <CrossNative/CrossNative_EXPORT.h>
#include "CNMatcher.h"

class CNIdentifyingVisitor;

class CNVisitingMatcher;
typedef std::shared_ptr<CNVisitingMatcher> CNVisitingMatcherPtr;

class CrossNative_EXPORT CNVisitingMatcher : public CNMatcher {
public:
    static CNVisitingMatcherPtr getNewInstance(std::shared_ptr<CNIdentifyingVisitor> identifyingVisitor);
    virtual ~CNVisitingMatcher();
protected:
    CNVisitingMatcher(std::shared_ptr<CNIdentifyingVisitor> identifyingVisitor);

public:
    virtual bool matches(std::shared_ptr<CNVisitable> visitable) override;

private:
    std::shared_ptr<CNIdentifyingVisitor> identifyingVisitor;
};

#endif //CROSSNATIVE_VISITINGMATCHER_H
