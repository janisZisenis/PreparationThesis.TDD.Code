#include <gmock/gmock.h>
#include "CNHierarchy.h"
#include "CrossNative/CNHierarchyNode/CNHierarchyNodeTestDoubles.h"
#include "CrossNative/CNHierarchyNode/CNFakeHierarchyNode.h"

class CNHierarchyTest : public testing::Test {
protected:
    virtual CNHierarchyPtr makeCNHierarchy() {
        return CNHierarchy::getNewInstance();
    }

    virtual CNHierarchyNodePtr makeCNHierarchyNodeDummy() {
        return CNHierarchyNodeDummy::getNewInstance();
    }
    virtual CNHierarchyNodePtr makeCNFakeHierarchyNode() {
        return CNFakeHierarchyNode::getNewInstance();
    }
    virtual CNHierarchyNodeSpyPtr makeCNHierarchyNodeSpy() {
        return CNHierarchyNodeSpy::getNewInstance();
    }

    virtual void expectHasCNHierarchyNodeAtIndex(CNHierarchyPtr sut, CNHierarchyNodePtr node, const CNHierarchyIndex& index) {
        CNHierarchyNodePtr actual = sut->retrieve(index);
        CNHierarchyNodePtr expected = node;

        std::string errorMessage = "CNHierarchy should have the CNHierarchyNode at index " + index.toString() + ", but it has not!";
        EXPECT_THAT(actual, testing::Eq(expected)) << errorMessage;
    }

    virtual void expectReceiverAddedCNHierarchyNode(CNHierarchyNodeSpyPtr receiver, CNHierarchyNodePtr node) {
        CNHierarchyNodePtr expected = node;
        CNHierarchyNodePtr actual = receiver->getAdded();

        std::string errorMessage = "CNHierarchyNode should have added the CNHierarchyNode as child, but it has not";
        EXPECT_THAT(actual, testing::Eq(expected)) << errorMessage;
    }
};

TEST_F(CNHierarchyTest, FreshInstance__AddWithNotExistingParentIndex__ShouldThrowCNNotExistingIndexException) {
    CNHierarchyPtr sut = makeCNHierarchy();

    CNHierarchyIndex notExistingParentIndex = CNHierarchyIndex({123, 6, 0});

    std::string errorMessage = "CNHierarchy should throw CNNotExistingIndexException, but it did not!";
    EXPECT_THROW(sut->add(makeCNHierarchyNodeDummy(), notExistingParentIndex), CNNotExistingIndexException) << errorMessage;
}

TEST_F(CNHierarchyTest, FreshInstance__AddWithInvalidIndex_ShouldStoreCNHierarchyNodeAtIndex_0) {
    CNHierarchyPtr sut = CNHierarchy::getNewInstance();

    CNHierarchyNodePtr node = makeCNHierarchyNodeDummy();
    sut->add(node, CNHierarchyIndex());

    expectHasCNHierarchyNodeAtIndex(sut, node, CNHierarchyIndex({0}));
}

TEST_F(CNHierarchyTest, AddedFirstWithInvalidIndex__AddSecondWithIndex_0__FirstShouldHaveAddedSecond) {
    CNHierarchyPtr sut = CNHierarchy::getNewInstance();
    CNHierarchyNodeSpyPtr first = makeCNHierarchyNodeSpy();
    sut->add(first, CNHierarchyIndex());

    CNHierarchyNodePtr second = makeCNHierarchyNodeDummy();
    sut->add(second, CNHierarchyIndex({0}));

    expectReceiverAddedCNHierarchyNode(first, second);
}

TEST_F(CNHierarchyTest, AddedFirstWithInvalidIndex__AddSecondWithIndex_0__ShouldStoreSecondAtIndex_0_0) {
    CNHierarchyPtr sut = CNHierarchy::getNewInstance();
    CNHierarchyNodePtr first = makeCNFakeHierarchyNode();
    sut->add(first, CNHierarchyIndex());

    CNHierarchyNodePtr second = makeCNHierarchyNodeDummy();
    sut->add(second, CNHierarchyIndex({0}));

    expectHasCNHierarchyNodeAtIndex(sut, second, CNHierarchyIndex({0, 0}));
}

