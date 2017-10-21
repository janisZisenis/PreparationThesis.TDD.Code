#ifndef PolyDataWriter_h
#define PolyDataWriter_h

#include "VTKWriter/VTKWriter_EXPORT.h"
#include <string>
#include <memory>

class PolyDataWriter {
public:
    VTKWriter_EXPORT PolyDataWriter();
    VTKWriter_EXPORT ~PolyDataWriter();

    VTKWriter_EXPORT void addVectorArrow(double start[3], double end[3]);
    VTKWriter_EXPORT void writePolyDataToFile(std::string filename);

private:
    class impl;
    impl* pimpl;
};

#endif
