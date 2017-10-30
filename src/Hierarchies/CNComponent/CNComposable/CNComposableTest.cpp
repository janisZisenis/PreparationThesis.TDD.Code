#include "gmock/gmock.h"
#include "CNComposable.h"
#include "Hierarchies/CNComponent/CNComponentTestDoubles.h"
#include "Hierarchies/CNVisitor/CNVisitorTestDoubles.h"
#include "Hierarchies/CNVisitable/CNVisitableTestDoubles.h"
#include "Hierarchies/CNComposer/CNComposerTestDoubles.h"

class CNComposableTest : public testing::Test {
protected:
    virtual CNComposablePtr makeCNComposableHierarchyNode(CNVisitablePtr visitable, CNComposerPtr composer) {
        return CNComposable::getNewInstance(visitable, composer);
    }

    virtual CNComponentPtr makeCNComponentDummy() {
        return CNComponentDummy::getNewInstance();
    }
    virtual CNVisitablePtr makeCNVisitableDummy() {
        return CNVisitableDummy::getNewInstance();
    }
    virtual CNVisitableSpyPtr makeCNVisitableSpy() {
        return CNVisitableSpy::getNewInstance();
    }
    virtual CNVisitorPtr makeCNVisitorDummy() {
        return CNVisitorDummy::getNewInstance();
    }
    virtual CNComposerPtr makeCNComposerDummy() {
        return CNComposerDummy::getNewInstance();
    }
    virtual CNComposerSpyPtr makeCNComposerSpy() {
        return CNComposerSpy::getNewInstance();
    }

    virtual void expectIsParentOf(CNComposablePtr parent, CNComponentPtr child) {
        bool actual = parent->isParentOf(child);

        std::string errorMessage = "CNComposable should be parent of CNComponent, but it is not!";
        EXPECT_TRUE(actual) << errorMessage;
    }
    virtual void expectIsNotParentOf(CNComposablePtr parent, CNComponentPtr child) {
        bool actual = parent->isParentOf(child);

        std::string errorMessage = "CNComposable should not be parent of CNComponent, but it is!";
        EXPECT_FALSE(actual) << errorMessage;
    }
    virtual void expectHasChildCount(CNComposablePtr sut, int childCount) {
        int expected = childCount;
        int actual = sut->getChildCount();

        std::string errorMessage = "The CNComposable should have child count "
                                   + std::to_string(expected) + ". Instead it has " + std::to_string(actual) + "!";
        EXPECT_THAT(actual, testing::Eq(expected)) << errorMessage;
    }
    virtual void expectHasChildAtPosition(CNComposablePtr sut, CNComponentPtr child, int childPos) {
        CNComponentPtr expected = child;
        CNComponentPtr actual = sut->getChild(childPos);

        assertIsValidChildPosition(sut, childPos);

        std::string errorMessage = "The CNComposable should have the child at position "
                                   + std::to_string(childPos) + ", but it has not!";
        EXPECT_THAT(actual, testing::Eq(expected)) << errorMessage;
    }
    virtual void assertIsValidChildPosition(CNComposablePtr sut, int childPos) {
        int expected = childPos;
        int actual = sut->getChildCount();

        std::string errorMessage = "CNComposable should have a valid child position of "
                                   + std::to_string(childPos) + ", but it has not!";
        ASSERT_THAT(actual, testing::Ge(expected)) << errorMessage;
    }
    virtual void expectVisitableHasAcceptedVisitor(CNVisitableSpyPtr visitable, CNVisitorPtr visitor) {
        CNVisitorPtr expected = visitable->getAccepted();
        CNVisitorPtr actual = visitor;

        std::string errorMessage = "The CNVisitable should have accepted the CNVisitor, but it has not!";
        EXPECT_THAT(actual, testing::Eq(expected)) << errorMessage;
    }

