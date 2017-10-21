#ifndef CROSSNATIVE_NOTEXISTINGINDEXEXCEPTION_H
#define CROSSNATIVE_NOTEXISTINGINDEXEXCEPTION_H

#include <memory>
#include <string>

class CNNotExistingIndexException : public std::exception {
    const char *what() const throw() override {
        return std::string("The CNHierarchyIndex is not existing").c_str();
    }
};

#endif //CROSSNATIVE_NOTEXISTINGINDEXEXCEPTION_H
