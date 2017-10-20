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

//TEST_F(CNHierarchyTest, AddedFirstWithInvalidCNHierarchyIndex__AddedSecondWithIndex_0__AddThirdWithIndex_0_0__SecondShouldHaveAddedThird) {
//    CNHierarchyPtr sut = CNHierarchy::getNewInstance();
//    CNHierarchyNodePtr first = makeCNFakeHierarchyNode();
//    sut->add(first, CNHierarchyIndex());
//    CNHierarchyNodeSpyPtr second = makeCNHierarchyNodeSpy();
//    sut->add(second, CNHierarchyIndex({0}));
//    CNHierarchyNodePtr third = makeCNHierarchyNodeDummy();
//    sut->add(third, CNHierarchyIndex({0,0}));
//
//    expectReceiverAddedCNHierarchyNode(second, third);
//}
//

//TEST_F(CNHierarchyTest, AddedFirstWithInvalidCNHierarchyIndex__AddedSecondWithIndex_0__AddThirdWithIndex_0__FirstShouldHaveAddedThird) {
//    CNHierarchyPtr sut = CNHierarchy::getNewInstance();
//    CNHierarchyNodeSpyPtr first = makeCNHierarchyNodeSpy();
//    sut->add(first, CNHierarchyIndex());
//    CNHierarchyNodePtr second = makeCNHierarchyNodeDummy();
//    sut->add(second, CNHierarchyIndex({0}));
//    CNHierarchyNodePtr third = makeCNHierarchyNodeDummy();
//    sut->add(third, CNHierarchyIndex({0}));
//
//    expectReceiverAddedCNHierarchyNode(first, third);
//}


//TEST_F(CNHierarchyTest, AddedWithInvalidIndex__AddWithInvalidCNHierarchyIndex_ShouldStoreTheSecondCNHierarchyNodeAtIndex_1) {
//    CNHierarchyPtr sut = CNHierarchy::getNewInstance();
//    sut->add(makeCNHierarchyNodeDummy(), CNHierarchyIndex());
//
//    CNHierarchyNodePtr second = makeCNHierarchyNodeDummy();
//    sut->add(second, CNHierarchyIndex());
//
//    expectHasCNHierarchyNodeAtIndex(sut, second, CNHierarchyIndex({1}));
//}

//TEST(CNHierarchyTest, testAdd_ShouldSetTheContentAtTheLastPositionOfTheParent) {
//    CNHierarchyPtr<TMock> sut = CNHierarchy<TMock>::getNewInstance();
//
//    TMockPtr zeroth = TMock::getNewInstance();
//    TMockPtr first = TMock::getNewInstance();
//    TMockPtr zerothZeroth = TMock::getNewInstance();
//    TMockPtr zerothFirst = TMock::getNewInstance();
//    TMockPtr firstZeroth = TMock::getNewInstance();
//
//    HierarchyIndex invalidIndex;
//    HierarchyIndex zerothIndex({0});
//    HierarchyIndex firstIndex({1});
//
//    sut->add(zeroth, invalidIndex);
//    sut->add(first, invalidIndex);
//    sut->add(zerothZeroth, zerothIndex);
//    sut->add(zerothFirst, zerothIndex);
//    sut->add(firstZeroth, firstIndex);
//
//    int rootChildCount = sut->getChildCountFor(invalidIndex);
//    EXPECT_THAT(sut->retrieve(CCore::HierarchyIndex(invalidIndex, rootChildCount - 2)), zeroth);
//    EXPECT_THAT(sut->retrieve(CCore::HierarchyIndex(invalidIndex, rootChildCount - 1)), first);
//
//    int zerothChildCount = sut->getChildCountFor(zerothIndex);
//    EXPECT_THAT(sut->retrieve(CCore::HierarchyIndex(zerothIndex, zerothChildCount - 2)), zerothZeroth);
//    EXPECT_THAT(sut->retrieve(CCore::HierarchyIndex(zerothIndex, zerothChildCount - 1)), zerothFirst);
//
//    int firstChildCount = sut->getChildCountFor(firstIndex);
//    EXPECT_THAT(sut->retrieve(CCore::HierarchyIndex(firstIndex, firstChildCount - 1)), firstZeroth);
//}

//TEST(CNHierarchyTest, testRemoveContent_ShouldRemoveTheGivenContentFromTheParent) {
//    CNHierarchyPtr<TMock> sut = CNHierarchy<TMock>::getNewInstance();
//
//    TMockPtr zeroth = TMock::getNewInstance();
//    TMockPtr first = TMock::getNewInstance();
//    TMockPtr zerothZeroth = TMock::getNewInstance();
//    TMockPtr zerothFirst = TMock::getNewInstance();
//    TMockPtr firstZeroth = TMock::getNewInstance();
//
//    HierarchyIndex invalidIndex;
//    HierarchyIndex zerothIndex({0});
//    HierarchyIndex firstIndex({1});
//
//    sut->add(zeroth, invalidIndex);
//    sut->add(first, invalidIndex);
//    sut->add(zerothZeroth, zerothIndex);
//    sut->add(zerothFirst, zerothIndex);
//    sut->add(firstZeroth, firstIndex);
//
//    sut->remove(first, invalidIndex);
//    sut->remove(zerothZeroth, zerothIndex);
//
//    ASSERT_THAT(sut->getChildCountFor(invalidIndex), 1);
//    EXPECT_THAT(sut->retrieve(CCore::HierarchyIndex(invalidIndex, 0)), zeroth);
//
//    ASSERT_THAT(sut->getChildCountFor(zerothIndex), 1);
//    EXPECT_THAT(sut->retrieve(CCore::HierarchyIndex(zerothIndex, 0)), zerothFirst);
//}

