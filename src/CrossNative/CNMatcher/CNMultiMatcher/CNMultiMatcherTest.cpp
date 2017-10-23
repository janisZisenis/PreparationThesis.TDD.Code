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

};

TEST_F(CNMultiMatcherTest, FreshInstance__ShouldNotMatchVisitable) {
    CNMultiMatcherPtr sut = makeCNMultiMatcher();

    CNVisitablePtr visitable = makeCNVisitableDummy();
    expectDoesNotMatchVisitable(sut, visitable);
}
