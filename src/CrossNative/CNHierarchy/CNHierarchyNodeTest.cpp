//#include "gmock/gmock.h"
//
//#include "CNHierarchyNode.h"
//#include "CCore/Component/ComponentMocks.h"
//#include "CCore/Component/ChildManagedComposite/TMock.h"
//#include "CCore/Component/ChildManagedComposite/ChildManagementMocks.h"
//
//TEST(CNHierarchyNodeTest, testAdd_AddsComponentToChildren) {
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
//    ASSERT_THAT(sut->getChildCount(), 3);
//    EXPECT_THAT(sut->getChild(0), first);
//    EXPECT_THAT(sut->getChild(1), second);
//    EXPECT_THAT(sut->getChild(2), third);
//}
//
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
//
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
//
//TEST(CNHierarchyNodeTest, testGetContent_ReturnsContens) {
//    TMockPtr content = TMock::getNewInstance();
//    CNHierarchyNodePtr<TMock> sut = CNHierarchyNode<TMock>::getNewInstance(content);
//
//    EXPECT_THAT(sut->getContent(), content);
//}