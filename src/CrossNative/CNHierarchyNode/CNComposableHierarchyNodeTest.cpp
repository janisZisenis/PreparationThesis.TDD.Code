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
    EXPECT_THROW(sut->remove(node),CNChildNotFoundException);
}

//TEST(CNHierarchyNodeTest, testInsert_InsertsComponentAtChildPosition) {
//    CNHierarchyNodePtr<TMock> sut = CNHierarchyNode<TMock>::getNewInstance(TMock::getNewInstance());
//
//    ComponentDummyPtr<TMock> first = ComponentDummy<TMock>::getNewInstance();
//    ComponentDummyPtr<TMock> second = ComponentDummy<TMock>::getNewInstance();
//    ComponentDummyPtr<TMock> third = ComponentDummy<TMock>::getNewInstance();
//
//    sut->insert(third,  0);
//    sut->insert(first,  0);
//    sut->insert(second, 1);
//
//    ASSERT_THAT(sut->getChildCount(), 3);
//    EXPECT_THAT(sut->getChild(0), first);
//    EXPECT_THAT(sut->getChild(1), second);
//    EXPECT_THAT(sut->getChild(2), third);
//}

//TEST(CNHierarchyNodeTest, testRemove_RemovesGivenComponentFromChildren) {
//    CNHierarchyNodePtr<TMock> sut = CNHierarchyNode<TMock>::getNewInstance(TMock::getNewInstance());
//
//    ComponentDummyPtr<TMock> first = ComponentDummy<TMock>::getNewInstance();
//    ComponentDummyPtr<TMock> second = ComponentDummy<TMock>::getNewInstance();
//    ComponentDummyPtr<TMock> third = ComponentDummy<TMock>::getNewInstance();
//
//    sut->add(first);
//    sut->add(second);
//    sut->add(third);
//
//    sut->remove(second);
//
//    ASSERT_THAT(sut->getChildCount(), 2);
//    EXPECT_THAT(sut->getChild(0),first);
//    EXPECT_THAT(sut->getChild(1),third);
//}

//TEST(CNHierarchyNodeTest, testGetContent_ReturnsContens) {
//    TMockPtr content = TMock::getNewInstance();
//    CNHierarchyNodePtr<TMock> sut = CNHierarchyNode<TMock>::getNewInstance(content);
//
//    EXPECT_THAT(sut->getContent(), content);
//}