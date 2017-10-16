#ifndef CROSSNATIVE_VISITABLEVISITORMISMATCHEXCEPTION_H
#define CROSSNATIVE_VISITABLEVISITORMISMATCHEXCEPTION_H

#include <string>

class CNVisitableVisitorMismatchException : public std::exception {
    const char *what() const throw() override {
        return "CNVisitable and CNVisitor are mismatching!";
    };
};

#endif //CROSSNATIVE_VISITABLEVISITORMISMATCHEXCEPTION_H