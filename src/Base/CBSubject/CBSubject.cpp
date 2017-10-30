#include "CBSubject.h"
#include "Base/CBObserver/CBObserver.h"

CBSubjectPtr CBSubject::getNewInstance() {
    return CBSubjectPtr(new CBSubject());
}
CBSubject::~CBSubject() {};

CBSubject::CBSubject() {};

void CBSubject::attach(CBObserverPtr observer) {
    observers.push_back(observer);
}

void CBSubject::detach(CBObserverPtr observer) {
    for(int i = 0; i < observers.size(); i++) {
        if(!observers[i].lock() || observers[i].lock() == observer)
            removeObserver(i--);
    }
}

void CBSubject::notifyObservers() {
    for(int i = 0; i < observers.size(); i++) {
        if(!observers[i].lock()) removeObserver(i--);

        observers[i].lock()->update();
    }
}

void CBSubject::removeObserver(int index) {
    observers.erase(observers.begin() + index);
}

