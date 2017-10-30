#include <gmock/gmock.h>

#include "CBSubject.h"
#include "Base/CBObserver/CBObserverMocks.h"

class CBSubjectTests : public testing::Test {
protected:
    virtual CBSubjectPtr makeCBSubject() {
        return CBSubject::getNewInstance();
    }
    virtual CBObserverSpyPtr makeCBObserverSpy() {
        return CBObserverSpy::getNewInstance();
    }

    virtual void expectObserverIsUpdated(CBObserverSpyPtr observer) {
        bool result = observer->wasUpdated();

        std::string errorMessage = "CBObserver should be updated, but it was not updated!";

        EXPECT_TRUE(result) << errorMessage;
    }
    virtual void expectObserverIsNotUpdated(CBObserverSpyPtr observer) {
        bool result = observer->wasUpdated();

        std::string errorMessage = "CBObserver should not be updated, but it was updated!";

        EXPECT_FALSE(result) << errorMessage;
    }
};

TEST_F(CBSubjectTests, _2ObserversAttachted_1ObserverDetached__Notify__UpdatesAttachedObserver) {
    CBSubjectPtr sut = makeCBSubject();
    CBObserverSpyPtr first = makeCBObserverSpy();
    CBObserverSpyPtr second = makeCBObserverSpy();
    sut->attach(first);
    sut->attach(second);
    sut->detach(first);

    sut->notifyObservers();

    expectObserverIsNotUpdated(first);
    expectObserverIsUpdated(second);
}