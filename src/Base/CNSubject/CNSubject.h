#ifndef CROSSNATIVE_SUBJECT_H
#define CROSSNATIVE_SUBJECT_H

#include <memory>
#include <vector>

class CNObserver;

class CNSubject;
typedef std::shared_ptr<CNSubject> CNSubjectPtr;

class CNSubject {
public:
    static CNSubjectPtr getNewInstance();
    virtual ~CNSubject();

protected:
    CNSubject();

public:
    virtual void attach(std::shared_ptr<CNObserver> observer);
    virtual void detach(std::shared_ptr<CNObserver> observer);
    virtual void notifyObservers();

private:
    void removeObserver(int index);

    std::vector< std::weak_ptr<CNObserver> > observers;
};

#endif //CROSSNATIVE_SUBJECT_H