#ifndef CROSSNATIVE_ITERATOREXCEPTION_H
#define CROSSNATIVE_ITERATOREXCEPTION_H

#include <string>

class CNIteratorOutOfBoundsException : public std::exception {
    const char *what() const throw() {
        return std::string("Iterator is out of bounds").c_str();
    }
};

#endif //CROSSNATIVE_ITERATOREXCEPTION_H