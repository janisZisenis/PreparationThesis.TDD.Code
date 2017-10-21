#include "gmock/gmock.h"
#include "CNFakeHierarchyNode.h"
#include "CNHierarchyNodeTestDoubles.h"

class CNFakeHierarchyNodeTest : public testing::Test {
protected:
    virtual CNFakeHierarchyNodePtr makeCNFakeHierarchyNode() {
        return CNFakeHierarchyNode::getNewInstance();
    }

    virtual CNHierarchyNodePtr makeCNHierarchyNodeDummy() {
        return CNHierarchyNodeDummy::getNewInstance();
    }

    virtual void expectIsParentOf(CNFakeHierarchyNodePtr parent,
                                  CNHierarchyNodePtr child) {
        bool actual = parent->isParentOf(child);

        std::string errorMessage = "CNFakeHierarchyNode should be parent of CNHierarchyNode, but it is not!";
        EXPECT_TRUE(actual) << errorMessage;
    }
    virtual void expectIsNotParentOf(CNFakeHierarchyNodePtr parent,
                                     CNHierarchyNodePtr child) {
        bool actual = parent->isParentOf(child);

        std::string errorMessage = "CNFakeHierarchyNode should not be parent of CNHierarchyNode, but it is!";
        EXPECT_FALSE(actual) << errorMessage;
    }
    virtual void expectHasChildCount(CNFakeHierarchyNodePtr sut, int childCount) {
        int expected = childCount;
        int actual = sut->getChildCount();

        std::string errorMessage = "The CNFakeHierarchyNode should have child count "
                                   + std::to_string(expected) + ". Instead it has " + std::to_string(actual) + "!";
        EXPECT_THAT(actual, testing::Eq(expected)) << errorMessage;
    }
    virtual void expectHasChildAtPosition(CNFakeHierarchyNodePtr sut, CNHierarchyNodePtr child ,int childPos) {
        CNHierarchyNodePtr expected = child;
        CNHierarchyNodePtr actual = sut->getChild(childPos);

        assertIsValidChildPosition(sut, childPos);

        std::string errorMessage = "The CNFakeHierarchyNode should have the child at position "
                                   + std::to_string(childPos) + ", but it has not!";
        EXPECT_THAT(actual, testing::Eq(expected)) << errorMessage;
    }
    virtual void assertIsValidChildPosition(CNFakeHierarchyNodePtr sut, int childPos) {
        int expected = childPos;
        int actual = sut->getChildCount();

        std::string errorMessage = "CNFakeHierarchyNode should have a valid child position of " + std::to_string(childPos) + ", but it has not!";
        ASSERT_THAT(actual, testing::Ge(expected)) << errorMessage;
    }
};

TEST_F(CNFakeHierarchyNodeTest, FreshInstance__ShouldNotBeParentOfCNHierarchyNode) {
    CNFakeHierarchyNodePtr sut = makeCNFakeHierarchyNode();

    CNHierarchyNodePtr node = makeCNHierarchyNodeDummy();

    expectIsNotParentOf(sut, node);
}

TEST_F(CNFakeHierarchyNodeTest, FreshInstance__Add__ShouldBeParentOfAddedCNHierarchyNode) {
    CNFakeHierarchyNodePtr sut = makeCNFakeHierarchyNode();

    CNHierarchyNodePtr node = makeCNHierarchyNodeDummy();
    sut->add(node);

    expectIsParentOf(sut, node);
}

TEST_F(CNFakeHierarchyNodeTest, AddedCNHierarchyNode__Remove__ShouldNotBeParentOfRemovedCNHierarchyNodeAnymore) {
    CNFakeHierarchyNodePtr sut = makeCNFakeHierarchyNode();
    CNHierarchyNodePtr node = makeCNHierarchyNodeDummy();
    sut->add(node);

    sut->remove(node);

    expectIsNotParentOf(sut, node);
}

TEST_F(CNFakeHierarchyNodeTest, FreshInstance__Remove__ShouldThrowCNChildNotFoundException) {
    CNFakeHierarchyNodePtr sut = makeCNFakeHierarchyNode();

    CNHierarchyNodePtr node = makeCNHierarchyNodeDummy();

    std::string errorMessage = "CNFakeHierarchyNode should throw CNChildNotFoundException, but it did not!";
    EXPECT_THROW(sut->remove(node), CNChildNotFoundException);
}

