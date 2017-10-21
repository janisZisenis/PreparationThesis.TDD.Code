#include <gmock/gmock.h>
#include "SelectionModelImp.h"
#include "CodeBase/CBObserver/CBObserverMocks.h"

class SelectionModelImpTest : public testing::Test {
protected:
    virtual SelectionModelImpPtr makeSelectionModelImp() {
        return SelectionModelImp::getNewInstance();
    }

    virtual CBObserverSpyPtr makeCBObserverSpy() {
        return CBObserverSpy::getNewInstance();
    }

    virtual void expectHasNoSelction(SelectionModelImpPtr sut) {
        bool actual = sut->hasSelection();

        std::string errorMessage = "SelectionModelImp should not have a selection, but it has!";
        EXPECT_FALSE(actual) << errorMessage;
    }

    virtual void expectHasSelection(SelectionModelImpPtr sut) {
        bool actual = sut->hasSelection();

        std::string errorMessage = "SelectionModelImp should have a selection, but it has not!";
        EXPECT_TRUE(actual) << errorMessage;
    }
    virtual void expectedWasUpdated(CBObserverSpyPtr observer) {
        bool actual = observer->wasUpdated();

        std::string errorMessage = "SelectionModelImp should have updated the CBObserver, but it has not!";
        EXPECT_TRUE(actual) << errorMessage;
    }
    virtual void expectedWasNotUpdated(CBObserverSpyPtr observer) {
        bool actual = observer->wasUpdated();

        std::string errorMessage = "SelectionModelImp should not have updated the CBObserver, but it has!";
        EXPECT_FALSE(actual) << errorMessage;
    }
};

TEST_F(SelectionModelImpTest, FreshInstance_ShouldNotHaveASelection) {
    SelectionModelImpPtr sut = SelectionModelImp::getNewInstance();

    expectHasNoSelction(sut);
}

TEST_F(SelectionModelImpTest, FreshInstance__SetValidIndex__ShouldHaveASelection) {
    SelectionModelImpPtr sut = SelectionModelImp::getNewInstance();

    sut->setSelectedIndex(CNHierarchyIndex({0}));

    expectHasSelection(sut);
}

TEST_F(SelectionModelImpTest, AttachedTwoObservers_DetachedOneObserver__SetSelectedIndex__ShouldUpdateAttachedObserver) {
    SelectionModelImpPtr sut = SelectionModelImp::getNewInstance();
    CBObserverSpyPtr first = makeCBObserverSpy();
    sut->attach(first);
    CBObserverSpyPtr second = makeCBObserverSpy();
    sut->attach(second);
    sut->detach(second);

    sut->setSelectedIndex(CNHierarchyIndex());

    expectedWasUpdated(first);
    expectedWasNotUpdated(second);
}

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
