#include <gmock/gmock.h>
#include "CNTagMatcher.h"

#include "CrossNative/CNTagged/CNFakeTagged.h"


class CNTagMatcherTest : public testing::Test {
protected:
    virtual CNTagMatcherPtr makeCNTagMatcher(std::string tag) {
        return CNTagMatcher::getNewInstance(tag);
    }

    virtual CNTaggedPtr makeCNFakeTagged(std::string tag) {
        return CNFakeTagged::getNewInstance(tag);
    }

    virtual void expectMatcherMatchesTagged(CNTagMatcherPtr sut, CNTaggedPtr tagged) {
        bool actual = sut->matches(tagged);

        std::string errorMessage = "CNTagMatcher should match the tagged, but it does not!";
        EXPECT_TRUE(actual) << errorMessage;
    }

    virtual void expectMatcherDoesNotMatchTagged(CNTagMatcherPtr sut, CNTaggedPtr tagged) {
        bool actual = sut->matches(tagged);

        std::string errorMessage = "CNTagMatcher should not match the tagged, but it does!";
        EXPECT_FALSE(actual) << errorMessage;
    }
};

TEST_F(CNTagMatcherTest, FreshInstance__TaggedWithSameTag__MatcherShouldMatchTheTagged) {
    CNTagMatcherPtr sut = makeCNTagMatcher("theTag");

    CNTaggedPtr tagged = makeCNFakeTagged("theTag");

    expectMatcherMatchesTagged(sut, tagged);
}

TEST_F(CNTagMatcherTest, FreshInstance__TaggedWithDifferentTag__MatcherShouldNotMatchTheTagged) {
    CNTagMatcherPtr sut = makeCNTagMatcher("theTag");

    CNTaggedPtr tagged = makeCNFakeTagged("differentTag");

    expectMatcherDoesNotMatchTagged(sut, tagged);
}