TEST_F(CNHierarchyTest, AddedFirstWithInvalidIndex_AddedSecondWithIndex_0__AddThirdWithIndex_0__ShouldStoreThirdAtIndex_0_1) {
    CNHierarchyPtr sut = CNHierarchy::getNewInstance();
    CNHierarchyNodePtr first = makeCNFakeHierarchyNode();
    sut->add(first, CNHierarchyIndex());
    CNHierarchyNodePtr second = makeCNFakeHierarchyNode();
    sut->add(second, CNHierarchyIndex({0}));

    CNHierarchyNodePtr third = makeCNFakeHierarchyNode();
    sut->add(third, CNHierarchyIndex({0}));

    expectHasCNHierarchyNodeAtIndex(sut, third, CNHierarchyIndex({0, 1}));
}

TEST_F(CNHierarchyTest, AddedFirstWithInvalidIndex_AddedSecondWithIndex_0__AddThirdWithIndex_0_0__SecondShouldHaveAddedThird) {
    CNHierarchyPtr sut = CNHierarchy::getNewInstance();
    CNHierarchyNodePtr first = makeCNFakeHierarchyNode();
    sut->add(first, CNHierarchyIndex());
    CNHierarchyNodeSpyPtr second = makeCNHierarchyNodeSpy();
    sut->add(second, CNHierarchyIndex({0}));

    CNHierarchyNodePtr third = makeCNHierarchyNodeDummy();
    sut->add(third, CNHierarchyIndex({0, 0}));

    expectReceiverAddedCNHierarchyNode(second, third);
}

TEST_F(CNHierarchyTest, AddedFirstWithInvalidIndex__AddSecondWithInvalidIndex__ShouldStoreSecondAtIndex_1) {
    CNHierarchyPtr sut = CNHierarchy::getNewInstance();
    CNHierarchyNodePtr first = makeCNFakeHierarchyNode();
    sut->add(first, CNHierarchyIndex());

    CNHierarchyNodePtr second = makeCNHierarchyNodeDummy();
    sut->add(second, CNHierarchyIndex());

    expectHasCNHierarchyNodeAtIndex(sut, second, CNHierarchyIndex({1}));
}

TEST_F(CNHierarchyTest, AddedFirstWithInvalidIndex__AddedSecondWithInvalidIndex__AddThirdWithIndex_1__SecondShouldHaveAddedThird) {
    CNHierarchyPtr sut = CNHierarchy::getNewInstance();
    CNHierarchyNodePtr first = makeCNFakeHierarchyNode();
    sut->add(first, CNHierarchyIndex());
    CNHierarchyNodeSpyPtr second = makeCNHierarchyNodeSpy();
    sut->add(second, CNHierarchyIndex());

    CNHierarchyNodePtr third = makeCNHierarchyNodeDummy();
    sut->add(third, CNHierarchyIndex({1}));

    expectReceiverAddedCNHierarchyNode(second, third);
}

TEST_F(CNHierarchyTest, AddedFirstWithInvalidIndex__AddSecondWithInvalidIndex__AddThirdWithIndex_1__ShouldStoreThirdAtIndex_1_0) {
    CNHierarchyPtr sut = CNHierarchy::getNewInstance();
    CNHierarchyNodePtr first = makeCNFakeHierarchyNode();
    sut->add(first, CNHierarchyIndex());
    CNHierarchyNodePtr second = makeCNFakeHierarchyNode();
    sut->add(second, CNHierarchyIndex());

    CNHierarchyNodePtr third = makeCNHierarchyNodeDummy();
    sut->add(third, CNHierarchyIndex({1}));

    expectHasCNHierarchyNodeAtIndex(sut, third, CNHierarchyIndex({1, 0}));
}

TEST_F(CNHierarchyTest, AddedFirstWithInvalidIndex_AddedSecondWithIndex_0_AddedThirdWithIndex_0__AddFourthWithIndex_0_1__ThirdShouldHaveAddedFourth) {
    CNHierarchyPtr sut = CNHierarchy::getNewInstance();
    CNHierarchyNodePtr first = makeCNFakeHierarchyNode();
    sut->add(first, CNHierarchyIndex());
    CNHierarchyNodePtr second = makeCNFakeHierarchyNode();
    sut->add(second, CNHierarchyIndex({0}));
    CNHierarchyNodeSpyPtr third = makeCNHierarchyNodeSpy();
    sut->add(third, CNHierarchyIndex({0}));

    CNHierarchyNodePtr fourth = makeCNHierarchyNodeDummy();
    sut->add(fourth, CNHierarchyIndex({0, 1}));

    expectReceiverAddedCNHierarchyNode(third, fourth);
}

