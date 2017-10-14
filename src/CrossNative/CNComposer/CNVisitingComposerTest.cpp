#include "gmock/gmock.h"
#include "CNVisitingComposer.h"

#include "CrossNative/CNVisitor/CNVisitorTestDoubles.h"
#include "CrossNative/CNComponent/CNComponentTestDoubles.h"

class CNVisitingComposerTest : public testing::Test {
protected:
    virtual CNVisitingComposerPtr makeCNVisitingComposer(CNVisitorPtr composing, CNVisitorPtr decomposing) {
        return CNVisitingComposer::getNewInstance(composing, decomposing);
    }

    virtual CNVisitorDummyPtr makeCNVisitorDummy() {
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


TEST_F(CNVisitingComposerTest, FreshInstance__Mount__ComponentShouldHaveAcceptedTheComposingVisitor) {
    CNVisitorDummyPtr composing = makeCNVisitorDummy();
    CNVisitorDummyPtr decomposing = makeCNVisitorDummy();
    CNVisitingComposerPtr sut = makeCNVisitingComposer(composing, decomposing);

    CNComponentSpyPtr component = makeCNComponentSpy();
    sut->mount(component);

    expectComponentHasAcceptedVisitor(component, composing);
}