    virtual void expectComposerMountedChild(CNComposerSpyPtr composer, CNVisitablePtr child) {
        CNVisitablePtr expected = child;
        CNVisitablePtr actual = composer->getMounted();

        std::string errorMessage = "CNComposer should have mounted child, but it has not!";
        EXPECT_THAT(actual, testing::Eq(expected)) << errorMessage;
    }
    virtual void expectComposerDismountedChild(CNComposerSpyPtr composer, CNVisitablePtr child) {
        CNVisitablePtr expected = child;
        CNVisitablePtr actual = composer->getDismounted();

        std::string errorMessage = "CNComposer should have dismounted child, but it has not!";
        EXPECT_THAT(actual, testing::Eq(expected)) << errorMessage;
    }
};

class CNComposable_With_CNVisitableDummy_CNComposerDummy : public CNComposableTest {
protected:
    virtual void SetUp() override {
        CNVisitablePtr visitable = makeCNVisitableDummy();
        CNComposerPtr composer = makeCNComposerDummy();
        sut = makeCNComposableHierarchyNode(visitable, composer);
    }

    CNComposablePtr sut;
};

class CNComposable_With_CNVisitableDummy_CNComposerSpy : public CNComposableTest {
protected:
    virtual void SetUp() override {
        CNVisitablePtr visitable = makeCNVisitableDummy();
        composer = makeCNComposerSpy();
        sut = makeCNComposableHierarchyNode(visitable, composer);
    }

    CNComposerSpyPtr composer;
    CNComposablePtr sut;
};

TEST_F(CNComposable_With_CNVisitableDummy_CNComposerDummy, FreshInstance__ShouldNotBeParentOfChild) {
    CNComponentPtr child = makeCNComponentDummy();

    expectIsNotParentOf(sut, child);
}

TEST_F(CNComposable_With_CNVisitableDummy_CNComposerDummy, FreshInstance__AddChild__ShouldBeParentOfAddedChild) {
    CNComponentPtr child = makeCNComponentDummy();
    sut->add(child);

    expectIsParentOf(sut, child);
}

TEST_F(CNComposable_With_CNVisitableDummy_CNComposerDummy, AddedChild__RemoveChild__ShouldNotBeParentOfRemovedChildAnymore) {
    CNComponentPtr child = makeCNComponentDummy();
    sut->add(child);

    sut->remove(child);

    expectIsNotParentOf(sut, child);
}

TEST_F(CNComposable_With_CNVisitableDummy_CNComposerDummy, FreshInstance__RemoveChild__ShouldThrowCNChildNotFoundException) {
    CNComponentPtr child = makeCNComponentDummy();

    std::string errorMessage = "CNComposable should throw CNChildNotFoundException, but it did not!";
    EXPECT_THROW(sut->remove(child), CNChildNotFoundException);
}

TEST_F(CNComposable_With_CNVisitableDummy_CNComposerDummy, FreshInstance__InsertChildWithChildPos0__ShouldBeParentOfChild) {
    CNComponentPtr child = makeCNComponentDummy();
    sut->insert(child, 0);

    expectIsParentOf(sut, child);
}

TEST_F(CNComposable_With_CNVisitableDummy_CNComposerDummy, FreshInstance__InsertWithChildPos1__ShouldThrowCNInvalidInsertingPositionException) {
    CNComponentPtr child = makeCNComponentDummy();

    std::string errorMessage = "CNComposable should throw CNInvalidInsertingPositionException, but it did not!";
    EXPECT_THROW(sut->insert(child, 1), CNInvalidInsertingPositionException);
}

TEST_F(CNComposable_With_CNVisitableDummy_CNComposerDummy, AddedTwoChildren_InsertedOneChild__RemoveInsertedChild__ShouldHaveChildCount2) {
    sut->add(makeCNComponentDummy());
    sut->add(makeCNComponentDummy());
    CNComponentPtr child = makeCNComponentDummy();
    sut->insert(child, 0);

    sut->remove(child);

    expectHasChildCount(sut, 2);
}

TEST_F(CNComposable_With_CNVisitableDummy_CNComposerDummy, AddedChild__AddChild__ShouldStoreTheSecondChildAtChildPosition1) {
    CNComponentPtr first = makeCNComponentDummy();
    sut->add(first);

    CNComponentPtr second = makeCNComponentDummy();
    sut->add(second);

    expectHasChildAtPosition(sut, second, 1);
}

