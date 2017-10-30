#ifndef CODEBASEIMP_ACTIONAPPEARANCEFACTORY_H
#define CODEBASEIMP_ACTIONAPPEARANCEFACTORY_H

#include <memory>
#include <string>
#include "Base/CBTransActionAppearance/CBActionStates.h"

class CBTransActionAppearance;
class CBActionAccessibility;
class CBActionState;
class CBActionTitle;

class CBActionAppearanceFactory;
typedef std::shared_ptr<CBActionAppearanceFactory> CBActionAppearanceFactoryPtr;

class CBActionAppearanceFactory {
public:
    static CBActionAppearanceFactoryPtr getNewInstance();
    virtual ~CBActionAppearanceFactory();
private:
    CBActionAppearanceFactory();

public:
    std::shared_ptr<CBTransActionAppearance> makeCBTransActionAppearance(std::shared_ptr<CBActionAccessibility> accessibility,
                                                                         std::shared_ptr<CBActionState> state,
                                                                         std::shared_ptr<CBActionTitle> title);
    std::shared_ptr<CBTransActionAppearance> makeCBFixedTransActionAppearance(bool accessibility,
                                                                              CBActionStates state,
                                                                              std::string title);

    std::shared_ptr<CBActionAccessibility> makeCBFixedActionAccessibility(bool accessibility);
    std::shared_ptr<CBActionState> makeCBFixedActionState(CBActionStates state);
    std::shared_ptr<CBActionTitle> makeCBFixedActionTitle(std::string title);
};

#endif //CODEBASEIMP_ACTIONAPPEARANCEFACTORY_H