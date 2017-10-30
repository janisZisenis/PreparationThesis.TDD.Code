#ifndef CROSSNATIVE_VISITINGCOMPOSER_H
#define CROSSNATIVE_VISITINGCOMPOSER_H

#include "Hierarchies/CNComposer/CNComposer.h"

class CNVisitor;

class CNVisitingComposer;
typedef std::shared_ptr<CNVisitingComposer> CNVisitingComposerPtr;

class CNVisitingComposer : public CNComposer {
public:
    static CNVisitingComposerPtr getNewInstance(std::shared_ptr<CNVisitor> mounting, std::shared_ptr<CNVisitor> dismounting);
    virtual ~CNVisitingComposer();

protected:
    CNVisitingComposer(std::shared_ptr<CNVisitor> mounting, std::shared_ptr<CNVisitor> dismounting);

public:
    virtual void mount(std::shared_ptr<CNVisitable> visitable) override;
    virtual void dismount(std::shared_ptr<CNVisitable> visitable) override;

private:
    std::shared_ptr<CNVisitor> mounting;
    std::shared_ptr<CNVisitor> dismounting;
};

#endif //CROSSNATIVE_VISITINGCOMPOSER_H