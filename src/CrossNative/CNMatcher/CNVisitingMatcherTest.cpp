#include <gmock/gmock.h>
#include "CNVisitingMatcher.h"

#include "CNIdentifyingVisitorTestDoubles.h"
#include "CrossNative/CNVisitable/CNVisitableTestDoubles.h"


class CNVisitingMatcherTest : public testing::Test {
protected:
    virtual CNVisitingMatcherPtr makeCNVistingMatcher(CNIdentifyingVisitorPtr identifyingVisitor) {
        return CNVisitingMatcher::getNewInstance(identifyingVisitor);
    }
    virtual CNIdentifyingVisitorPtr makeCNIdentifyingVisitorDummy() {
        return CNIdentifyingVisitorDummy::getNewInstance();
    }
    virtual CNIdentifyingVisitorStubPtr makeCNIdentifyingVisitorStub() {
        return CNIdentifyingVisitorStub::getNewInstance();
    }
    virtual CNVisitablePtr makeCNVisitableDummy() {
        return CNVisitableDummy::getNewInstance();
    }
    virtual CNVisitableSpyPtr makeCNVisitableSpy() {
        return CNVisitableSpy::getNewInstance();
    }

    virtual void expectMatcherMatchesVisitable(CNVisitingMatcherPtr sut, CNVisitablePtr visitable) {
        bool actual = sut->matches(visitable);

        std::string errorMessage = "CNMatcher should match the CNVisitable, but it does not!";
        EXPECT_TRUE(actual) << errorMessage;
    }
    virtual void expectMatcherDoesNotMatchVisitable(CNVisitingMatcherPtr sut, CNVisitablePtr visitable) {
        bool actual = sut->matches(visitable);

        std::string errorMessage = "CNMatcher should not match the CNVisitable, but it does!";
        EXPECT_FALSE(actual) << errorMessage;
    }

    virtual void expectVisitableHasAcceptedVisitor(CNVisitableSpyPtr visitable, CNVisitorPtr visitor) {
        CNVisitorPtr expected = visitor;
        CNVisitorPtr actual = visitable->getAccepted();

        std::string errorMessage = "The CNVisitable should have accepted the CNVisitor, but it has not!";
        EXPECT_THAT(actual, testing::Eq(expected)) << errorMessage;
    }
};

TEST_F(CNVisitingMatcherTest, FreshInstance__MatchesVisitable__VisitableShouldHaveAcceptedTheVisitor) {
    CNIdentifyingVisitorPtr visitor = makeCNIdentifyingVisitorDummy();
    CNVisitingMatcherPtr sut = makeCNVistingMatcher(visitor);

    CNVisitableSpyPtr visitable = makeCNVisitableSpy();
    sut->matches(visitable);

    expectVisitableHasAcceptedVisitor(visitable, visitor);
}

TEST_F(CNVisitingMatcherTest, FreshInstance__VisitorDoesNotIdentifyVisitable__MatcherShouldNotMatchVisitable) {
    CNIdentifyingVisitorStubPtr visitor = makeCNIdentifyingVisitorStub();
    visitor->setIdentified(false);
    CNVisitingMatcherPtr sut = makeCNVistingMatcher(visitor);

    CNVisitablePtr visitable = makeCNVisitableDummy();

    expectMatcherDoesNotMatchVisitable(sut, visitable);
}

TEST_F(CNVisitingMatcherTest, FreshInstance__VisitorIdentifiesVisitable__MatcherShouldMatchVisitable) {
    CNIdentifyingVisitorStubPtr visitor = makeCNIdentifyingVisitorStub();
    visitor->setIdentified(true);
    CNVisitingMatcherPtr sut = makeCNVistingMatcher(visitor);

    CNVisitablePtr visitable = makeCNVisitableDummy();

    expectMatcherMatchesVisitable(sut, visitable);
}