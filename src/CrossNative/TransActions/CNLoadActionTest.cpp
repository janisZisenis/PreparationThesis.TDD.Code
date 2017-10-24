#include <gmock/gmock.h>
#include "CNLoadAction.h"

class CNLoadActionTest : public testing::Test {
protected:
    virtual CNLoadActionPtr makeCNLoadAction() {
        return CNLoadAction::getNewInstance();
    }
};

TEST_F(CNLoadActionTest, asdf) {
    EXPECT_TRUE(false);
}