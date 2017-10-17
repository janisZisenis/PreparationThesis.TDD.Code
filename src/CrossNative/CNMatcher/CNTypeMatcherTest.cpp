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
    virtual CNVisitableDummyPtr makeCNVisitableDummy() {
        return CNVisitableDummy::getNewInstance();
    }
    virtual CNVisitableSpyPtr makeCNVisitableSpy() {
        return CNVisitableSpy::getNewInstance();
    }
    virtual CNVisitablePtr makeCNVisitableSaboteur() {
        return CNVisitableSaboteur::getNewInstance();
    }

    virtual void expectVisitableHasAcceptedVisitor(CNVisitableSpyPtr visitable, CNVisitorPtr visitor) {
        CNVisitorPtr expected = visitable->getAccepted();
        CNVisitorPtr actual = visitor;

        std::string errorMessage = "The visitable should have accepted the visitor, but it has not!";
        EXPECT_THAT(actual, testing::Eq(expected)) << errorMessage;
    }
    virtual void expectMatcherDoesNotMatchVisitable(CNTypeMatcherPtr sut, CNVisitablePtr visitable) {
        bool actual = sut->matches(visitable);

        std::string errorMessage = "CNTypeMatcher should not match the visitable, but it does!";
        EXPECT_FALSE(actual) << errorMessage;
    }
    virtual void expectMatcherMatchesVisitable(CNTypeMatcherPtr sut, CNVisitablePtr visitable) {
        bool actual = sut->matches(visitable);

        std::string errorMessage = "CNTypeMatcher should match the visitable, but it does not!";
        EXPECT_TRUE(actual) << errorMessage;
    }
};

TEST_F(CNTypeMatcherTest, FreshInstance__Matches__VisitableShouldHaveAcceptedTheVisitor) {
    CNVisitorPtr matching = makeCNVisitorDummy();
    CNTypeMatcherPtr sut = makeCNTypeMatcher(matching);

    CNVisitableSpyPtr visitable = makeCNVisitableSpy();
    sut->matches(visitable);

    expectVisitableHasAcceptedVisitor(visitable, matching);
}

TEST_F(CNTypeMatcherTest, FreshInstance__MatchesVisitableSaboteur__SUTShouldNotMatch) {
    CNVisitorPtr matching = makeCNVisitorDummy();
    CNTypeMatcherPtr sut = makeCNTypeMatcher(matching);

    CNVisitablePtr visitable = makeCNVisitableSaboteur();

    expectMatcherDoesNotMatchVisitable(sut, visitable);
}

TEST_F(CNTypeMatcherTest, FreshInstance__MatchesVisitable__SUTShouldMatch) {
    CNVisitorPtr matching = makeCNVisitorDummy();
    CNTypeMatcherPtr sut = makeCNTypeMatcher(matching);

    CNVisitablePtr visitable = makeCNVisitableDummy();

    expectMatcherMatchesVisitable(sut, visitable);
}