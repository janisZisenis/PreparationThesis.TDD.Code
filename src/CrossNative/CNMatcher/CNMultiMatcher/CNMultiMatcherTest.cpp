#include <gmock/gmock.h>
#include "CNMultiMatcher.h"
#include "CrossNative/CNMatcher/CNMatcherTestDoubles.h"
#include "CrossNative/CNVisitable/CNVisitableTestDoubles.h"

class CNMultiMatcherTest : public testing::Test {
protected:
    virtual CNMultiMatcherPtr makeCNMultiMatcher() {
        return CNMultiMatcher::getNewInstance();
    }

    virtual CNMatcherStubPtr makeCNMatcherStub() {
        return CNMatcherStub::getNewInstance();
    }

    virtual CNVisitablePtr makeCNVisitableDummy() {
        return CNVisitableDummy::getNewInstance();
    }

    virtual void expectDoesNotMatchVisitable(CNMultiMatcherPtr sut, CNVisitablePtr visitable) {
        bool expected = sut->matches(visitable);

        std::string errorMessage = "CNMultiMatcher should not match the CNVisitable, but it does!";
        EXPECT_FALSE(expected) << errorMessage;
    }
    virtual void expectMatchesVisitable(CNMultiMatcherPtr sut, CNVisitablePtr visitable) {
        bool expected = sut->matches(visitable);

        std::string errorMessage = "CNMultiMatcher should match the CNVisitable, but it does not!";
        EXPECT_TRUE(expected) << errorMessage;
    }
};

TEST_F(CNMultiMatcherTest, FreshInstance__ShouldNotMatchVisitable) {
    CNMultiMatcherPtr sut = makeCNMultiMatcher();

    CNVisitablePtr visitable = makeCNVisitableDummy();
    expectDoesNotMatchVisitable(sut, visitable);
}

TEST_F(CNMultiMatcherTest, FreshInstance__AddMatchingMatcher__ShouldMatchVisitable) {
    CNMultiMatcherPtr sut = makeCNMultiMatcher();

    CNMatcherStubPtr matcher = makeCNMatcherStub();
    matcher->setIsMatching(true);
    sut->add(matcher);

    CNVisitablePtr visitable = makeCNVisitableDummy();
    expectMatchesVisitable(sut, visitable);
}

TEST_F(CNMultiMatcherTest, AddedNotMatchingMatcher__AddMatchingMatcher__ShouldMatchVisitable) {
    CNMultiMatcherPtr sut = makeCNMultiMatcher();
    CNMatcherStubPtr notMatchingMatcher = makeCNMatcherStub();
    notMatchingMatcher->setIsMatching(false);
    sut->add(notMatchingMatcher);

    CNMatcherStubPtr matchingMatcher = makeCNMatcherStub();
    matchingMatcher->setIsMatching(true);
    sut->add(matchingMatcher);

    CNVisitablePtr visitable = makeCNVisitableDummy();
    expectMatchesVisitable(sut, visitable);
}