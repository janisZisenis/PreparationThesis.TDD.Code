#ifndef CROSSNATIVE_ACCEPTOR_H
#define CROSSNATIVE_ACCEPTOR_H

#include <memory>

class CNVisitableVisitorMismatchException : public std::exception {
    const char *what() const throw() override {
        return "CNVisitable and CNVisitor are mismatching!";
    };
};

class CNVisitor;
class CNVisitable;

class CNAcceptor;
typedef std::shared_ptr<CNAcceptor> CNAcceptorPtr;

class CNAcceptor {
public:
    virtual void accept(std::shared_ptr<CNVisitor> visitor, std::shared_ptr<CNVisitable> visitable) = 0;
};

#endif //CROSSNATIVE_ACCEPTOR_H
