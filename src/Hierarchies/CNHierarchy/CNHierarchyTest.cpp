#include <gmock/gmock.h>
#include "CNHierarchy.h"
#include "Hierarchies/CNComponent/CNComponentTestDoubles.h"
#include "Hierarchies/CNComponent/CNFakeComponent.h"

class CNHierarchyTest : public testing::Test {
protected:
    virtual CNHierarchyPtr makeCNHierarchy() {
        return CNHierarchy::getNewInstance();
    }

    virtual CNComponentPtr makeCNHierarchyNodeDummy() {
        return CNComponentDummy::getNewInstance();
    }
    virtual CNComponentPtr makeCNFakeHierarchyNode() {
        return CNFakeComponent::getNewInstance();
    }
    virtual CNComponentSpyPtr makeCNHierarchyNodeSpy() {
        return CNComponentSpy::getNewInstance();
    }

    virtual void expectHasCNHierarchyNodeAtIndex(CNHierarchyPtr sut, CNComponentPtr node, const CNHierarchyIndex& index) {
        CNComponentPtr actual = sut->retrieve(index);
        CNComponentPtr expected = node;

        std::string errorMessage = "CNHierarchy should have the CNComponent at index " + index.toString() + ", but it has not!";
        EXPECT_THAT(actual, testing::Eq(expected)) << errorMessage;
    }

    virtual void expectReceiverAddedCNHierarchyNode(CNComponentSpyPtr receiver, CNComponentPtr node) {
        CNComponentPtr expected = node;
        CNComponentPtr actual = receiver->getAdded();

        std::string errorMessage = "CNComponent should have added the CNComponent as child, but it has not";
        EXPECT_THAT(actual, testing::Eq(expected)) << errorMessage;
    }
    virtual void expectReceiverRemovedCNHierarchyNode(CNComponentSpyPtr receiver, CNComponentPtr node) {
        CNComponentPtr expected = node;
        CNComponentPtr actual = receiver->getRemoved();

        std::string errorMessage = "CNComponent should have removed the CNComponent as child, but it has not";
        EXPECT_THAT(actual, testing::Eq(expected)) << errorMessage;
    }
};

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

TEST_F(CNHierarchyTest, FreshInstance__AddWithNotExistingIndex__ShouldThrowCNNotExistingIndexException) {
    CNHierarchyPtr sut = makeCNHierarchy();

    CNHierarchyIndex notExistingIndex = CNHierarchyIndex({123, 6, 0});

    std::string errorMessage = "CNHierarchy should throw CNNotExistingIndexException, but it did not!";
    EXPECT_THROW(sut->add(makeCNHierarchyNodeDummy(), notExistingIndex), CNNotExistingIndexException) << errorMessage;
}

TEST_F(CNHierarchyTest, FreshInstance__AddWithInvalidIndex_ShouldStoreCNHierarchyNodeAtIndex_0) {
    CNHierarchyPtr sut = CNHierarchy::getNewInstance();

    CNComponentPtr node = makeCNHierarchyNodeDummy();
    sut->add(node, CNHierarchyIndex());

    expectHasCNHierarchyNodeAtIndex(sut, node, CNHierarchyIndex({0}));
}

TEST_F(CNHierarchyTest, AddedFirstWithInvalidIndex__AddSecondWithIndex_0__FirstShouldHaveAddedSecond) {
    CNHierarchyPtr sut = CNHierarchy::getNewInstance();
    CNComponentSpyPtr first = makeCNHierarchyNodeSpy();
    sut->add(first, CNHierarchyIndex());

    CNComponentPtr second = makeCNHierarchyNodeDummy();
    sut->add(second, CNHierarchyIndex({0}));

    expectReceiverAddedCNHierarchyNode(first, second);
}

