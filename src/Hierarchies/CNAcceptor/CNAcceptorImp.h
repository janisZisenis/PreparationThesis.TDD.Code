#ifndef CROSSNATIVE_ACCEPTORIMP_H
#define CROSSNATIVE_ACCEPTORIMP_H

#include "CNAcceptor.h"

template<typename CNVisitorType, typename CNVisitableType>
class CNAcceptorImp;

template<typename CNVisitorType, typename CNVisitableType>
using CNAcceptorImpPtr = std::shared_ptr<CNAcceptorImp<CNVisitorType, CNVisitableType> >;

template<typename CNVisitorType, typename CNVisitableType>
class CNAcceptorImp : public CNAcceptor {
public:
    virtual ~CNAcceptorImp() {};
private:
    CNAcceptorImp() {};

public:
    static CNAcceptorImpPtr<CNVisitorType, CNVisitableType> getNewInstance() {
        return CNAcceptorImpPtr<CNVisitorType, CNVisitableType>(new CNAcceptorImp<CNVisitorType, CNVisitableType>());
    };

    virtual void accept(std::shared_ptr<CNVisitor> visitor, std::shared_ptr<CNVisitable> visitable) override {
        std::shared_ptr<CNVisitorType> castedVisitor = cast(visitor);
        std::shared_ptr<CNVisitableType> castedVisitable = cast(visitable);

        if(!castedVisitor || !castedVisitable) throw CNVisitableVisitorMismatchException();

        castedVisitor->visit(castedVisitable);
    }

private:
    virtual std::shared_ptr<CNVisitableType> cast(std::shared_ptr<CNVisitable> visitable) {
        return std::dynamic_pointer_cast<CNVisitableType>(visitable);
    }
    virtual std::shared_ptr<CNVisitorType> cast(std::shared_ptr<CNVisitor> visitor) {
        return std::dynamic_pointer_cast<CNVisitorType>(visitor);
    }
};

#endif //CROSSNATIVE_ACCEPTORIMP_H