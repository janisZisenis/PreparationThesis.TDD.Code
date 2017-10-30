#ifndef CROSSNATIVE_TAGIDENTIFYINGVISITOR_H
#define CROSSNATIVE_TAGIDENTIFYINGVISITOR_H

#include <string>
#include "CrossHierarchies/CNMatcher/CNVisitingMatcher/CNIdentifyingVisitor.h"
#include "CrossHierarchies/CNTagged/CNTaggedVisitor.h"

class CNTagIdentifyingVisitor;
typedef std::shared_ptr<CNTagIdentifyingVisitor> CNTagIdentifyingVisitorPtr;

class CNTagIdentifyingVisitor : public CNIdentifyingVisitor, public CNTaggedVisitor {
public:
    static CNTagIdentifyingVisitorPtr getNewInstance(std::string tag);
    virtual ~CNTagIdentifyingVisitor();
protected:
    CNTagIdentifyingVisitor(std::string tag);

public:
    bool hasIdentified() override;

    void visit(std::shared_ptr<CNTagged> tagged) override;

private:
    std::string expectedTag;
    std::string actualTag;
};

#endif //CROSSNATIVE_TAGIDENTIFYINGVISITOR_H
