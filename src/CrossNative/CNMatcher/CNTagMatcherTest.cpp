#include <gmock/gmock.h>
#include "CNTagMatcher.h"

#include "CrossNative/CNVisitable/CNVisitableTestDoubles.h"


class CNTagMatcherTest : public testing::Test {
protected:
    virtual CNTagMatcherPtr makeCNTagMatcher(std::string tag) {
        return CNTagMatcher::getNewInstance(tag);
    }

    virtual CNVisitablePtr makeCNVisitableDummy() {
        return CNVisitableDummy::getNewInstance();
    }

    virtual void expectMatcherDoesNotMatchVisitable(CNTagMatcherPtr sut, CNVisitablePtr visitable) {
        bool actual = sut->matches(visitable);

        std::string errorMessage = "CNTagMatcher should not match the visitable, but it does!";
        EXPECT_FALSE(actual) << errorMessage;
    }
};

TEST_F(CNTagMatcherTest, FreshInstance) {
    CNTagMatcherPtr sut = makeCNTagMatcher("theTag");

    CNVisitablePtr visitable = makeCNVisitableDummy();

    expectMatcherDoesNotMatchVisitable(sut, visitable);
}