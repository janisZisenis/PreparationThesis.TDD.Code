//#include <gmock/gmock.h>
//#include "CNHierarchy.h"
//#include "CCore/Component/ChildManagedComposite/TMock.h"
//
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
//
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
//
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
//
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
//
//TEST(CNHierarchyTest, testAddRemove_ShouldThrowIndexOutOfBoundsExceptionIfParentIndexIsOutOfBounds) {
//    CNHierarchyPtr<TMock> sut = CNHierarchy<TMock>::getNewInstance();
//
//    HierarchyIndex outOfBoundsIndex({1, 1, 66, 8});
//    EXPECT_THROW(sut->add(TMock::getNewInstance(), outOfBoundsIndex), IndexOutOfBoundsException);
//    EXPECT_THROW(sut->remove(TMock::getNewInstance(), outOfBoundsIndex), IndexOutOfBoundsException);
//}
//
//TEST(CNHierarchyTest, testInsertRemove_ShouldThrowIndexOutOfBoundsExceptionIfParentIndexIsOutOfBounds) {
//    CNHierarchyPtr<TMock> sut = CNHierarchy<TMock>::getNewInstance();
//
//    HierarchyIndex outOfBoundsIndex({1, 1, 66, 8});
//    int childPos = 0;
//    EXPECT_THROW(sut->insert(TMock::getNewInstance(), outOfBoundsIndex, childPos), IndexOutOfBoundsException);
//    EXPECT_THROW(sut->remove(outOfBoundsIndex, childPos), IndexOutOfBoundsException);
//}
//
//TEST(CNHierarchyTest, testGetChildCountForIndexWithIndexOutOfBounds_ShouldThrowIndexOutOfBoundsException) {
//    CNHierarchyPtr<TMock> sut = CNHierarchy<TMock>::getNewInstance();
//
//    HierarchyIndex outOfBoundsIndex({1, 6, 88, 99});
//    EXPECT_THROW(sut->getChildCountFor(outOfBoundsIndex), IndexOutOfBoundsException);
//}
//
//TEST(CNHierarchyTest, testRetrieveWithIndexOutOfBounds_ShouldThrowIndexOutOfBoundsException) {
//    CNHierarchyPtr<TMock> sut = CNHierarchy<TMock>::getNewInstance();
//
//    HierarchyIndex outOfBoundsIndex({1, 6, 88, 99});
//    EXPECT_THROW(sut->retrieve(outOfBoundsIndex), IndexOutOfBoundsException);
//}
//
//TEST(CNHierarchyTest, testRetrieveWithInvalidIndex_ShouldThrowIndexOutOfBoundsException) {
//    CNHierarchyPtr<TMock> sut = CNHierarchy<TMock>::getNewInstance();
//
//    HierarchyIndex invalidIndex;
//    EXPECT_THROW(sut->retrieve(invalidIndex), IndexOutOfBoundsException);
//}
//
//
//
//
//TEST(CNHierarchyTest, testBeginPreOrder_ReturnsIterator_WhichIteratesTheHierarchyContent_InPreOrder) {
//    CNHierarchyPtr<TMock> sut = CNHierarchy<TMock>::getNewInstance();
//
//    HierarchyIndex invalidIndex;
//
//    TMockPtr zeroth = TMock::getNewInstance();
//    HierarchyIndex zerothIndex({0});
//
//    TMockPtr first = TMock::getNewInstance();
//    HierarchyIndex firstIndex({1});
//
//    TMockPtr second = TMock::getNewInstance();
//    HierarchyIndex secondIndex({2});
//
//    TMockPtr zerothZeroth = TMock::getNewInstance();
//    TMockPtr zerothFirst = TMock::getNewInstance();
//    TMockPtr firstZeroth = TMock::getNewInstance();
//    TMockPtr firstFirst = TMock::getNewInstance();
//    TMockPtr secondZeroth = TMock::getNewInstance();
//    TMockPtr secondFirst = TMock::getNewInstance();
//
//    sut->add(zeroth, invalidIndex);
//    sut->add(first, invalidIndex);
//    sut->add(second, invalidIndex);
//    sut->add(zerothZeroth, zerothIndex);
//    sut->add(zerothFirst, zerothIndex);
//    sut->add(firstZeroth, firstIndex);
//    sut->add(firstFirst, firstIndex);
//    sut->add(secondZeroth, secondIndex);
//    sut->add(secondFirst, secondIndex);
//
//    IteratorPtr<TMock> it = sut->begin();
//    EXPECT_THAT(it->current(), zeroth);
//
//    it->next();
//    EXPECT_THAT(it->current(), zerothZeroth);
//
//    it->next();
//    EXPECT_THAT(it->current(), zerothFirst);
//
//    it->next();
//    EXPECT_THAT(it->current(), first);
//
//    it->next();
//    EXPECT_THAT(it->current(), firstZeroth);
//
//    it->next();
//    EXPECT_THAT(it->current(), firstFirst);
//
//    it->next();
//    EXPECT_THAT(it->current(), second);
//
//    it->next();
//    EXPECT_THAT(it->current(), secondZeroth);
//
//    it->next();
//    EXPECT_THAT(it->current(), secondFirst);
//
//    it->next();
//    EXPECT_TRUE(it->isDone());
//    EXPECT_THROW(it->current(), IteratorOutOfBoundsException);
//
//    it->next();
//    EXPECT_TRUE(it->isDone());
//}
//
//TEST(CNHierarchyTest, testBeginPostOrder_ReturnsIterator_WhichIteratesTheHierarchyContent_InPostOrder) {
//    CNHierarchyPtr<TMock> sut = CNHierarchy<TMock>::getNewInstance();
//
//    HierarchyIndex invalidIndex;
//
//    TMockPtr zeroth = TMock::getNewInstance();
//    HierarchyIndex zerothIndex({0});
//
//    TMockPtr first = TMock::getNewInstance();
//    HierarchyIndex firstIndex({1});
//
//    TMockPtr second = TMock::getNewInstance();
//    HierarchyIndex secondIndex({2});
//
//    TMockPtr zerothZeroth = TMock::getNewInstance();
//    TMockPtr zerothFirst = TMock::getNewInstance();
//    TMockPtr firstZeroth = TMock::getNewInstance();
//    TMockPtr firstFirst = TMock::getNewInstance();
//    TMockPtr secondZeroth = TMock::getNewInstance();
//    TMockPtr secondFirst = TMock::getNewInstance();
//
//    sut->add(zeroth, invalidIndex);
//    sut->add(first, invalidIndex);
//    sut->add(second, invalidIndex);
//    sut->add(zerothZeroth, zerothIndex);
//    sut->add(zerothFirst, zerothIndex);
//    sut->add(firstZeroth, firstIndex);
//    sut->add(firstFirst, firstIndex);
//    sut->add(secondZeroth, secondIndex);
//    sut->add(secondFirst, secondIndex);
//
//    IteratorPtr<TMock> it = sut->begin(PostOrder);
//    EXPECT_THAT(it->current(), zerothZeroth);
//
//    it->next();
//    EXPECT_THAT(it->current(), zerothFirst);
//
//    it->next();
//    EXPECT_THAT(it->current(), zeroth);
//
//    it->next();
//    EXPECT_THAT(it->current(), firstZeroth);
//
//    it->next();
//    EXPECT_THAT(it->current(), firstFirst);
//
//    it->next();
//    EXPECT_THAT(it->current(), first);
//
//    it->next();
//    EXPECT_THAT(it->current(), secondZeroth);
//
//    it->next();
//    EXPECT_THAT(it->current(), secondFirst);
//
//    it->next();
//    EXPECT_THAT(it->current(), second);
//
//    it->next();
//    EXPECT_TRUE(it->isDone());
//    EXPECT_THROW(it->current(), IteratorOutOfBoundsException);
//
//    it->next();
//    EXPECT_TRUE(it->isDone());
//}
//
//TEST(CNHierarchyTest, testBeginLevelOrder_ReturnsIterator_WhichIteratesTheHierarchyContent_InLevelOrder) {
//    CNHierarchyPtr<TMock> sut = CNHierarchy<TMock>::getNewInstance();
//
//    HierarchyIndex invalidIndex;
//
//    TMockPtr zeroth = TMock::getNewInstance();
//    HierarchyIndex zerothIndex({0});
//
//    TMockPtr first = TMock::getNewInstance();
//    HierarchyIndex firstIndex({1});
//
//    TMockPtr second = TMock::getNewInstance();
//    HierarchyIndex secondIndex({2});
//
//    TMockPtr zerothZeroth = TMock::getNewInstance();
//    TMockPtr zerothFirst = TMock::getNewInstance();
//    TMockPtr firstZeroth = TMock::getNewInstance();
//    TMockPtr firstFirst = TMock::getNewInstance();
//    TMockPtr secondZeroth = TMock::getNewInstance();
//    TMockPtr secondFirst = TMock::getNewInstance();
//
//    sut->add(zeroth, invalidIndex);
//    sut->add(first, invalidIndex);
//    sut->add(second, invalidIndex);
//    sut->add(zerothZeroth, zerothIndex);
//    sut->add(zerothFirst, zerothIndex);
//    sut->add(firstZeroth, firstIndex);
//    sut->add(firstFirst, firstIndex);
//    sut->add(secondZeroth, secondIndex);
//    sut->add(secondFirst, secondIndex);
//
//    IteratorPtr<TMock> it = sut->begin(LevelOrder);
//    EXPECT_THAT(it->current(), zeroth);
//
//    it->next();
//    EXPECT_THAT(it->current(), first);
//
//    it->next();
//    EXPECT_THAT(it->current(), second);
//
//    it->next();
//    EXPECT_THAT(it->current(), zerothZeroth);
//
//    it->next();
//    EXPECT_THAT(it->current(), zerothFirst);
//
//    it->next();
//    EXPECT_THAT(it->current(), firstZeroth);
//
//    it->next();
//    EXPECT_THAT(it->current(), firstFirst);
//
//    it->next();
//    EXPECT_THAT(it->current(), secondZeroth);
//
//    it->next();
//    EXPECT_THAT(it->current(), secondFirst);
//
//    it->next();
//    EXPECT_TRUE(it->isDone());
//    EXPECT_THROW(it->current(), IteratorOutOfBoundsException);
//
//    it->next();
//    EXPECT_TRUE(it->isDone());
//}
//