TEST_F(CNHierarchyTest, AddedFirstWithInvalidIndex_AddedSecondWithIndex_0_AddedThirdWithIndex_0__AddFourthWithIndex_0_1__ShouldStoreFourthAtIndex_0_1_0) {
    CNHierarchyPtr sut = CNHierarchy::getNewInstance();
    CNHierarchyNodePtr first = makeCNFakeHierarchyNode();
    sut->add(first, CNHierarchyIndex());
    CNHierarchyNodePtr second = makeCNFakeHierarchyNode();
    sut->add(second, CNHierarchyIndex({0}));
    CNHierarchyNodePtr third = makeCNFakeHierarchyNode();
    sut->add(third, CNHierarchyIndex({0}));

    CNHierarchyNodePtr fourth = makeCNHierarchyNodeDummy();
    sut->add(fourth, CNHierarchyIndex({0, 1}));

    expectHasCNHierarchyNodeAtIndex(sut, fourth, CNHierarchyIndex({0, 1, 0}));
}

TEST_F(CNHierarchyTest, AddedFirstWithInvalidIndex_AddedSecondWithInvalidIndex_AddedThirdWithIndex_1__AddFourthWithIndex_1_0__ThirdShouldHaveAddedFourth) {
    CNHierarchyPtr sut = CNHierarchy::getNewInstance();
    CNHierarchyNodePtr first = makeCNFakeHierarchyNode();
    sut->add(first, CNHierarchyIndex());
    CNHierarchyNodePtr second = makeCNFakeHierarchyNode();
    sut->add(second, CNHierarchyIndex());
    CNHierarchyNodeSpyPtr third = makeCNHierarchyNodeSpy();
    sut->add(third, CNHierarchyIndex({1}));

    CNHierarchyNodePtr fourth = makeCNHierarchyNodeDummy();
    sut->add(fourth, CNHierarchyIndex({1, 0}));

    expectReceiverAddedCNHierarchyNode(third, fourth);
}

TEST_F(CNHierarchyTest, FreshInstance__RetrieveWithNotExistingIndex__ShouldThrowCNNotExistingIndexException) {
    CNHierarchyPtr sut = makeCNHierarchy();

    CNHierarchyIndex notExistingIndex = CNHierarchyIndex({99, 3, 54});

    std::string errorMessage = "CNHierarchy should throw CNNotExistingIndexException, but it did not!";
    EXPECT_THROW(sut->retrieve(notExistingIndex), CNNotExistingIndexException) << errorMessage;
}

TEST_F(CNHierarchyTest, FreshInstance__RetrieveWithInvalidIndex__ShouldThrowCNInvalidIndexException) {
    CNHierarchyPtr sut = makeCNHierarchy();

    CNHierarchyIndex invalidIndex = CNHierarchyIndex();

    std::string errorMessage = "CNHierarchy should throw CNInvalidIndexException, but it did not!";
    EXPECT_THROW(sut->retrieve(invalidIndex), CNInvalidIndexException) << errorMessage;
}

//TEST_F(CNHierarchyTest, FreshInstance__AddWithIndexOutOfBounds__ShouldThrowCNIndexOutOfBoundsException) {
//    CNHierarchyPtr sut = makeCNHierarchy();
//
//    HierarchyIndex outOfBoundsIndex({1, 1, 66, 8});
//    EXPECT_THROW(sut->add(TMock::getNewInstance(), outOfBoundsIndex), IndexOutOfBoundsException);
//    EXPECT_THROW(sut->remove(TMock::getNewInstance(), outOfBoundsIndex), IndexOutOfBoundsException);
//}

//TEST(CNHierarchyTest, testInsertRemove_ShouldThrowIndexOutOfBoundsExceptionIfParentIndexIsOutOfBounds) {
//    CNHierarchyPtr<TMock> sut = CNHierarchy<TMock>::getNewInstance();
//
//    HierarchyIndex outOfBoundsIndex({1, 1, 66, 8});
//    int childPos = 0;
//    EXPECT_THROW(sut->insert(TMock::getNewInstance(), outOfBoundsIndex, childPos), IndexOutOfBoundsException);
//    EXPECT_THROW(sut->remove(outOfBoundsIndex, childPos), IndexOutOfBoundsException);
//}

//TEST(CNHierarchyTest, testRetrieveWithIndexOutOfBounds_ShouldThrowIndexOutOfBoundsException) {
//    CNHierarchyPtr<TMock> sut = CNHierarchy<TMock>::getNewInstance();
//
//    HierarchyIndex outOfBoundsIndex({1, 6, 88, 99});
//    EXPECT_THROW(sut->retrieve(outOfBoundsIndex), IndexOutOfBoundsException);
//}