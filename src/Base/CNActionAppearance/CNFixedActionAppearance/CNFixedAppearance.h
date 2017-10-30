#ifndef CROSSNATIVE_FIXEDAPPEARANCE_H
#define CROSSNATIVE_FIXEDAPPEARANCE_H

#include <Base/CNTransActionAppearance/CNTransActionAppearance.h>

class CNActionAccessibility;
class CNActionState;
class CNActionTitle;

class CNFixedAppearance;
typedef std::shared_ptr<CNFixedAppearance> CNFixedAppearancePtr;

class CNFixedAppearance : public CNTransActionAppearance {
public:
    static CNFixedAppearancePtr getNewInstance(bool accessibility,
                                               CNActionStates state,
                                               std::string title);
    virtual ~CNFixedAppearance();
private:
    CNFixedAppearance(bool accessibility,
                      CNActionStates state,
                      std::string title);

public:
    virtual bool isAccessible() override;
    CNActionStates getState() override;
    std::string getTitle() override;

private:
    bool accessibility;
    CNActionStates state;
    std::string title;
};

#endif //CROSSNATIVE_FIXEDAPPEARANCE_H