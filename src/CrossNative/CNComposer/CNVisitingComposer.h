#ifndef CROSSNATIVE_VISITINGCOMPOSER_H
#define CROSSNATIVE_VISITINGCOMPOSER_H

#include <CrossNative/CrossNative_EXPORT.h>

#include "CNComposer.h"

class CNVisitor;

class CNVisitingComposer;
typedef std::shared_ptr<CNVisitingComposer> CNVisitingComposerPtr;
class CrossNative_EXPORT CNVisitingComposer : public CNComposer {
public:
    static CNVisitingComposerPtr getNewInstance(std::shared_ptr<CNVisitor> composing, std::shared_ptr<CNVisitor> decomposing);
    virtual ~CNVisitingComposer();

protected:
    CNVisitingComposer(std::shared_ptr<CNVisitor> composing, std::shared_ptr<CNVisitor> decomposing);

public:
    virtual void mount(std::shared_ptr<CNComponent> component) override;
    virtual void dismount(std::shared_ptr<CNComponent> component) override;

private:
    std::shared_ptr<CNVisitor> composing;
};

#endif //CROSSNATIVE_VISITINGCOMPOSER_H