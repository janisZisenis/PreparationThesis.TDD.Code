#include <gmock/gmock.h>
#include "CNTypeMatcher.h"

#include "CrossNative/CNVisitor/CNVisitorTestDoubles.h"
#include "CrossNative/CNComponent/CNComponentTestDoubles.h"

class CNTypeMatcherTest : public testing::Test {
protected:
    virtual CNTypeMatcherPtr makeCNTypeMatcher(CNVisitorPtr matching) {
        return CNTypeMatcher::getNewInstance(matching);
    }
    virtual CNVisitorPtr makeCNVisitorDummy() {
        return CNVisitorDummy::getNewInstance();
    }
    virtual CNComponentSpyPtr makeCNComponentSpy() {
        return CNComponentSpy::getNewInstance();
    }

    virtual void expectComponentHasAcceptedVisitor(CNComponentSpyPtr component, CNVisitorPtr visitor) {
        CNVisitorPtr expected = component->getAccepted();
        CNVisitorPtr actual = visitor;

        std::string errorMessage = "The component should have accepted the visitor, but it has not!";
        EXPECT_THAT(actual, testing::Eq(expected)) << errorMessage;
    }
};

TEST_F(CNTypeMatcherTest, FreshInstance__Matches__ComponentShouldHaveAcceptedTheMatchingVisitor) {
    CNVisitorPtr matching = makeCNVisitorDummy();
    CNTypeMatcherPtr sut = makeCNTypeMatcher(matching);

    CNComponentSpyPtr component = makeCNComponentSpy();
    sut->matches(component);

    expectComponentHasAcceptedVisitor(component, matching);
}