//TEST(CNHierarchyTest, testInsert_ShouldSetTheContentAtGivenChildPositionOfTheParent) {
//    CNHierarchyPtr<TMock> sut = CNHierarchy<TMock>::getNewInstance();
//
//    TMockPtr zeroth = TMock::getNewInstance();
//    TMockPtr first = TMock::getNewInstance();
//    TMockPtr zerothZeroth = TMock::getNewInstance();
//    TMockPtr zerothFirst = TMock::getNewInstance();
//    TMockPtr firstZeroth = TMock::getNewInstance();
//
//    HierarchyIndex invalidIndex;
//    HierarchyIndex zerothIndex({0});
//    HierarchyIndex firstIndex({1});
//
//    sut->insert(zeroth, invalidIndex, 0);
//    sut->insert(first, invalidIndex, 0);
//    sut->insert(zerothZeroth, zerothIndex, 0);
//    sut->insert(zerothFirst, zerothIndex, 0);
//    sut->insert(firstZeroth, firstIndex, 0);
//
//    EXPECT_THAT(sut->retrieve(CCore::HierarchyIndex(invalidIndex, 1)), zeroth);
//    EXPECT_THAT(sut->retrieve(CCore::HierarchyIndex(invalidIndex, 0)), first);
//
//    EXPECT_THAT(sut->retrieve(CCore::HierarchyIndex(zerothIndex, 1)), zerothZeroth);
//    EXPECT_THAT(sut->retrieve(CCore::HierarchyIndex(zerothIndex, 0)), zerothFirst);
//
//    EXPECT_THAT(sut->retrieve(CCore::HierarchyIndex(firstIndex, 0)), firstZeroth);
//}

//TEST(CNHierarchyTest, testRemoveChildPos_ShouldRemoveTheGivenChildPosFromTheParent) {
//    CNHierarchyPtr<TMock> sut = CNHierarchy<TMock>::getNewInstance();
//
//    TMockPtr zeroth = TMock::getNewInstance();
//    TMockPtr first = TMock::getNewInstance();
//    TMockPtr zerothZeroth = TMock::getNewInstance();
//    TMockPtr zerothFirst = TMock::getNewInstance();
//    TMockPtr firstZeroth = TMock::getNewInstance();
//
//    HierarchyIndex invalidIndex;
//    HierarchyIndex zerothIndex({0});
//    HierarchyIndex firstIndex({1});
//
//    sut->insert(zeroth, invalidIndex, 0);
//    sut->insert(first, invalidIndex, 0);
//    sut->insert(zerothZeroth, zerothIndex, 0);
//    sut->insert(zerothFirst, zerothIndex, 0);
//    sut->insert(firstZeroth, firstIndex, 0);
//
//    sut->remove(zerothIndex, 0);
//    ASSERT_THAT(sut->getChildCountFor(zerothIndex), 1);
//    EXPECT_THAT(sut->retrieve(CCore::HierarchyIndex(zerothIndex, 0)), zerothZeroth);
//
//    sut->remove(invalidIndex, 0);
//    ASSERT_THAT(sut->getChildCountFor(invalidIndex), 1);
//    EXPECT_THAT(sut->retrieve(CCore::HierarchyIndex(invalidIndex, 0)), zeroth);
//}

//TEST(CNHierarchyTest, testAddRemove_ShouldThrowIndexOutOfBoundsExceptionIfParentIndexIsOutOfBounds) {
//    CNHierarchyPtr<TMock> sut = CNHierarchy<TMock>::getNewInstance();
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

//TEST(CNHierarchyTest, testGetChildCountForIndexWithIndexOutOfBounds_ShouldThrowIndexOutOfBoundsException) {
//    CNHierarchyPtr<TMock> sut = CNHierarchy<TMock>::getNewInstance();
//
//    HierarchyIndex outOfBoundsIndex({1, 6, 88, 99});
//    EXPECT_THROW(sut->getChildCountFor(outOfBoundsIndex), IndexOutOfBoundsException);
//}

//TEST(CNHierarchyTest, testRetrieveWithIndexOutOfBounds_ShouldThrowIndexOutOfBoundsException) {
//    CNHierarchyPtr<TMock> sut = CNHierarchy<TMock>::getNewInstance();
//
//    HierarchyIndex outOfBoundsIndex({1, 6, 88, 99});
//    EXPECT_THROW(sut->retrieve(outOfBoundsIndex), IndexOutOfBoundsException);
//}

//TEST(CNHierarchyTest, testRetrieveWithInvalidIndex_ShouldThrowIndexOutOfBoundsException) {
//    CNHierarchyPtr<TMock> sut = CNHierarchy<TMock>::getNewInstance();
//
//    HierarchyIndex invalidIndex;
//    EXPECT_THROW(sut->retrieve(invalidIndex), IndexOutOfBoundsException);
//}