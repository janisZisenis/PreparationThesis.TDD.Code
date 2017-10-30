#ifndef CROSSNATIVE_ACCEPTOR_H
#define CROSSNATIVE_ACCEPTOR_H

#include <memory>
#include "Hierarchies/CNVisitable/CNVisitableVisitorMismatchException.h"

class CNVisitor;
class CNVisitable;

class CNAcceptor;
typedef std::shared_ptr<CNAcceptor> CNAcceptorPtr;

class CNAcceptor {
public:
    virtual void accept(std::shared_ptr<CNVisitor> visitor, std::shared_ptr<CNVisitable> visitable) = 0;
};

#endif //CROSSNATIVE_ACCEPTOR_H
