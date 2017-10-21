#ifndef CROSSNATIVE_INVALIDINDEXEXCEPTION_H
#define CROSSNATIVE_INVALIDINDEXEXCEPTION_H

#include <memory>
#include <string>

class CNInvalidIndexException : public std::exception {
    const char *what() const throw() override {
        return std::string("The CNHierarchyIndex is invalid").c_str();
    }
};

#endif //CROSSNATIVE_INVALIDINDEXEXCEPTION_H
