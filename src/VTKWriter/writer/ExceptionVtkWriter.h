#ifndef ExcpetionVtkWriter_h
#define ExcpetionVtkWriter_h

#include <exception>
#include <iostream>
#include <string>
#include <sstream>

class ExcpetionVtkWriter : public std::exception {
public:
    virtual const char* what() const throw() = 0;
};

class writePolyDataFileWithoutContent : public ExcpetionVtkWriter
{
    const char* what() const throw() {
        std::ostringstream getNr;
        getNr << "writePolyDataFileWithoutContent.";
        return getNr.str().c_str();
    }
};

#endif
