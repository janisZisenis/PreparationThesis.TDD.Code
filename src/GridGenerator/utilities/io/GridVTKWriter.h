#ifndef GridVTKWriter_h
#define GridVTKWriter_h

#include <string>
#include "Core_Export.h"

class Transformator;
struct Grid;

class Core_EXPORT GridVTKWriter
{
public:
static void writeGridToVTK(const struct Grid &grid, std::string name, Transformator trans, bool binaer);

private:
    GridVTKWriter();
    ~GridVTKWriter();

    static FILE *file;
    static bool binaer;
    static unsigned int size;
    static unsigned int nx;
    static unsigned int ny;
    static unsigned int nz;
    static unsigned int startX;
    static unsigned int startY;
    static unsigned int startZ;

    static void openFile(std::string name, std::string mode);
    static void initalValues(const struct Grid &grid);

    static void closeFile();
    static void writeHeader();
    static void writePoints(Transformator trans);
    static void writeCells();
    static void writeTypeHeader();
    static void writeTypes(const struct Grid &grid);
    static void end_line();
    static void force_big_endian(unsigned char *bytes);
    static void write_int(int val);
    static void write_float(float val);
};


#endif
