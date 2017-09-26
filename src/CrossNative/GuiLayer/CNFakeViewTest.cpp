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

    virtual void expectIteratorIsDone(CNIteratorPtr it) {
        std::string errorMessage = "The Iterator should be done, but is it not!";

        EXPECT_TRUE(it->isDone()) << errorMessage;
    }
};

TEST_F(CNFakeViewTest, Fresh__makeIterator__ShouldProvideIterator_ThatIsAlreadyDone) {
    CNFakeViewPtr sut = makeCNFakeView();
    CNIteratorPtr it = sut->makeIterator();

    expectIteratorIsDone(it);
}