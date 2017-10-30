#include "gmock/gmock.h"
#include "CNVisitingComposer.h"

#include "Hierarchies/CNVisitor/CNVisitorTestDoubles.h"
#include "Hierarchies/CNVisitable/CNVisitableTestDoubles.h"

class CNVisitingComposerTest : public testing::Test {
protected:
    virtual CNVisitingComposerPtr makeCNVisitingComposer(CNVisitorPtr composing, CNVisitorPtr decomposing) {
        return CNVisitingComposer::getNewInstance(composing, decomposing);
    }
    virtual CNVisitorDummyPtr makeCNVisitorDummy() {
        return CNVisitorDummy::getNewInstance();
    }
    virtual CNVisitableSpyPtr makeCNVisitableSpy() {
        return CNVisitableSpy::getNewInstance();
    }

    virtual void expectVisitableHasAcceptedVisitor(CNVisitableSpyPtr visitable, CNVisitorPtr visitor) {
        CNVisitorPtr expected = visitable->getAccepted();
        CNVisitorPtr actual = visitor;

        std::string errorMessage = "The visitable should have accepted the visitor, but it has not!";
        EXPECT_THAT(actual, testing::Eq(expected)) << errorMessage;
    }
};


TEST_F(CNVisitingComposerTest, FreshInstance__Mount__VisitableShouldHaveAcceptedTheMountingVisitor) {
    CNVisitorDummyPtr mounting = makeCNVisitorDummy();
    CNVisitorDummyPtr dismounting = makeCNVisitorDummy();
    CNVisitingComposerPtr sut = makeCNVisitingComposer(mounting, dismounting);

    CNVisitableSpyPtr visitable = makeCNVisitableSpy();
    sut->mount(visitable);

    expectVisitableHasAcceptedVisitor(visitable, mounting);
}

TEST_F(CNVisitingComposerTest, FreshInstance__Mount__VisitableShouldHaveAcceptedTheDismountingVisitor) {
    CNVisitorDummyPtr mounting = makeCNVisitorDummy();
    CNVisitorDummyPtr dismounting = makeCNVisitorDummy();
    CNVisitingComposerPtr sut = makeCNVisitingComposer(mounting, dismounting);

    CNVisitableSpyPtr visitable = makeCNVisitableSpy();
    sut->dismount(visitable);

    expectVisitableHasAcceptedVisitor(visitable, dismounting);
}