TEST_F(CNComposable_With_CNVisitableDummy_CNComposerDummy, AddedChild__InsertChildWithChildPosition0__ShouldStoreTheSecondChildAtChildPosition0) {
    CNComponentPtr first = makeCNComponentDummy();
    sut->add(first);

    CNComponentPtr second = makeCNComponentDummy();
    sut->insert(second, 0);

    expectHasChildAtPosition(sut, second, 0);
}

TEST_F(CNComposable_With_CNVisitableDummy_CNComposerDummy, AddedChild__GetChildWithChildPosition1__ShouldThrowCNInvalidChildPositionException) {
    CNComponentPtr first = makeCNComponentDummy();
    sut->add(first);

    std::string errorMessage = "CNComposable should throw CNInvalidChildPositionException, but it does not!";
    EXPECT_THROW(sut->getChild(1), CNInvalidChildPositionException) << errorMessage;
}

TEST_F(CNComposable_With_CNVisitableDummy_CNComposerDummy, AddedTwoChildren__RemoveWithChildPosition0__ShouldStoreTheSecondChildAtChildPosition0) {
    sut->add(makeCNComponentDummy());
    CNComponentPtr child = makeCNComponentDummy();
    sut->add(child);

    sut->remove(0);

    expectHasChildAtPosition(sut, child, 0);
}

TEST_F(CNComposable_With_CNVisitableDummy_CNComposerDummy, FreshInstance__RemoveWithChildPosition1__ShouldThrowCNInvalidChildPositionException) {
    std::string errorMessage = "CNComposable should throw CNInvalidChildPositionException, but it did not!";
    EXPECT_THROW(sut->remove(1), CNInvalidChildPositionException);
}

TEST_F(CNComposableTest, FreshInstance__Accept__VisitableShouldHaveAcceptedVisitor) {
    CNVisitableSpyPtr visitable = makeCNVisitableSpy();
    CNComposerPtr composer = makeCNComposerDummy();
    CNComposablePtr sut = makeCNComposableHierarchyNode(visitable, composer);

    CNVisitorPtr visitor = makeCNVisitorDummy();
    sut->accept(visitor);

    expectVisitableHasAcceptedVisitor(visitable, visitor);
}

TEST_F(CNComposable_With_CNVisitableDummy_CNComposerSpy, FreshInstance__AddChild__ComposerShouldMountTheAddedChild) {
    CNComponentPtr child = makeCNComponentDummy();
    sut->add(child);

    expectComposerMountedChild(composer, child);
}

TEST_F(CNComposable_With_CNVisitableDummy_CNComposerSpy, ChildAdded__RemoveChild__ComposerShouldDismountTheRemovedChild) {
    CNComponentPtr child = makeCNComponentDummy();
    sut->add(child);

    sut->remove(child);

    expectComposerDismountedChild(composer, child);
}

TEST_F(CNComposable_With_CNVisitableDummy_CNComposerSpy, FreshInstance__InsertChildWithChildPosition0__ComposerShouldMountTheAddedChild) {
    CNComponentPtr child = makeCNComponentDummy();
    sut->insert(child, 0);

    expectComposerMountedChild(composer, child);
}

TEST_F(CNComposable_With_CNVisitableDummy_CNComposerSpy, ChildInsertedWithChildPos0__RemoveWithChildPos0__ComposerShouldDismountTheRemovedChild) {
    CNComponentPtr child = makeCNComponentDummy();
    sut->insert(child, 0);

    sut->remove(0);

    expectComposerDismountedChild(composer, child);
}

TEST_F(CNComposable_With_CNVisitableDummy_CNComposerSpy, ChildAdded__Destruction__ComposerShouldDismountTheChild) {
    CNComponentPtr child = makeCNComponentDummy();
    sut->add(child);

    sut.reset();

    expectComposerDismountedChild(composer, child);
}

