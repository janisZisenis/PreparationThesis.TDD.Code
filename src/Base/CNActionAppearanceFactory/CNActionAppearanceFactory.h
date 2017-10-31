#ifndef CROSSNATIVE_ACTIONAPPEARANCEFACTORY_H
#define CROSSNATIVE_ACTIONAPPEARANCEFACTORY_H

#include <memory>
#include <string>
#include "Base/TransActionAppearances/CNTransActionAppearanceImp/CNTransActionStateValues.h"

class CNTransActionAppearance;
class CNTransActionAccessibility;
class CNTransActionState;
class CNTransActionTitle;

class CNActionAppearanceFactory;
typedef std::shared_ptr<CNActionAppearanceFactory> CNActionAppearanceFactoryPtr;

class CNActionAppearanceFactory {
public:
    static CNActionAppearanceFactoryPtr getNewInstance();
    virtual ~CNActionAppearanceFactory();
private:
    CNActionAppearanceFactory();

public:
    std::shared_ptr<CNTransActionAppearance> makeCNTransActionAppearance(std::shared_ptr<CNTransActionAccessibility> accessibility,
                                                                         std::shared_ptr<CNTransActionState> state,
                                                                         std::shared_ptr<CNTransActionTitle> title);
    std::shared_ptr<CNTransActionAppearance> makeCNFixedTransActionAppearance(bool accessibility,
                                                                              CNTransActionStateValues state,
                                                                              std::string title);

    std::shared_ptr<CNTransActionAccessibility> makeCNFixedActionAccessibility(bool accessibility);
    std::shared_ptr<CNTransActionState> makeCNFixedActionState(CNTransActionStateValues state);
    std::shared_ptr<CNTransActionTitle> makeCNFixedActionTitle(std::string title);
};

#endif //CROSSNATIVE_ACTIONAPPEARANCEFACTORY_H