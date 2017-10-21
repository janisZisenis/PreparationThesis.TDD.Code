#include <gmock/gmock.h>
#include "SelectionModelImp.h"
#include "CodeBase/CBObserver/CBObserver.h"

class SelectionModelImpTest : public testing::Test {
protected:
    virtual SelectionModelImpPtr makeSelectionModelImp() {
        return SelectionModelImp::getNewInstance();
    }


    virtual void expectHasNoSelction(SelectionModelImpPtr sut) {
        bool actual = sut->hasSelection();

        std::string errorMessage = "SelectionModelImp should not have a selection, but it has!";
        EXPECT_FALSE(actual) << errorMessage;
    }
};

TEST_F(SelectionModelImpTest, FreshInstance_ShouldNotHaveASelection) {
    SelectionModelImpPtr sut = SelectionModelImp::getNewInstance();

    expectHasNoSelction(sut);
}

//TEST(SelectionModelImpTest, HasValidSelection_ReturnsTrueIfSelectedIndexIsBiggerThanOrEqual_0) {
//    SelectionModelImpPtr sut = SelectionModelImp::getNewInstance();
//
//    sut->setSelectedIndex(CNHierarchyIndex());
//    EXPECT_FALSE(sut->hasSelection());
//    EXPECT_TRUE(sut->getSelectedIndex() == CNHierarchyIndex());
//
//    sut->setSelectedIndex(CNHierarchyIndex({0}));
//    EXPECT_TRUE(sut->hasSelection());
//    EXPECT_TRUE(sut->getSelectedIndex() == CNHierarchyIndex({0}));
//}
//
//class ObserverMock;
//typedef std::shared_ptr<ObserverMock> ObserverMockPtr;
//class ObserverMock : public CBObserver {
//public:
//    static ObserverMockPtr getNewInstance(SelectionModelImpPtr selectionModel) {
//        return ObserverMockPtr(new ObserverMock(selectionModel));
//    }
//    virtual ~ObserverMock() {}
//protected:
//    ObserverMock(SelectionModelImpPtr selectionModel) : selectionModel(selectionModel) {}
//
//public:
//    void update() override {
//        updated = true;
//        updatedIndex = selectionModel->getSelectedIndex();
//    }
//
//    virtual void expectWasNotUpdated() {
//        EXPECT_FALSE(updated);
//    }
//    virtual void expectWasUpdatedWithIndex(CNHierarchyIndex index) {
//        EXPECT_TRUE(updatedIndex == index);
//    }
//
//private:
//    bool updated = false;
//    CNHierarchyIndex updatedIndex;
//    SelectionModelImpPtr selectionModel;
//};
//
//TEST(SelectionModelImpTest, SetSelectedIndex_ShouldFirstSetTheSelectedIndex_ThenUpdateAllAttachedObservers) {
//    SelectionModelImpPtr sut = SelectionModelImp::getNewInstance();
//
//    ObserverMockPtr first = ObserverMock::getNewInstance(sut);
//    sut->attach(first);
//    ObserverMockPtr second = ObserverMock::getNewInstance(sut);
//    sut->attach(second);
//    ObserverMockPtr third = ObserverMock::getNewInstance(sut);
//    sut->attach(third);
//
//    sut->detach(second);
//
//
//    sut->setSelectedIndex(CNHierarchyIndex({3, 4, 0}));
//
//    first->expectWasUpdatedWithIndex(CNHierarchyIndex({3, 4, 0}));
//    second->expectWasNotUpdated();
//    third->expectWasUpdatedWithIndex(CNHierarchyIndex({3, 4, 0}));
//}
