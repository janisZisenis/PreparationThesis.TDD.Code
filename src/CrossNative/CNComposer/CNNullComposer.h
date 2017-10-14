#ifndef CROSSNATIVE_NULLCOMPOSER_H
#define CROSSNATIVE_NULLCOMPOSER_H

#include "CNComposer.h"

class CNNullComposer;
typedef std::shared_ptr<CNNullComposer> CNNullComposerPtr;

class CNNullComposer : public CNComposer {
public:
    static CNNullComposerPtr getNewInstance() {
        return CNNullComposerPtr(new CNNullComposer());
    };
    virtual ~CNNullComposer() {};

protected:
    CNNullComposer() {}

public:
    virtual void mount(std::shared_ptr<CNVisitable> visitable) override {}
    virtual void dismount(std::shared_ptr<CNVisitable> visitable) override {}
};

#endif //CROSSNATIVE_NULLCOMPOSER_H