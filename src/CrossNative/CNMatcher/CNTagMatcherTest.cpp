#include <gmock/gmock.h>
#include "CNTagMatcher.h"

#include "CrossNative/CNTagged/CNFakeTagged.h"
#include "CrossNative/CNVisitable/CNVisitableTestDoubles.h"


class CNTagMatcherTest : public testing::Test {
protected:
    virtual CNTagMatcherPtr makeCNTagMatcher(std::string tag) {
        return CNTagMatcher::getNewInstance(tag);
    }
    virtual CNVisitablePtr makeCNVisitableSaboteur() {
        return CNVisitableSaboteur::getNewInstance();
    }
    virtual CNTaggedPtr makeCNFakeTagged(std::string tag) {
        return CNFakeTagged::getNewInstance(tag);
    }

    virtual void expectMatcherMatchesVisitable(CNTagMatcherPtr sut, CNVisitablePtr visitable) {
        bool actual = sut->matches(visitable);

        std::string errorMessage = "CNTagMatcher should match the visitable, but it does not!";
        EXPECT_TRUE(actual) << errorMessage;
    }
    virtual void expectMatcherDoesNotMatchVisitable(CNTagMatcherPtr sut, CNVisitablePtr visitable) {
        bool actual = sut->matches(visitable);

        std::string errorMessage = "CNTagMatcher should not match the visitable, but it does!";
        EXPECT_FALSE(actual) << errorMessage;
    }
};

TEST_F(CNTagMatcherTest, FreshInstance__TaggedWithSameTag__MatcherShouldMatchTheTagged) {
    CNTagMatcherPtr sut = makeCNTagMatcher("theTag");

    CNTaggedPtr tagged = makeCNFakeTagged("theTag");

    expectMatcherMatchesVisitable(sut, tagged);
}

TEST_F(CNTagMatcherTest, FreshInstance__TaggedWithDifferentTag__MatcherShouldNotMatchTheTagged) {
    CNTagMatcherPtr sut = makeCNTagMatcher("theTag");

    CNTaggedPtr tagged = makeCNFakeTagged("differentTag");

    expectMatcherDoesNotMatchVisitable(sut, tagged);
}

TEST_F(CNTagMatcherTest, FreshInstance__MatchesWithVisitableSaboteur__MatcherShouldNotMatchTheTagged) {
    CNTagMatcherPtr sut = makeCNTagMatcher("theTag");

    CNVisitablePtr visitable = makeCNVisitableSaboteur();

    expectMatcherDoesNotMatchVisitable(sut, visitable);
}


