#include <gmock/gmock.h>
#include "CNFakeView.h"
#include "CNViewTestDoubles.h"

class CNFakeViewTest : public testing::Test {
protected:
    virtual CNFakeViewPtr makeCNFakeView() {
        return CNFakeView::getNewInstance();
    }
    virtual CNViewDummyPtr makeCNViewDummy() {
        return CNViewDummy::getNewInstance();
    }

    virtual std::string getNotInitializedIteratorErrorMessage() {
        return "Should throw CNNotInitializedIteratorException, but it threw nothing";
    }

    virtual void expectIteratorIsDone(CNIteratorPtr it) {
        std::string errorMessage = "The Iterator should be done, but is it not!";

        EXPECT_TRUE(it->isDone()) << errorMessage;
    }
};

TEST_F(CNFakeViewTest, FreshInstance_NotInitializedIterator__IteratorsCurrent__ShouldThrow_NotInitializedIteratorException) {
    CNFakeViewPtr sut = makeCNFakeView();
    CNIteratorPtr it = sut->makeIterator();

    EXPECT_THROW(it->current(), CNNotInitializedIteratorException) << getNotInitializedIteratorErrorMessage();
}

TEST_F(CNFakeViewTest, FreshInstance_NotInitializedIterator__IteratorsNext__ShouldThrow_NotInitializedIteratorException) {
    CNFakeViewPtr sut = makeCNFakeView();
    CNIteratorPtr it = sut->makeIterator();

    EXPECT_THROW(it->next(), CNNotInitializedIteratorException) << getNotInitializedIteratorErrorMessage();
}

TEST_F(CNFakeViewTest, FreshInstance_NotInitializedIterator__IteratorsIsDone__ShouldThrow_NotInitializedIteratorException) {
    CNFakeViewPtr sut = makeCNFakeView();
    CNIteratorPtr it = sut->makeIterator();

    EXPECT_THROW(it->isDone(), CNNotInitializedIteratorException) << getNotInitializedIteratorErrorMessage();
}