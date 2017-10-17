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
};

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