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

    virtual void expectHierarchyNodeIsParentOf(CNComposableHierarchyNodePtr parent, CNHierarchyNodePtr child) {
        bool actual = parent->isParentOf(child);

        std::string errorMessage = "CNComposableHierarchyNode should be parent of CNHierarchyNode, but it is not!";
        EXPECT_TRUE(actual) << errorMessage;
    }
};

TEST_F(CNComposableHierarchyNodeTest, FreshInstance__Add__ShouldBeParentOfAddedCNHierarchyNode) {
    CNComposableHierarchyNodePtr sut = makeCNComposableHierarchyNode();

    CNHierarchyNodePtr first = makeCNHierarchyNodeDummy();
    sut->add(first);

    expectHierarchyNodeIsParentOf(sut, first);
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