TEST_F(CNHierarchyTest, AddedFirstWithInvalidIndex__AddSecondWithIndex_0__ShouldStoreSecondAtIndex_0_0) {
    CNHierarchyPtr sut = CNHierarchy::getNewInstance();
    CNComponentPtr first = makeCNFakeHierarchyNode();
    sut->add(first, CNHierarchyIndex());

    CNComponentPtr second = makeCNHierarchyNodeDummy();
    sut->add(second, CNHierarchyIndex({0}));

    expectHasCNHierarchyNodeAtIndex(sut, second, CNHierarchyIndex({0, 0}));
}

TEST_F(CNHierarchyTest, AddedFirstWithInvalidIndex_AddedSecondWithIndex_0__AddThirdWithIndex_0__ShouldStoreThirdAtIndex_0_1) {
    CNHierarchyPtr sut = CNHierarchy::getNewInstance();
    CNComponentPtr first = makeCNFakeHierarchyNode();
    sut->add(first, CNHierarchyIndex());
    CNComponentPtr second = makeCNFakeHierarchyNode();
    sut->add(second, CNHierarchyIndex({0}));

    CNComponentPtr third = makeCNFakeHierarchyNode();
    sut->add(third, CNHierarchyIndex({0}));

    expectHasCNHierarchyNodeAtIndex(sut, third, CNHierarchyIndex({0, 1}));
}

TEST_F(CNHierarchyTest, AddedFirstWithInvalidIndex_AddedSecondWithIndex_0__AddThirdWithIndex_0_0__SecondShouldHaveAddedThird) {
    CNHierarchyPtr sut = CNHierarchy::getNewInstance();
    CNComponentPtr first = makeCNFakeHierarchyNode();
    sut->add(first, CNHierarchyIndex());
    CNComponentSpyPtr second = makeCNHierarchyNodeSpy();
    sut->add(second, CNHierarchyIndex({0}));

    CNComponentPtr third = makeCNHierarchyNodeDummy();
    sut->add(third, CNHierarchyIndex({0, 0}));

    expectReceiverAddedCNHierarchyNode(second, third);
}

TEST_F(CNHierarchyTest, AddedFirstWithInvalidIndex__AddSecondWithInvalidIndex__ShouldStoreSecondAtIndex_1) {
    CNHierarchyPtr sut = CNHierarchy::getNewInstance();
    CNComponentPtr first = makeCNFakeHierarchyNode();
    sut->add(first, CNHierarchyIndex());

    CNComponentPtr second = makeCNHierarchyNodeDummy();
    sut->add(second, CNHierarchyIndex());

    expectHasCNHierarchyNodeAtIndex(sut, second, CNHierarchyIndex({1}));
}

TEST_F(CNHierarchyTest, AddedFirstWithInvalidIndex__AddedSecondWithInvalidIndex__AddThirdWithIndex_1__SecondShouldHaveAddedThird) {
    CNHierarchyPtr sut = CNHierarchy::getNewInstance();
    CNComponentPtr first = makeCNFakeHierarchyNode();
    sut->add(first, CNHierarchyIndex());
    CNComponentSpyPtr second = makeCNHierarchyNodeSpy();
    sut->add(second, CNHierarchyIndex());

    CNComponentPtr third = makeCNHierarchyNodeDummy();
    sut->add(third, CNHierarchyIndex({1}));

    expectReceiverAddedCNHierarchyNode(second, third);
}

TEST_F(CNHierarchyTest, AddedFirstWithInvalidIndex__AddSecondWithInvalidIndex__AddThirdWithIndex_1__ShouldStoreThirdAtIndex_1_0) {
    CNHierarchyPtr sut = CNHierarchy::getNewInstance();
    CNComponentPtr first = makeCNFakeHierarchyNode();
    sut->add(first, CNHierarchyIndex());
    CNComponentPtr second = makeCNFakeHierarchyNode();
    sut->add(second, CNHierarchyIndex());

    CNComponentPtr third = makeCNHierarchyNodeDummy();
    sut->add(third, CNHierarchyIndex({1}));

    expectHasCNHierarchyNodeAtIndex(sut, third, CNHierarchyIndex({1, 0}));
}

