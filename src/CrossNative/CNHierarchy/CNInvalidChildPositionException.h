#ifndef CROSSNATIVE_INVALIDCHILDPOSITIONEXCEPTION_H
#define CROSSNATIVE_INVALIDCHILDPOSITIONEXCEPTION_H

#include <memory>
#include <string>

namespace CCore {

    class CNInvalidChildPositionException : public std::exception {
        const char *what() const throw() override {
            return std::string("The given child position for parent is invalid").c_str();
        }
    };

}

#endif //CROSSNATIVE_INVALIDCHILDPOSITIONEXCEPTION_H