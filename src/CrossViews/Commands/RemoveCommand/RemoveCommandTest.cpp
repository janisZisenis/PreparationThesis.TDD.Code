//#include <gmock/gmock.h>
//
//#include "RemoveCommand.h"
//#include "CCore/Component/ComponentMocks.h"
//#include "LViCE/HierarchicModel/API/InsertingHierarchicModelMocks.h"
//#include "LViCE/HierarchicModel/VisitableComposerPairMocks.h"
//
//TEST(RemoveCommandTest, testExecuteShouldTriggerTheModelToRemoveTheGivenIndex) {
//    InsertingHierarchicModelSpyPtr model = InsertingHierarchicModelSpy::getNewInstance();
//    CCore::HierarchyIndex removingIndex({0, 2, 7});
//    RemoveCommandPtr sut = RemoveCommand::getNewInstance(model, removingIndex);
//
//    sut->execute();
//
//    EXPECT_TRUE(model->getRemovedIndex() == removingIndex.parent());
//    EXPECT_THAT(model->getRemovedChildPos(), removingIndex.childPosition());
//}
//
//TEST(RemoveCommandTest, testUndoShouldTriggerTheModelToAddTheVisitableComposerPairAtTheRemovingIndex) {
//    InsertingHierarchicModelSpyPtr model = InsertingHierarchicModelSpy::getNewInstance();
//    CCore::VisitableDummyPtr visitable = CCore::VisitableDummy::getNewInstance();
//    VisitableComposerPairStubPtr pair = VisitableComposerPairStub::getNewInstance();
//    pair->setVisitable(visitable);
//
//    CCore::HierarchyIndex removingIndex({1, 5, 7});
//    model->setVisitableComposerPairForIndex(pair, removingIndex);
//
//    RemoveCommandPtr sut = RemoveCommand::getNewInstance(model, removingIndex);
//
//    sut->undo();
//
//    EXPECT_THAT(model->getInsertedPair(), pair);
//    EXPECT_TRUE(model->getInsertedChildPos() == removingIndex.childPosition());
//    EXPECT_TRUE(model->getInsertingIndex() == removingIndex.parent());
//}