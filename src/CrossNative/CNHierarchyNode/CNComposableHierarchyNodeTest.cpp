#include "gmock/gmock.h"
#include "CNComposableHierarchyNode.h"
#include "CNHierarchyNodeTestDoubles.h"
#include "CrossNative/CNVisitor/CNVisitorTestDoubles.h"
#include "CrossNative/CNVisitable/CNVisitableTestDoubles.h"
#include "CrossNative/CNComposer/CNComposerTestDoubles.h"

class CNComposableHierarchyNodeTest : public testing::Test {
protected:
    virtual CNComposableHierarchyNodePtr makeCNComposableHierarchyNode(CNVisitablePtr visitable, CNComposerPtr composer) {
        return CNComposableHierarchyNode::getNewInstance(visitable, composer);
    }

    virtual CNHierarchyNodePtr makeCNHierarchyNodeDummy() {
        return CNHierarchyNodeDummy::getNewInstance();
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

    virtual void expectIsParentOf(CNComposableHierarchyNodePtr parent,
                                  CNHierarchyNodePtr child) {
        bool actual = parent->isParentOf(child);

        std::string errorMessage = "CNComposableHierarchyNode should be parent of CNHierarchyNode, but it is not!";
        EXPECT_TRUE(actual) << errorMessage;
    }
    virtual void expectIsNotParentOf(CNComposableHierarchyNodePtr parent,
                                     CNHierarchyNodePtr child) {
        bool actual = parent->isParentOf(child);

        std::string errorMessage = "CNComposableHierarchyNode should not be parent of CNHierarchyNode, but it is!";
        EXPECT_FALSE(actual) << errorMessage;
    }
    virtual void expectHasChildCount(CNComposableHierarchyNodePtr sut, int childCount) {
        int expected = childCount;
        int actual = sut->getChildCount();

        std::string errorMessage = "The CNComposableHierarchyNode should have child count "
                                   + std::to_string(expected) + ". Instead it has " + std::to_string(actual) + "!";
        EXPECT_THAT(actual, testing::Eq(expected)) << errorMessage;
    }
    virtual void expectHasChildAtPosition(CNComposableHierarchyNodePtr sut, CNHierarchyNodePtr child ,int childPos) {
        CNHierarchyNodePtr expected = child;
        CNHierarchyNodePtr actual = sut->getChild(childPos);

        assertIsValidChildPosition(sut, childPos);

        std::string errorMessage = "The CNComposableHierarchyNode should have the child at position "
                                   + std::to_string(childPos) + ", but it has not!";
        EXPECT_THAT(actual, testing::Eq(expected)) << errorMessage;
    }
    virtual void assertIsValidChildPosition(CNComposableHierarchyNodePtr sut, int childPos) {
        int expected = childPos;
        int actual = sut->getChildCount();

        std::string errorMessage = "CNComposableHierarchyNode should have a valid child position of " + std::to_string(childPos) + ", but it has not!";
        ASSERT_THAT(actual, testing::Ge(expected)) << errorMessage;
    }
    virtual void expectVisitableHasAcceptedVisitor(CNVisitableSpyPtr visitable, CNVisitorPtr visitor) {
        CNVisitorPtr expected = visitable->getAccepted();
        CNVisitorPtr actual = visitor;

        std::string errorMessage = "The visitable should have accepted the visitor, but it has not!";
        EXPECT_THAT(actual, testing::Eq(expected)) << errorMessage;
    }

    virtual void expectComposerMountedChild(CNComposerSpyPtr composer, CNVisitablePtr child) {
        CNVisitablePtr expected = child;
        CNVisitablePtr actual = composer->getMounted();

        std::string errorMessage = "Composer should have mounted child, but it has not!";
        EXPECT_THAT(actual, testing::Eq(expected)) << errorMessage;
    }
    virtual void expectComposerDismountedChild(CNComposerSpyPtr composer, CNVisitablePtr child) {
        CNVisitablePtr expected = child;
        CNVisitablePtr actual = composer->getDismounted();

        std::string errorMessage = "Composer should have dismounted child, but it has not!";
        EXPECT_THAT(actual, testing::Eq(expected)) << errorMessage;
    }
};

class CNComposableHierarchyNode_With_CNVisitableDummy_CNComposerDummy : public CNComposableHierarchyNodeTest {
protected:
    virtual void SetUp() override {
        CNVisitablePtr visitable = makeCNVisitableDummy();
        CNComposerPtr composer = makeCNComposerDummy();
        sut = makeCNComposableHierarchyNode(visitable, composer);
    }

