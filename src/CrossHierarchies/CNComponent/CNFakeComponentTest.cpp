#include "gmock/gmock.h"
#include "CNFakeComponent.h"
#include "CNComponentTestDoubles.h"
#include "CrossHierarchies/CNVisitor/CNVisitorTestDoubles.h"

class CNFakeComponentTest : public testing::Test {
protected:
    virtual CNFakeComponentPtr makeCNFakeComponent() {
        return CNFakeComponent::getNewInstance();
    }

    virtual CNComponentPtr makeCNComponentDummy() {
        return CNComponentDummy::getNewInstance();
    }
    virtual CNVisitorPtr makeCNVisitorDummy() {
        return CNVisitorDummy::getNewInstance();
    }
    virtual CNFakeComponentVisitorSpyPtr makeCNFakeComponentVisitorSpy() {
        return CNFakeComponentVisitorSpy::getNewInstance();
    }

    virtual void expectIsParentOf(CNFakeComponentPtr parent, CNComponentPtr child) {
        bool actual = parent->isParentOf(child);

        std::string errorMessage = "CNFakeComponent should be parent of CNComponent, but it is not!";
        EXPECT_TRUE(actual) << errorMessage;
    }
    virtual void expectIsNotParentOf(CNFakeComponentPtr parent, CNComponentPtr child) {
        bool actual = parent->isParentOf(child);

        std::string errorMessage = "CNFakeComponent should not be parent of CNComponent, but it is!";
        EXPECT_FALSE(actual) << errorMessage;
    }
    virtual void expectHasChildCount(CNFakeComponentPtr sut, int childCount) {
        int expected = childCount;
        int actual = sut->getChildCount();

        std::string errorMessage = "The CNFakeComponent should have child count "
                                   + std::to_string(expected) + ". Instead it has " + std::to_string(actual) + "!";
        EXPECT_THAT(actual, testing::Eq(expected)) << errorMessage;
    }
    virtual void expectHasChildAtPosition(CNFakeComponentPtr sut, CNComponentPtr child ,int childPos) {
        CNComponentPtr expected = child;
        CNComponentPtr actual = sut->getChild(childPos);

        assertIsValidChildPosition(sut, childPos);

        std::string errorMessage = "The CNFakeComponent should have the child at position "
                                   + std::to_string(childPos) + ", but it has not!";
        EXPECT_THAT(actual, testing::Eq(expected)) << errorMessage;
    }
    virtual void assertIsValidChildPosition(CNFakeComponentPtr sut, int childPos) {
        int expected = childPos;
        int actual = sut->getChildCount();

        std::string errorMessage = "CNFakeComponent should have a valid child position of " + std::to_string(childPos) + ", but it has not!";
        ASSERT_THAT(actual, testing::Ge(expected)) << errorMessage;
    }
    virtual void expectVisitorHasVisitedSUT(CNFakeComponentVisitorSpyPtr visitor, CNFakeComponentPtr sut) {
        CNFakeComponentPtr expected = sut;
        CNFakeComponentPtr actual = visitor->getVisited();

        std::string errorMessage = "CNFakeComponentVisitor should have visited the SUT, but it has not!";
        EXPECT_THAT(actual, testing::Eq(expected)) << errorMessage;
    }
};

TEST_F(CNFakeComponentTest, FreshInstance__ShouldNotBeParentOfChild) {
    CNFakeComponentPtr sut = makeCNFakeComponent();

    CNComponentPtr child = makeCNComponentDummy();

    expectIsNotParentOf(sut, child);
}

TEST_F(CNFakeComponentTest, FreshInstance__AddChild__ShouldBeParentOfAddedChild) {
    CNFakeComponentPtr sut = makeCNFakeComponent();

    CNComponentPtr child = makeCNComponentDummy();
    sut->add(child);

    expectIsParentOf(sut, child);
}

TEST_F(CNFakeComponentTest, AddedChild__RemoveChild__ShouldNotBeParentOfRemovedChildAnymore) {
    CNFakeComponentPtr sut = makeCNFakeComponent();
    CNComponentPtr child = makeCNComponentDummy();
    sut->add(child);

    sut->remove(child);

    expectIsNotParentOf(sut, child);
}

TEST_F(CNFakeComponentTest, FreshInstance__RemoveChild__ShouldThrowCNChildNotFoundException) {
    CNFakeComponentPtr sut = makeCNFakeComponent();

    CNComponentPtr child = makeCNComponentDummy();

    std::string errorMessage = "CNFakeComponent should throw CNChildNotFoundException, but it did not!";
    EXPECT_THROW(sut->remove(child), CNChildNotFoundException);
}

