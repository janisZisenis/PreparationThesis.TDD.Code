#include <gmock/gmock.h>

#include "CNSubject.h"
#include "Base/CNObserver/CNObserverTestDoubles.h"

class CNSubjectTests : public testing::Test {
protected:
    virtual CNSubjectPtr makeCNSubject() {
        return CNSubject::getNewInstance();
    }
    virtual CNObserverSpyPtr makeCNObserverSpy() {
        return CNObserverSpy::getNewInstance();
    }

    virtual void expectObserverIsUpdated(CNObserverSpyPtr observer) {
        bool result = observer->wasUpdated();

        std::string errorMessage = "CNObserver should be updated, but it was not updated!";

        EXPECT_TRUE(result) << errorMessage;
    }
    virtual void expectObserverIsNotUpdated(CNObserverSpyPtr observer) {
        bool result = observer->wasUpdated();

        std::string errorMessage = "CNObserver should not be updated, but it was updated!";

        EXPECT_FALSE(result) << errorMessage;
    }
};

TEST_F(CNSubjectTests, _2ObserversAttachted_1ObserverDetached__Notify__UpdatesAttachedObserver) {
    CNSubjectPtr sut = makeCNSubject();
    CNObserverSpyPtr first = makeCNObserverSpy();
    CNObserverSpyPtr second = makeCNObserverSpy();
    sut->attach(first);
    sut->attach(second);
    sut->detach(first);

    sut->notifyObservers();

    expectObserverIsNotUpdated(first);
    expectObserverIsUpdated(second);
}