#include <gmock/gmock.h>
#include "SelectionModelImp.h"
#include "CodeBase/CBObserver/CBObserverMocks.h"

class SelectionModelImpTest : public testing::Test {
protected:
    class CBObserverMock;
    typedef std::shared_ptr<CBObserverMock> CBObserverMockPtr;
    class CBObserverMock : public CBObserver {
    public:
        static CBObserverMockPtr getNewInstance(SelectionModelImpPtr selectionModel) {
            return CBObserverMockPtr(new CBObserverMock(selectionModel));
        }
        virtual ~CBObserverMock() {}
    protected:
        CBObserverMock(SelectionModelImpPtr selectionModel) : selectionModel(selectionModel) {}

    public:
        void update() override {
            actual = selectionModel->getSelectedIndex();
        }

        virtual void expectIndexDuringUpdate(CNHierarchyIndex index) {
            expected = index;
        }

        virtual void verify() {
            std::string errorMessage = "The index during update should be " + expected.toString()
                                       + ". Instead it is " + actual.toString()  + "!";
            EXPECT_THAT(actual, testing::Eq(expected)) << errorMessage;
        }
    private:
        bool updated = false;
        CNHierarchyIndex expected;
        CNHierarchyIndex actual;
        SelectionModelImpPtr selectionModel;
    };

    virtual CBObserverMockPtr makeCBObserverMock(SelectionModelImpPtr selectionModel) {
        return CBObserverMock::getNewInstance(selectionModel);
    }

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

TEST_F(SelectionModelImpTest, AttachedObserver__SetSelectedIndexTo_1_2_3__ShouldUpdateAttachedObserverWithIndex_1_2_3) {
    SelectionModelImpPtr sut = SelectionModelImp::getNewInstance();
    CBObserverMockPtr observer = makeCBObserverMock(sut);
    observer->expectIndexDuringUpdate(CNHierarchyIndex({1, 2, 3}));
    sut->attach(observer);

    sut->setSelectedIndex(CNHierarchyIndex({1, 2, 3}));

    observer->verify();
}