TEST_F(CNHierarchyTest, AddedFirstWithInvalidIndex_AddedSecondWithIndex_0_AddedThirdWithIndex_0__AddFourthWithIndex_0_1__ThirdShouldHaveAddedFourth) {
    CNHierarchyPtr sut = CNHierarchy::getNewInstance();
    CNComponentPtr first = makeCNFakeHierarchyNode();
    sut->add(first, CNHierarchyIndex());
    CNComponentPtr second = makeCNFakeHierarchyNode();
    sut->add(second, CNHierarchyIndex({0}));
    CNComponentSpyPtr third = makeCNHierarchyNodeSpy();
    sut->add(third, CNHierarchyIndex({0}));

    CNComponentPtr fourth = makeCNHierarchyNodeDummy();
    sut->add(fourth, CNHierarchyIndex({0, 1}));

    expectReceiverAddedCNHierarchyNode(third, fourth);
}

TEST_F(CNHierarchyTest, AddedFirstWithInvalidIndex_AddedSecondWithIndex_0_AddedThirdWithIndex_0__AddFourthWithIndex_0_1__ShouldStoreFourthAtIndex_0_1_0) {
    CNHierarchyPtr sut = CNHierarchy::getNewInstance();
    CNComponentPtr first = makeCNFakeHierarchyNode();
    sut->add(first, CNHierarchyIndex());
    CNComponentPtr second = makeCNFakeHierarchyNode();
    sut->add(second, CNHierarchyIndex({0}));
    CNComponentPtr third = makeCNFakeHierarchyNode();
    sut->add(third, CNHierarchyIndex({0}));

    CNComponentPtr fourth = makeCNHierarchyNodeDummy();
    sut->add(fourth, CNHierarchyIndex({0, 1}));

    expectHasCNHierarchyNodeAtIndex(sut, fourth, CNHierarchyIndex({0, 1, 0}));
}

TEST_F(CNHierarchyTest, AddedFirstWithInvalidIndex_AddedSecondWithInvalidIndex_AddedThirdWithIndex_1__AddFourthWithIndex_1_0__ThirdShouldHaveAddedFourth) {
    CNHierarchyPtr sut = CNHierarchy::getNewInstance();
    CNComponentPtr first = makeCNFakeHierarchyNode();
    sut->add(first, CNHierarchyIndex());
    CNComponentPtr second = makeCNFakeHierarchyNode();
    sut->add(second, CNHierarchyIndex());
    CNComponentSpyPtr third = makeCNHierarchyNodeSpy();
    sut->add(third, CNHierarchyIndex({1}));

    CNComponentPtr fourth = makeCNHierarchyNodeDummy();
    sut->add(fourth, CNHierarchyIndex({1, 0}));

    expectReceiverAddedCNHierarchyNode(third, fourth);
}


TEST_F(CNHierarchyTest, FreshInstance__RemoveWithNotExistingIndex__ShouldThrowCNNotExistingIndexException) {
    CNHierarchyPtr sut = makeCNHierarchy();

    CNHierarchyIndex notExistingIndex = CNHierarchyIndex({123, 6, 0});

    std::string errorMessage = "CNHierarchy should throw CNNotExistingIndexException, but it did not!";
    EXPECT_THROW(sut->remove(makeCNHierarchyNodeDummy(), notExistingIndex), CNNotExistingIndexException) << errorMessage;
}

TEST_F(CNHierarchyTest, AddedFirstWithInvalidIndex_AddedSecondWithIndex_0__RemoveSecondWithIndex_0__FirstShouldHaveRemovedSecond) {
    CNHierarchyPtr sut = CNHierarchy::getNewInstance();
    CNComponentSpyPtr first = makeCNHierarchyNodeSpy();
    sut->add(first, CNHierarchyIndex());

    CNComponentPtr second = makeCNHierarchyNodeDummy();
    sut->remove(second, CNHierarchyIndex({0}));

    expectReceiverRemovedCNHierarchyNode(first, second);
}