TEST_F(CNFakeComponentTest, FreshInstance__InsertChildWithChildPos0__ShouldBeParentOfChild) {
    CNFakeComponentPtr sut = makeCNFakeComponent();

    CNComponentPtr child = makeCNComponentDummy();
    sut->insert(child, 0);

    expectIsParentOf(sut, child);
}

TEST_F(CNFakeComponentTest, FreshInstance__InsertCHildWithChildPos1__ShouldThrowCNInvalidInsertingPositionException) {
    CNFakeComponentPtr sut = makeCNFakeComponent();

    CNComponentPtr child = makeCNComponentDummy();

    std::string errorMessage = "CNFakeComponent should throw CNInvalidInsertingPositionException, but it did not!";
    EXPECT_THROW(sut->insert(child, 1), CNInvalidInsertingPositionException);
}

TEST_F(CNFakeComponentTest, AddedTwoChildren_InsertedOneChildren__RemoveInsertedChildren__ShouldHaveChildCount2) {
    CNFakeComponentPtr sut = makeCNFakeComponent();
    sut->add(makeCNComponentDummy());
    sut->add(makeCNComponentDummy());
    CNComponentPtr child = makeCNComponentDummy();
    sut->insert(child, 0);

    sut->remove(child);

    expectHasChildCount(sut, 2);
}

TEST_F(CNFakeComponentTest, AddedChild__AddChild__ShouldStoreTheSecondChildAtChildPosition1) {
    CNFakeComponentPtr sut = makeCNFakeComponent();
    CNComponentPtr first = makeCNComponentDummy();
    sut->add(first);

    CNComponentPtr second = makeCNComponentDummy();
    sut->add(second);

    expectHasChildAtPosition(sut, second, 1);
}

TEST_F(CNFakeComponentTest, AddedChild__InsertChildWithChildPosition0__ShouldStoreTheSecondCNComponentAtChildPosition0) {
    CNFakeComponentPtr sut = makeCNFakeComponent();
    CNComponentPtr first = makeCNComponentDummy();
    sut->add(first);

    CNComponentPtr second = makeCNComponentDummy();
    sut->insert(second, 0);

    expectHasChildAtPosition(sut, second, 0);
}

TEST_F(CNFakeComponentTest, AddedChild__GetChildWithChildPosition1__ShouldThrowCNInvalidChildPositionException) {
    CNFakeComponentPtr sut = makeCNFakeComponent();
    CNComponentPtr first = makeCNComponentDummy();
    sut->add(first);

    std::string errorMessage = "CNFakeComponent should throw CNInvalidChildPositionException, but it does not!";
    EXPECT_THROW(sut->getChild(1), CNInvalidChildPositionException) << errorMessage;
}

TEST_F(CNFakeComponentTest, AddedTwoChildren__RemoveChildWithChildPosition0__ShouldStoreTheSecondChildAtChildPosition0) {
    CNFakeComponentPtr sut = makeCNFakeComponent();
    sut->add(makeCNComponentDummy());
    CNComponentPtr child = makeCNComponentDummy();
    sut->add(child);

    sut->remove(0);

    expectHasChildAtPosition(sut, child, 0);
}

TEST_F(CNFakeComponentTest, FreshInstance__RemoveChildWithChildPosition1__ShouldThrowCNInvalidChildPositionException) {
    CNFakeComponentPtr sut = makeCNFakeComponent();

    std::string errorMessage = "CNFakeComponent should throw CNInvalidChildPositionException, but it did not!";
    EXPECT_THROW(sut->remove(1), CNInvalidChildPositionException);
}

TEST_F(CNFakeComponentTest, FreshInstance__AcceptWithFalseVisitorSubType__ShouldThrowCNVisitableVisitorMismatchException) {
    CNFakeComponentPtr sut = makeCNFakeComponent();

    CNVisitorPtr visitor = makeCNVisitorDummy();

    std::string errorMessage = "CNFakeComponent should throw CNVisitableVisitorMismatchException, but it did not!";
    EXPECT_THROW(sut->accept(visitor), CNVisitableVisitorMismatchException);
}

TEST_F(CNFakeComponentTest, FreshInstance__AcceptWithCNFakeComponentVisitor__VisitorShouldHaveVisitedTheSUT) {
    CNFakeComponentPtr sut = makeCNFakeComponent();

    CNFakeComponentVisitorSpyPtr visitor = makeCNFakeComponentVisitorSpy();
    sut->accept(visitor);

    expectVisitorHasVisitedSUT(visitor, sut);
}