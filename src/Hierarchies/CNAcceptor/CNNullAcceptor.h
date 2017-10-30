#ifndef CROSSNATIVE_NULLACCEPTOR_H
#define CROSSNATIVE_NULLACCEPTOR_H

#include "Hierarchies/CNVisitor/CNVisitor.h"
#include "CNAcceptor.h"

class CNNullAcceptor;
typedef std::shared_ptr<CNNullAcceptor> NullAcceptorPtr;

class CNNullAcceptor : public CNAcceptor {
public:
    virtual ~CNNullAcceptor() {};

    static NullAcceptorPtr getNewInstance() {
        return NullAcceptorPtr(new CNNullAcceptor());
    };

    virtual void accept(std::shared_ptr<CNVisitor> visitor, std::shared_ptr<CNVisitable> visitable) override {};
};

#endif //CROSSNATIVE_NULLACCEPTOR_H