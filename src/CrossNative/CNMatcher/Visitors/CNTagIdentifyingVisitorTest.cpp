#include <gmock/gmock.h>
#include "CNTagIdentifyingVisitor.h"
#include "CrossNative/CNTagged/CNTaggedTestDoubles.h"

class CNTagIdentifyingVisitorTest : public testing::Test {
protected:
    virtual CNTagIdentifyingVisitorPtr makeCNTagIdentifyingVisitor(std::string tag) {
        return CNTagIdentifyingVisitor::getNewInstance(tag);
    }
    virtual CNTaggedStubPtr makeCNTaggedStub() {
        return CNTaggedStub::getNewInstance();
    }

    virtual void expectHasIdentified(CNTagIdentifyingVisitorPtr sut) {
        bool actual = sut->hasIdentified();

        std::string errorMessage = "CNTagIdentifyingVisitor should have identified the CNTagged, but it has not!";
        EXPECT_TRUE(actual) << errorMessage;
    }
};

TEST_F(CNTagIdentifyingVisitorTest, FreshInstance__VisitTaggedWithTheSameTag__ShouldIdentifyTagged) {
    CNTagIdentifyingVisitorPtr sut = makeCNTagIdentifyingVisitor("theTag");

    CNTaggedStubPtr tagged = makeCNTaggedStub();
    tagged->setTag("theTag");
    sut->visit(tagged);

    expectHasIdentified(sut);
}

