#ifndef CROSSNATIVE_NULLACCEPTOR_H
#define CROSSNATIVE_NULLACCEPTOR_H

#include "CrossNative/CNVisitor/CNVisitor.h"
#include "CrossNative/CNAcceptor/CNAcceptor.h"

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