#include "gmock/gmock.h"
#include "CNComposableHierarchyNode.h"
#include "CNHierarchyNodeTestDoubles.h"

class CNComposableHierarchyNodeTest : public testing::Test {
protected:
    virtual CNComposableHierarchyNodePtr makeCNComposableHierarchyNode() {
        return CNComposableHierarchyNode::getNewInstance();
    }

    virtual CNHierarchyNodePtr makeCNHierarchyNodeDummy() {
        return CNHierarchyNodeDummy::getNewInstance();
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
};

TEST_F(CNComposableHierarchyNodeTest, FreshInstance__ShouldNotBeParentOfCNHierarchyNode) {
    CNComposableHierarchyNodePtr sut = makeCNComposableHierarchyNode();

    CNHierarchyNodePtr node = makeCNHierarchyNodeDummy();

    expectIsNotParentOf(sut, node);
}

TEST_F(CNComposableHierarchyNodeTest, FreshInstance__Add__ShouldBeParentOfAddedCNHierarchyNode) {
    CNComposableHierarchyNodePtr sut = makeCNComposableHierarchyNode();

    CNHierarchyNodePtr node = makeCNHierarchyNodeDummy();
    sut->add(node);

    expectIsParentOf(sut, node);
}

TEST_F(CNComposableHierarchyNodeTest, AddedCNHierarchyNode__Remove__ShouldNotBeParentOfRemovedCNHierarchyNodeAnymore) {
    CNComposableHierarchyNodePtr sut = makeCNComposableHierarchyNode();
    CNHierarchyNodePtr node = makeCNHierarchyNodeDummy();
    sut->add(node);

    sut->remove(node);

    expectIsNotParentOf(sut, node);
}

TEST_F(CNComposableHierarchyNodeTest, FreshInstance__Remove__ShouldThrowCNChildNotFoundException) {
    CNComposableHierarchyNodePtr sut = makeCNComposableHierarchyNode();

    CNHierarchyNodePtr node = makeCNHierarchyNodeDummy();

    std::string errorMessage = "CNComposableHierarchyNode should throw CNChildNotFoundException, but it did not!";
    EXPECT_THROW(sut->remove(node), CNChildNotFoundException);
}

TEST_F(CNComposableHierarchyNodeTest, FreshInstance__InsertWithChildPos0__ShouldBeParentOfCNHierarchyNode) {
    CNComposableHierarchyNodePtr sut = makeCNComposableHierarchyNode();

    CNHierarchyNodePtr node = makeCNHierarchyNodeDummy();
    sut->insert(node, 0);

    expectIsParentOf(sut, node);
}

TEST_F(CNComposableHierarchyNodeTest, FreshInstance__InsertWithChildPos1__ShouldThrowCNInvalidInsertingPositionException) {
    CNComposableHierarchyNodePtr sut = makeCNComposableHierarchyNode();

    CNHierarchyNodePtr node = makeCNHierarchyNodeDummy();

    std::string errorMessage = "CNComposableHierarchyNode should throw CNInvalidInsertingPositionException, but it did not!";
    EXPECT_THROW(sut->insert(node, 1), CNInvalidInsertingPositionException);
}

TEST_F(CNComposableHierarchyNodeTest, AddedTwoCNHierarchyNodes_InsertedOneCNHierarchyNode__RemoveInsertedCNHierarchyNodes__ShouldHaveChildCount2) {
    CNComposableHierarchyNodePtr sut = makeCNComposableHierarchyNode();
    sut->add(makeCNHierarchyNodeDummy());
    sut->add(makeCNHierarchyNodeDummy());
    CNHierarchyNodePtr node = makeCNHierarchyNodeDummy();
    sut->add(node);

    sut->remove(node);

    expectHasChildCount(sut, 2);
}

TEST_F(CNComposableHierarchyNodeTest, AddedCNHierarchyNode__Add__ShouldKeepTheSecondCNHierarchyNodeAtChildPosition1) {
    CNComposableHierarchyNodePtr sut = makeCNComposableHierarchyNode();
    CNHierarchyNodePtr first = makeCNHierarchyNodeDummy();
    sut->add(first);

    CNHierarchyNodePtr second = makeCNHierarchyNodeDummy();
    sut->add(second);

    expectHasChildAtPosition(sut, second, 1);
}

TEST_F(CNComposableHierarchyNodeTest, AddedCNHierarchyNode__InsertWithChildPosition0__ShouldKeepTheSecondCNHierarchyNodeAtChildPosition0) {
    CNComposableHierarchyNodePtr sut = makeCNComposableHierarchyNode();
    CNHierarchyNodePtr first = makeCNHierarchyNodeDummy();
    sut->add(first);

    CNHierarchyNodePtr second = makeCNHierarchyNodeDummy();
    sut->insert(second, 0);

    expectHasChildAtPosition(sut, second, 0);
}

TEST_F(CNComposableHierarchyNodeTest, AddedCNHierarchyNode__GetChildWithChildPosition1__ShouldThrowCNInvalidChildPositionException) {
    CNComposableHierarchyNodePtr sut = makeCNComposableHierarchyNode();
    CNHierarchyNodePtr first = makeCNHierarchyNodeDummy();
    sut->add(first);

    std::string errorMessage = "CNComposableHierarchyNode should throw CNInvalidChildPositionException, but it does not!";
    EXPECT_THROW(sut->getChild(1), CNInvalidChildPositionException) << errorMessage;
}