#ifndef CROSSNATIVE_INVALIDINSERTINGPOSITIONEXCEPTION_H
#define CROSSNATIVE_INVALIDINSERTINGPOSITIONEXCEPTION_H

#include <memory>
#include <string>

class CNInvalidInsertingPositionException : public std::exception {
    const char *what() const throw() override {
        return std::string("The given inserting position is out of bounds").c_str();
    }
};

#endif //CROSSNATIVE_INVALIDINSERTINGPOSITIONEXCEPTION_H