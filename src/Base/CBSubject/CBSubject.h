#ifndef CODEBASEIMP_SUBJECT_H
#define CODEBASEIMP_SUBJECT_H

#include <memory>
#include <vector>

class CBObserver;

class CBSubject;
typedef std::shared_ptr<CBSubject> CBSubjectPtr;

class CBSubject {
public:
    static CBSubjectPtr getNewInstance();
    virtual ~CBSubject();

protected:
    CBSubject();

public:
    virtual void attach(std::shared_ptr<CBObserver> observer);
    virtual void detach(std::shared_ptr<CBObserver> observer);
    virtual void notifyObservers();

private:
    void removeObserver(int index);

    std::vector< std::weak_ptr<CBObserver> > observers;
};

#endif //CODEBASEIMP_SUBJECT_H