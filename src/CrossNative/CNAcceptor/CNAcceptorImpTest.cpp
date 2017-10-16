#include "gmock/gmock.h"
#include "CNAcceptorImp.h"
#include "CrossNative/CNVisitor/CNVisitorTestDoubles.h"
#include "CrossNative/CNVisitable/CNVisitableTestDoubles.h"

class CNAcceptorImpTests : public testing::Test {
protected:
    class CNSpecificVisitable;
    typedef std::shared_ptr<CNSpecificVisitable> CNSpecificVisitablePtr;
    class CNSpecificVisitable : public CNVisitable{
    public:
        static CNSpecificVisitablePtr getNewInstance() {
            return CNSpecificVisitablePtr(new CNSpecificVisitable());
        }
        virtual ~CNSpecificVisitable() {}
    protected:
        CNSpecificVisitable() {}

    public:
        virtual void accept(CNVisitorPtr visitor) {}
    };

    class CNSpecificVisitor;
    typedef std::shared_ptr<CNSpecificVisitor> CNSpecificVisitorPtr;
    class CNSpecificVisitor : public CNVisitor{
    public:
        static CNSpecificVisitorPtr getNewInstance() {
            return CNSpecificVisitorPtr(new CNSpecificVisitor());
        }
        virtual ~CNSpecificVisitor() {}
    protected:
        CNSpecificVisitor() {}

    public:
        virtual void visit(CNSpecificVisitablePtr specificVisitable) {
            visited = specificVisitable;
        }

        virtual CNSpecificVisitablePtr getVisited() {
            return visited;
        }
    private:
        CNSpecificVisitablePtr visited;
    };

protected:
    template<typename CNVisitorType, typename CNVisitableType>
    CNAcceptorImpPtr<CNVisitorType, CNVisitableType> makeAcceptorImp() {
        return CNAcceptorImp<CNVisitorType, CNVisitableType>::getNewInstance();
    }

    virtual CNVisitableDummyPtr makeCNVisitableDummy() {
        return CNVisitableDummy::getNewInstance();
    }
    virtual CNSpecificVisitablePtr makeCNSpecificVisitable() {
        return CNSpecificVisitable::getNewInstance();
    }
    virtual CNVisitorDummyPtr makeCNVisitorDummy() {
        return CNVisitorDummy::getNewInstance();
    }
    virtual CNSpecificVisitorPtr makeCNSpecificVisitor() {
        return CNSpecificVisitor::getNewInstance();
    }

    virtual std::string getThrowsVisitableVisitorMismatchExceptionErrorMessage() {
        return "Should throw CNVisitableVisitorMismatchException, because of a mismatch between visitor and visitable, but it didn't!";
    }
    virtual void expectVisitorHasVisitedExpectedVisitable(CNSpecificVisitorPtr visitor, CNSpecificVisitablePtr expected) {
        CNSpecificVisitablePtr actual = visitor->getVisited();

        std::string errorMessage = "The has not visited the expected visitable!";

        EXPECT_THAT(expected, actual) << errorMessage;
    }
};


TEST_F(CNAcceptorImpTests, FreshInstance_VisitableAndVisitorAreMatching__Accept__VisitorHasVisitedTheVisitable) {
    CNAcceptorImpPtr<CNSpecificVisitor, CNSpecificVisitable> sut = makeAcceptorImp<CNSpecificVisitor, CNSpecificVisitable>();

    CNSpecificVisitablePtr visitable = makeCNSpecificVisitable();
    CNSpecificVisitorPtr visitor = makeCNSpecificVisitor();

    sut->accept(visitor, visitable);

    expectVisitorHasVisitedExpectedVisitable(visitor, visitable);
}

TEST_F(CNAcceptorImpTests, FreshInstance_VisitorHasFalseType__Accept__ThrowsCNVisitableVisitorMismatchException) {
    CNAcceptorImpPtr<CNSpecificVisitor, CNSpecificVisitable> sut = makeAcceptorImp<CNSpecificVisitor, CNSpecificVisitable>();

    CNVisitorDummyPtr visitorWithFalseType = makeCNVisitorDummy();
    CNSpecificVisitablePtr visitable = makeCNSpecificVisitable();

    std::string errorMessage = getThrowsVisitableVisitorMismatchExceptionErrorMessage();
    ASSERT_THROW(sut->accept(visitorWithFalseType, visitable), CNVisitableVisitorMismatchException) << errorMessage;
}

TEST_F(CNAcceptorImpTests, FreshInstance_VisitableHasFalseType__Accept__ThrowsCNVisitableVisitorMismatchException) {
    CNAcceptorImpPtr<CNSpecificVisitor, CNSpecificVisitable> sut = makeAcceptorImp<CNSpecificVisitor, CNSpecificVisitable>();

    CNSpecificVisitorPtr visitor = makeCNSpecificVisitor();
    CNVisitableDummyPtr visitableWithFalseType = makeCNVisitableDummy();

    std::string errorMessage = getThrowsVisitableVisitorMismatchExceptionErrorMessage();
    ASSERT_THROW(sut->accept(visitor, visitableWithFalseType), CNVisitableVisitorMismatchException) << errorMessage;
}
