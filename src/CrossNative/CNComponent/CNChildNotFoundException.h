#ifndef CROSSNATIVE_COMPONENTNOTFOUNDEXCEPTION_H
#define CROSSNATIVE_COMPONENTNOTFOUNDEXCEPTION_H

#include <memory>
#include <string>

class CNChildNotFoundException : public std::exception {
    const char *what() const throw() override {
        return std::string("The removed CNComponent was not found in children!").c_str();
    }
};

#endif //CROSSNATIVE_COMPONENTNOTFOUNDEXCEPTION_H