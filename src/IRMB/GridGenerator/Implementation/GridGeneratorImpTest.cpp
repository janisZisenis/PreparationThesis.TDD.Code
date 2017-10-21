#include <gmock/gmock.h>
#include "GridGeneratorImp.h"
#include "LViCE/GridGenerator/GridGeneratorVisitorMocks.h"
#include "CCore/Visitor/VisitorMocks.h"
#include "CCore/Visitor/VisitorCastException.h"

TEST(GridGeneratorImpTest, testIfVisitorHasFalseType_AcceptThrowsVisitorCastException) {
    GridGeneratorImpPtr sut = GridGeneratorImp::getNewInstance("Name", 0, 0, 0, 0, "Distribution");
    CCore::VisitorDummyPtr notConvertableVisitor = CCore::VisitorDummy::getNewInstance();

    EXPECT_THROW(sut->accept(notConvertableVisitor), CCore::VisitorCastException);
}

TEST(GridGeneratorTest, testIfVisitorHasCorrectType_AcceptShouldTriggerVisitorToVisitTheGridGenerator) {
    GridGeneratorImpPtr sut = GridGeneratorImp::getNewInstance("Name", 0, 0, 0, 0, "Distribution");
    GridGeneratorVisitorSpyPtr visitor = GridGeneratorVisitorSpy::getNewInstance();

    sut->accept(visitor);

    EXPECT_THAT(visitor->getVisitedGridGenerator(), sut);
}
