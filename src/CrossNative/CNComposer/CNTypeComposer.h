#ifndef CROSSNATIVE_VISITINGCOMPOSER_H
#define CROSSNATIVE_VISITINGCOMPOSER_H

#include <CrossNative/CrossNative_EXPORT.h>

#include "CNComposer.h"

class CNVisitor;

class CNTypeComposer;
typedef std::shared_ptr<CNTypeComposer> CNTypeComposerPtr;
class CrossNative_EXPORT CNTypeComposer : public CNComposer {
public:
    static CNTypeComposerPtr getNewInstance(std::shared_ptr<CNVisitor> mounting, std::shared_ptr<CNVisitor> dismounting);
    virtual ~CNTypeComposer();

protected:
    CNTypeComposer(std::shared_ptr<CNVisitor> mounting, std::shared_ptr<CNVisitor> dismounting);

public:
    virtual void mount(std::shared_ptr<CNComponent> component) override;
    virtual void dismount(std::shared_ptr<CNComponent> component) override;

private:
    std::shared_ptr<CNVisitor> mounting;
    std::shared_ptr<CNVisitor> dismounting;
};

#endif //CROSSNATIVE_VISITINGCOMPOSER_H