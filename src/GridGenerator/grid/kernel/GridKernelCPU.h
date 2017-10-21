#ifndef GridKernelCPU_H
#define GridKernelCPU_H
#include "Core_EXPORT.h"

#include "global.h"
#include <string>
#include <vector>

#include "GridKernel.h"
#include "Grid.h"

class Transformator;
struct Triangle;
struct Vertex;
struct DoubfloPtr1D;

class Core_EXPORT GridKernelCPU : public GridKernel
{
public:
    GridKernelCPU(){};
    GridKernelCPU(struct BoundingBox &box, Transformator &trans, std::string direction, bool isCoarse);
    GridKernelCPU(struct BoundingBox &box, Transformator &trans, std::string direction);
    virtual ~GridKernelCPU();

    virtual void meshGrid(struct Triangle *triangles, int size);
    virtual void writeArrows(std::string name);
    virtual void floodFill(struct Vertex vec);
    virtual void copyDataFromGPU() {};

    

private:
    void initalUniformGrid3d();
    void initalUniformGrid3dOnlyFluids();
    void forEachTriangleCreateBoundingBox(struct Triangle *triangles, int nTriangles, struct DoubfloPtr1D neighborAngles);

    void buildTrianglesAroundTheChannel();

};

#endif