TEST_F(CNFakeHierarchyNodeTest, FreshInstance__InsertWithChildPos0__ShouldBeParentOfCNHierarchyNode) {
    CNFakeHierarchyNodePtr sut = makeCNFakeHierarchyNode();

    CNHierarchyNodePtr node = makeCNHierarchyNodeDummy();
    sut->insert(node, 0);

    expectIsParentOf(sut, node);
}

TEST_F(CNFakeHierarchyNodeTest, FreshInstance__InsertWithChildPos1__ShouldThrowCNInvalidInsertingPositionException) {
    CNFakeHierarchyNodePtr sut = makeCNFakeHierarchyNode();

    CNHierarchyNodePtr node = makeCNHierarchyNodeDummy();

    std::string errorMessage = "CNFakeHierarchyNode should throw CNInvalidInsertingPositionException, but it did not!";
    EXPECT_THROW(sut->insert(node, 1), CNInvalidInsertingPositionException);
}

TEST_F(CNFakeHierarchyNodeTest, AddedTwoCNHierarchyNodes_InsertedOneCNHierarchyNode__RemoveInsertedCNHierarchyNodes__ShouldHaveChildCount2) {
    CNFakeHierarchyNodePtr sut = makeCNFakeHierarchyNode();
    sut->add(makeCNHierarchyNodeDummy());
    sut->add(makeCNHierarchyNodeDummy());
    CNHierarchyNodePtr node = makeCNHierarchyNodeDummy();
    sut->add(node);

    sut->remove(node);

    expectHasChildCount(sut, 2);
}

TEST_F(CNFakeHierarchyNodeTest, AddedCNHierarchyNode__Add__ShouldKeepTheSecondCNHierarchyNodeAtChildPosition1) {
    CNFakeHierarchyNodePtr sut = makeCNFakeHierarchyNode();
    CNHierarchyNodePtr first = makeCNHierarchyNodeDummy();
    sut->add(first);

    CNHierarchyNodePtr second = makeCNHierarchyNodeDummy();
    sut->add(second);

    expectHasChildAtPosition(sut, second, 1);
}

TEST_F(CNFakeHierarchyNodeTest, AddedCNHierarchyNode__InsertWithChildPosition0__ShouldKeepTheSecondCNHierarchyNodeAtChildPosition0) {
    CNFakeHierarchyNodePtr sut = makeCNFakeHierarchyNode();
    CNHierarchyNodePtr first = makeCNHierarchyNodeDummy();
    sut->add(first);

    CNHierarchyNodePtr second = makeCNHierarchyNodeDummy();
    sut->insert(second, 0);

    expectHasChildAtPosition(sut, second, 0);
}

TEST_F(CNFakeHierarchyNodeTest, AddedCNHierarchyNode__GetChildWithChildPosition1__ShouldThrowCNInvalidChildPositionException) {
    CNFakeHierarchyNodePtr sut = makeCNFakeHierarchyNode();
    CNHierarchyNodePtr first = makeCNHierarchyNodeDummy();
    sut->add(first);

    std::string errorMessage = "CNFakeHierarchyNode should throw CNInvalidChildPositionException, but it does not!";
    EXPECT_THROW(sut->getChild(1), CNInvalidChildPositionException) << errorMessage;
}

TEST_F(CNFakeHierarchyNodeTest, AddedTwoCNHierarchyNodes__RemoveWithChildPosition0__ShouldKeepTheSecondCNHierarchyNotAtChildPosition0) {
    CNFakeHierarchyNodePtr sut = makeCNFakeHierarchyNode();
    sut->add(makeCNHierarchyNodeDummy());
    CNHierarchyNodePtr node = makeCNHierarchyNodeDummy();
    sut->add(node);

    sut->remove(0);

    expectHasChildAtPosition(sut, node, 0);
}

TEST_F(CNFakeHierarchyNodeTest, FreshInstance__RemoveWithChildPosition1__ShouldThrowCNInvalidChildPositionException) {
    CNFakeHierarchyNodePtr sut = makeCNFakeHierarchyNode();

    std::string errorMessage = "CNFakeHierarchyNode should throw CNInvalidChildPositionException, but it did not!";
    EXPECT_THROW(sut->remove(1), CNInvalidChildPositionException);
}