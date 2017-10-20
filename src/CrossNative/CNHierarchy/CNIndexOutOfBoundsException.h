#ifndef CROSSNATIVE_INVALIDPATHEXCEPTION_H
#define CROSSNATIVE_INVALIDPATHEXCEPTION_H

#include <memory>
#include <string>

class CNIndexOutOfBoundsException : public std::exception {
    const char *what() const throw() override {
        return std::string("The index is out of bounds").c_str();
    }
};

#endif //CROSSNATIVE_INVALIDPATHEXCEPTION_H