    CNComposableHierarchyNodePtr sut;
};

class CNComposableHierarchyNode_With_CNVisitableDummy_CNComposerSpy : public CNComposableHierarchyNodeTest {
protected:
    virtual void SetUp() override {
        CNVisitablePtr visitable = makeCNVisitableDummy();
        composer = makeCNComposerSpy();
        sut = makeCNComposableHierarchyNode(visitable, composer);
    }

    CNComposerSpyPtr composer;
    CNComposableHierarchyNodePtr sut;
};

TEST_F(CNComposableHierarchyNode_With_CNVisitableDummy_CNComposerDummy, FreshInstance__ShouldNotBeParentOfCNHierarchyNode) {
    CNHierarchyNodePtr node = makeCNHierarchyNodeDummy();

    expectIsNotParentOf(sut, node);
}

TEST_F(CNComposableHierarchyNode_With_CNVisitableDummy_CNComposerDummy, FreshInstance__Add__ShouldBeParentOfAddedCNHierarchyNode) {
    CNHierarchyNodePtr node = makeCNHierarchyNodeDummy();
    sut->add(node);

    expectIsParentOf(sut, node);
}

TEST_F(CNComposableHierarchyNode_With_CNVisitableDummy_CNComposerDummy, AddedCNHierarchyNode__Remove__ShouldNotBeParentOfRemovedCNHierarchyNodeAnymore) {
    CNHierarchyNodePtr node = makeCNHierarchyNodeDummy();
    sut->add(node);

    sut->remove(node);

    expectIsNotParentOf(sut, node);
}

TEST_F(CNComposableHierarchyNode_With_CNVisitableDummy_CNComposerDummy, FreshInstance__Remove__ShouldThrowCNChildNotFoundException) {
    CNHierarchyNodePtr node = makeCNHierarchyNodeDummy();

    std::string errorMessage = "CNComposableHierarchyNode should throw CNChildNotFoundException, but it did not!";
    EXPECT_THROW(sut->remove(node), CNChildNotFoundException);
}

TEST_F(CNComposableHierarchyNode_With_CNVisitableDummy_CNComposerDummy, FreshInstance__InsertWithChildPos0__ShouldBeParentOfCNHierarchyNode) {
    CNHierarchyNodePtr node = makeCNHierarchyNodeDummy();
    sut->insert(node, 0);

    expectIsParentOf(sut, node);
}

TEST_F(CNComposableHierarchyNode_With_CNVisitableDummy_CNComposerDummy, FreshInstance__InsertWithChildPos1__ShouldThrowCNInvalidInsertingPositionException) {
    CNHierarchyNodePtr node = makeCNHierarchyNodeDummy();

    std::string errorMessage = "CNComposableHierarchyNode should throw CNInvalidInsertingPositionException, but it did not!";
    EXPECT_THROW(sut->insert(node, 1), CNInvalidInsertingPositionException);
}

TEST_F(CNComposableHierarchyNode_With_CNVisitableDummy_CNComposerDummy, AddedTwoCNHierarchyNodes_InsertedOneCNHierarchyNode__RemoveInsertedCNHierarchyNodes__ShouldHaveChildCount2) {
    sut->add(makeCNHierarchyNodeDummy());
    sut->add(makeCNHierarchyNodeDummy());
    CNHierarchyNodePtr node = makeCNHierarchyNodeDummy();
    sut->add(node);

    sut->remove(node);

    expectHasChildCount(sut, 2);
}

TEST_F(CNComposableHierarchyNode_With_CNVisitableDummy_CNComposerDummy, AddedCNHierarchyNode__Add__ShouldKeepTheSecondCNHierarchyNodeAtChildPosition1) {
    CNHierarchyNodePtr first = makeCNHierarchyNodeDummy();
    sut->add(first);

    CNHierarchyNodePtr second = makeCNHierarchyNodeDummy();
    sut->add(second);

    expectHasChildAtPosition(sut, second, 1);
}

TEST_F(CNComposableHierarchyNode_With_CNVisitableDummy_CNComposerDummy, AddedCNHierarchyNode__InsertWithChildPosition0__ShouldKeepTheSecondCNHierarchyNodeAtChildPosition0) {
    CNHierarchyNodePtr first = makeCNHierarchyNodeDummy();
    sut->add(first);

    CNHierarchyNodePtr second = makeCNHierarchyNodeDummy();
    sut->insert(second, 0);

    expectHasChildAtPosition(sut, second, 0);
}

TEST_F(CNComposableHierarchyNode_With_CNVisitableDummy_CNComposerDummy, AddedCNHierarchyNode__GetChildWithChildPosition1__ShouldThrowCNInvalidChildPositionException) {
    CNHierarchyNodePtr first = makeCNHierarchyNodeDummy();
    sut->add(first);

    std::string errorMessage = "CNComposableHierarchyNode should throw CNInvalidChildPositionException, but it does not!";
    EXPECT_THROW(sut->getChild(1), CNInvalidChildPositionException) << errorMessage;
}

TEST_F(CNComposableHierarchyNode_With_CNVisitableDummy_CNComposerDummy, AddedTwoCNHierarchyNodes__RemoveWithChildPosition0__ShouldKeepTheSecondCNHierarchyNotAtChildPosition0) {
    sut->add(makeCNHierarchyNodeDummy());
    CNHierarchyNodePtr node = makeCNHierarchyNodeDummy();
    sut->add(node);

    sut->remove(0);

    expectHasChildAtPosition(sut, node, 0);
}

TEST_F(CNComposableHierarchyNode_With_CNVisitableDummy_CNComposerDummy, FreshInstance__RemoveWithChildPosition1__ShouldThrowCNInvalidChildPositionException) {
    std::string errorMessage = "CNComposableHierarchyNode should throw CNInvalidChildPositionException, but it did not!";
    EXPECT_THROW(sut->remove(1), CNInvalidChildPositionException);
}

TEST_F(CNComposableHierarchyNodeTest, FreshInstance__Accept__VisitableShouldHaveAcceptedVisitor) {
    CNVisitableSpyPtr visitable = makeCNVisitableSpy();
    CNComposerPtr composer = makeCNComposerDummy();
    CNComposableHierarchyNodePtr sut = makeCNComposableHierarchyNode(visitable, composer);

    CNVisitorPtr visitor = makeCNVisitorDummy();
    sut->accept(visitor);

    expectVisitableHasAcceptedVisitor(visitable, visitor);
}

TEST_F(CNComposableHierarchyNode_With_CNVisitableDummy_CNComposerSpy, FreshInstance__Add__ComposerShouldMountTheAddedCNHierarchyNode) {
    CNHierarchyNodePtr child = makeCNHierarchyNodeDummy();
    sut->add(child);

    expectComposerMountedChild(composer, child);
}

TEST_F(CNComposableHierarchyNode_With_CNVisitableDummy_CNComposerSpy, CNHierarchyNodeAdded__Remove__ComposerShouldDismountTheRemovedCNHierarchyNode) {
    CNHierarchyNodePtr node = makeCNHierarchyNodeDummy();
    sut->add(node);

    sut->remove(node);

    expectComposerDismountedChild(composer, node);
}

TEST_F(CNComposableHierarchyNode_With_CNVisitableDummy_CNComposerSpy, FreshInstance__InsertWithChildPosition0__ComposerShouldMountTheAddedCNHierarchyNode) {
    CNHierarchyNodePtr node = makeCNHierarchyNodeDummy();
    sut->insert(node, 0);

    expectComposerMountedChild(composer, node);
}

TEST_F(CNComposableHierarchyNode_With_CNVisitableDummy_CNComposerSpy, CNHierarchyNodeInsertedWithChildPos0__RemoveWithChildPos0__ComposerShouldDismountTheRemovedCNHierarchyNode) {
    CNHierarchyNodePtr node = makeCNHierarchyNodeDummy();
    sut->insert(node, 0);

    sut->remove(0);

    expectComposerDismountedChild(composer, node);
}

TEST_F(CNComposableHierarchyNode_With_CNVisitableDummy_CNComposerSpy, CNHierarchyNodeAdded__Destruction__ComposerShouldDismountTheCNHierarchyNode) {
    CNHierarchyNodePtr node = makeCNHierarchyNodeDummy();
    sut->add(node);

    sut.reset();

    expectComposerDismountedChild(composer, node);
}

