#ifndef GridKernel_H
#define GridKernel_H

#include "global.h"
#include <string>
#include "Core_EXPORT.h"

#include "Grid.h"

struct Triangle;
struct Vertex;

class Core_EXPORT GridKernel
{
public:
    virtual ~GridKernel() {};

    virtual void meshGrid(struct Triangle *triangles, int size) = 0;
    virtual void writeArrows(std::string name) = 0;
    virtual void floodFill(struct Vertex vec) = 0;
    virtual void copyDataFromGPU() = 0;

    struct Grid grid;

};

#endif
