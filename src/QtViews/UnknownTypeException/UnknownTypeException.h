#ifndef IRMB_UNKNOWNTYPEEXCEPTION_H
#define IRMB_UNKNOWNTYPEEXCEPTION_H

class UnknownTypeException : public std::exception {
    const char *what() const throw() override {
        return std::string("The given subtype of the Visitable is unknown").c_str();
    }
};

#endif //IRMB_UNKNOWNTYPEEXCEPTION_H