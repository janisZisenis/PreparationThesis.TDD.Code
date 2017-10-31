#include <gmock/gmock.h>
#include "CNSelectionModelImp.h"
#include <Base/CNObserver/CNObserverTestDoubles.h>

class CNSelectionModelImpTest : public testing::Test {
protected:
    class CNObserverMock;
    typedef std::shared_ptr<CNObserverMock> CNObserverMockPtr;
    class CNObserverMock : public CNObserver {
    public:
        static CNObserverMockPtr getNewInstance(CNSelectionModelImpPtr selectionModel) {
            return CNObserverMockPtr(new CNObserverMock(selectionModel));
        }
        virtual ~CNObserverMock() {}
    protected:
        CNObserverMock(CNSelectionModelImpPtr selectionModel) : selectionModel(selectionModel) {}

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
        CNSelectionModelImpPtr selectionModel;
    };

    virtual CNObserverMockPtr makeCNObserverMock(CNSelectionModelImpPtr selectionModel) {
        return CNObserverMock::getNewInstance(selectionModel);
    }

    virtual CNSelectionModelImpPtr makeSelectionModelImp() {
        return CNSelectionModelImp::getNewInstance();
    }

    virtual CNObserverSpyPtr makeCBObserverSpy() {
        return CNObserverSpy::getNewInstance();
    }

    virtual void expectHasNoSelction(CNSelectionModelImpPtr sut) {
        bool actual = sut->hasSelection();

        std::string errorMessage = "CNSelectionModelImp should not have a selection, but it has!";
        EXPECT_FALSE(actual) << errorMessage;
    }

    virtual void expectHasSelection(CNSelectionModelImpPtr sut) {
        bool actual = sut->hasSelection();

        std::string errorMessage = "CNSelectionModelImp should have a selection, but it has not!";
        EXPECT_TRUE(actual) << errorMessage;
    }
    virtual void expectedWasUpdated(CNObserverSpyPtr observer) {
        bool actual = observer->wasUpdated();

        std::string errorMessage = "CNSelectionModelImp should have updated the CNObserver, but it has not!";
        EXPECT_TRUE(actual) << errorMessage;
    }
    virtual void expectedWasNotUpdated(CNObserverSpyPtr observer) {
        bool actual = observer->wasUpdated();

        std::string errorMessage = "CNSelectionModelImp should not have updated the CNObserver, but it has!";
        EXPECT_FALSE(actual) << errorMessage;
    }
};

TEST_F(CNSelectionModelImpTest, FreshInstance_ShouldNotHaveASelection) {
    CNSelectionModelImpPtr sut = CNSelectionModelImp::getNewInstance();

    expectHasNoSelction(sut);
}

TEST_F(CNSelectionModelImpTest, FreshInstance__SetValidIndex__ShouldHaveASelection) {
    CNSelectionModelImpPtr sut = CNSelectionModelImp::getNewInstance();

    sut->setSelectedIndex(CNHierarchyIndex({0}));

    expectHasSelection(sut);
}

TEST_F(CNSelectionModelImpTest, AttachedTwoObservers_DetachedOneObserver__SetSelectedIndex__ShouldUpdateAttachedObserver) {
    CNSelectionModelImpPtr sut = CNSelectionModelImp::getNewInstance();
    CNObserverSpyPtr first = makeCBObserverSpy();
    sut->attach(first);
    CNObserverSpyPtr second = makeCBObserverSpy();
    sut->attach(second);
    sut->detach(second);

    sut->setSelectedIndex(CNHierarchyIndex());

    expectedWasUpdated(first);
    expectedWasNotUpdated(second);
}

TEST_F(CNSelectionModelImpTest, AttachedObserver__SetSelectedIndexTo_1_2_3__ShouldUpdateAttachedObserverWithIndex_1_2_3) {
    CNSelectionModelImpPtr sut = CNSelectionModelImp::getNewInstance();
    CNObserverMockPtr observer = makeCNObserverMock(sut);
    observer->expectIndexDuringUpdate(CNHierarchyIndex({1, 2, 3}));
    sut->attach(observer);

    sut->setSelectedIndex(CNHierarchyIndex({1, 2, 3}));

    observer->verify();
}
