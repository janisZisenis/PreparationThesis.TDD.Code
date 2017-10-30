#ifndef CROSSNATIVE_ACTIONAPPEARANCEFACTORY_H
#define CROSSNATIVE_ACTIONAPPEARANCEFACTORY_H

#include <memory>
#include <string>
#include "Base/CNTransActionAppearance/CNActionStates.h"

class CNTransActionAppearance;
class CNActionAccessibility;
class CNActionState;
class CNActionTitle;

class CNActionAppearanceFactory;
typedef std::shared_ptr<CNActionAppearanceFactory> CNActionAppearanceFactoryPtr;

class CNActionAppearanceFactory {
public:
    static CNActionAppearanceFactoryPtr getNewInstance();
    virtual ~CNActionAppearanceFactory();
private:
    CNActionAppearanceFactory();

public:
    std::shared_ptr<CNTransActionAppearance> makeCNTransActionAppearance(std::shared_ptr<CNActionAccessibility> accessibility,
                                                                         std::shared_ptr<CNActionState> state,
                                                                         std::shared_ptr<CNActionTitle> title);
    std::shared_ptr<CNTransActionAppearance> makeCNFixedTransActionAppearance(bool accessibility,
                                                                              CNActionStates state,
                                                                              std::string title);

    std::shared_ptr<CNActionAccessibility> makeCNFixedActionAccessibility(bool accessibility);
    std::shared_ptr<CNActionState> makeCNFixedActionState(CNActionStates state);
    std::shared_ptr<CNActionTitle> makeCNFixedActionTitle(std::string title);
};

#endif //CROSSNATIVE_ACTIONAPPEARANCEFACTORY_H