#include "CNSubject.h"
#include "Base/CNObserver/CNObserver.h"

CNSubjectPtr CNSubject::getNewInstance() {
    return CNSubjectPtr(new CNSubject());
}
CNSubject::~CNSubject() {};

CNSubject::CNSubject() {};

void CNSubject::attach(CNObserverPtr observer) {
    observers.push_back(observer);
}

void CNSubject::detach(CNObserverPtr observer) {
    for(int i = 0; i < observers.size(); i++) {
        if(!observers[i].lock() || observers[i].lock() == observer)
            removeObserver(i--);
    }
}

void CNSubject::notifyObservers() {
    for(int i = 0; i < observers.size(); i++) {
        if(!observers[i].lock()) removeObserver(i--);

        observers[i].lock()->update();
    }
}

void CNSubject::removeObserver(int index) {
    observers.erase(observers.begin() + index);
}

