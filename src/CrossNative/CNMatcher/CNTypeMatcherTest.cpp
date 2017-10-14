#include <gmock/gmock.h>
#include "CNTypeMatcher.h"

#include "CrossNative/CNVisitor/CNVisitorTestDoubles.h"
#include "CrossNative/CNVisitable/CNVisitableTestDoubles.h"

class CNTypeMatcherTest : public testing::Test {
protected:
    virtual CNTypeMatcherPtr makeCNTypeMatcher(CNVisitorPtr matching) {
        return CNTypeMatcher::getNewInstance(matching);
    }
    virtual CNVisitorPtr makeCNVisitorDummy() {
        return CNVisitorDummy::getNewInstance();
    }
    virtual CNVisitableSpyPtr makeCNVisitableSpy() {
        return CNVisitableSpy::getNewInstance();
    }

    virtual void expectVisitableHasAcceptedVisitor(CNVisitableSpyPtr visitable, CNVisitorPtr visitor) {
        CNVisitorPtr expected = visitable->getAccepted();
        CNVisitorPtr actual = visitor;

        std::string errorMessage = "The visitable should have accepted the visitor, but it has not!";
        EXPECT_THAT(actual, testing::Eq(expected)) << errorMessage;
    }
};

TEST_F(CNTypeMatcherTest, FreshInstance__Matches__VisitableShouldHaveAcceptedTheMatchingVisitor) {
    CNVisitorPtr matching = makeCNVisitorDummy();
    CNTypeMatcherPtr sut = makeCNTypeMatcher(matching);

    CNVisitableSpyPtr visitable = makeCNVisitableSpy();
    sut->matches(visitable);

    expectVisitableHasAcceptedVisitor(visitable, matching);
}
