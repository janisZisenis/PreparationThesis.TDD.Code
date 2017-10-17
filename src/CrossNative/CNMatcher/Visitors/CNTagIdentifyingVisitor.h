#ifndef CROSSNATIVE_TAGIDENTIFYINGVISITOR_H
#define CROSSNATIVE_TAGIDENTIFYINGVISITOR_H

#include <CrossNative/CrossNative_EXPORT.h>
#include <string>
#include "CrossNative/CNMatcher/CNIdentifyingVisitor.h"
#include "CrossNative/CNTagged/CNTaggedVisitor.h"

class CNTagIdentifyingVisitor;
typedef std::shared_ptr<CNTagIdentifyingVisitor> CNTagIdentifyingVisitorPtr;

class CrossNative_EXPORT CNTagIdentifyingVisitor : public CNIdentifyingVisitor, public CNTaggedVisitor {
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
