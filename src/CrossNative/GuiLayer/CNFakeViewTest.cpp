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
    virtual std::string getIteratorOutOfBoundsErrorMessage() {
        return "Should throw CNIteratorOutOfBoundsException, but it threw nothing";
    }

    virtual void expectIteratorIsDone(CNIteratorPtr it) {
        std::string errorMessage = "The Iterator should be done, but is it not!";

        EXPECT_TRUE(it->isDone()) << errorMessage;
    }
    virtual void expectEquals(CNViewPtr actual, CNViewPtr expected) {
        std::string errorMessage = "The views are not equal, the iterator does not iterate in the correct order!";
        ASSERT_THAT(actual, testing::Eq(expected)) << errorMessage;
    }
};

TEST_F(CNFakeViewTest, FreshInstance_NotInitializedIterator__IteratorsCurrent__ShouldThrow_NotInitializedIteratorException) {
    CNFakeViewPtr sut = makeCNFakeView();
    CNIteratorPtr it = sut->makeIterator();

    std::string errorMessage = getNotInitializedIteratorErrorMessage();
    EXPECT_THROW(it->current(), CNNotInitializedIteratorException) << errorMessage;
}

TEST_F(CNFakeViewTest, FreshInstance_NotInitializedIterator__IteratorsNext__ShouldThrow_NotInitializedIteratorException) {
    CNFakeViewPtr sut = makeCNFakeView();
    CNIteratorPtr it = sut->makeIterator();

    std::string errorMessage = getNotInitializedIteratorErrorMessage();
    EXPECT_THROW(it->next(), CNNotInitializedIteratorException) << errorMessage;
}

TEST_F(CNFakeViewTest, FreshInstance_NotInitializedIterator__IteratorsIsDone__ShouldThrow_NotInitializedIteratorException) {
    CNFakeViewPtr sut = makeCNFakeView();
    CNIteratorPtr it = sut->makeIterator();

    std::string errorMessage = getNotInitializedIteratorErrorMessage();
    EXPECT_THROW(it->isDone(), CNNotInitializedIteratorException) << errorMessage;
}

TEST_F(CNFakeViewTest, _3ViewsAdded_InitializedIterator__IteratorShould_IterateChildrenInCorrectOrder) {
    CNFakeViewPtr sut = makeCNFakeView();
    CNViewPtr first = makeCNViewDummy();
    CNViewPtr second = makeCNViewDummy();
    CNViewPtr third = makeCNViewDummy();
    sut->add(first);
    sut->add(second);
    sut->add(third);

    CNIteratorPtr it = sut->makeIterator();
    it->first();

    expectEquals(first, it->current());
    it->next();

    expectEquals(second, it->current());
    it->next();

    expectEquals(third, it->current());
}

TEST_F(CNFakeViewTest, _3ViewsAdded_InitializedIterator__IteratorsNext_BeyondTheLastElement__IteratorsCurrent_ShouldThrow_CNIteratorOutOfBoundsException) {
    CNFakeViewPtr sut = makeCNFakeView();
    CNViewPtr first = makeCNViewDummy();
    CNViewPtr second = makeCNViewDummy();
    CNViewPtr third = makeCNViewDummy();
    sut->add(first);
    sut->add(second);
    sut->add(third);

    CNIteratorPtr it = sut->makeIterator();
    it->first();

    it->next();
    it->next();
    it->next();

    std::string errorMessage = getIteratorOutOfBoundsErrorMessage();
    ASSERT_THROW(it->current(), CNNotIteratorOutOfBoundsException) << errorMessage;
}

TEST_F(CNFakeViewTest, _3ViewsAdded_InitializedIterator__IteratorsNext_BeyondTheLastElement__IteratorShouldBeDone) {
    CNFakeViewPtr sut = makeCNFakeView();
    CNViewPtr first = makeCNViewDummy();
    CNViewPtr second = makeCNViewDummy();
    CNViewPtr third = makeCNViewDummy();
    sut->add(first);
    sut->add(second);
    sut->add(third);

    CNIteratorPtr it = sut->makeIterator();
    it->first();

    it->next();
    it->next();
    it->next();

    expectIteratorIsDone(it);
}