#define _CRT_SECURE_NO_DEPRECATE
#include "UnstructuredGridWrapper.h"
#include <iostream>

#include <VTKWriter/writer/UnstructuredGridWriter.h>

#include <stl/Triangle.h>
#include <stl/Vertex.h>
#include <stl/BoundingBox.h>
#include <grid/kernel/Grid.h>

UnstructuredGridWrapper::UnstructuredGridWrapper()
{
#ifndef __unix__
    this->writer = new UnstructuredGridWriter();
#endif
}

UnstructuredGridWrapper::~UnstructuredGridWrapper()
{
#ifndef __unix__
    delete this->writer;
#endif
}

void UnstructuredGridWrapper::addBoundingBox(double boundingBox[6], int type)
{
#ifndef __unix__
    this->writer->addBoundingBox(boundingBox, type);
#endif
}

void UnstructuredGridWrapper::addBoundingBox(BoundingBox box, int type)
{
#ifndef __unix__
    double b[6] = {(double)box.minX,(double)box.maxX,(double)box.minY,(double)box.maxY,(double)box.minZ,(double)box.maxZ };
    this->writer->addBoundingBox(b, type);
#endif
}

void UnstructuredGridWrapper::addVoxel(double node[3], double nodeNX[3], double nodeNY[3], double nodeNZ[3], double nodeNYNX[3], double nodeNZNY[3], double nodeNZNX[3], double nodeNZNYNX[3], int nodeTypes[8])
{
#ifndef __unix__
    this->writer->addVoxel(node, nodeNX, nodeNY, nodeNZ, nodeNYNX, nodeNZNY, nodeNZNX, nodeNZNYNX, nodeTypes);
#endif
}

void UnstructuredGridWrapper::addTriangle(double v1[3], double v2[3], double v3[3], int type[3])
{
#ifndef __unix__
    this->writer->addTriangle(v1, v2, v3, type);
#endif
}

void UnstructuredGridWrapper::addTriangle(Triangle t, int type[3])
{
#ifndef __unix__
    double v1[3] = { t.v1.x, t.v1.y, t.v1.z };
    double v2[3] = { t.v2.x, t.v2.y, t.v2.z };
    double v3[3] = { t.v3.x, t.v3.y, t.v3.z };

    this->writer->addTriangle(v1, v2, v3, type);
#endif
}

void UnstructuredGridWrapper::addTriangles(std::vector<Triangle> triangles)
{
#ifndef __unix__
    for (int i = 0; i < triangles.size(); i++) {
        double v1[3] = { triangles[i].v1.x, triangles[i].v1.y, triangles[i].v1.z };
        double v2[3] = { triangles[i].v2.x, triangles[i].v2.y, triangles[i].v2.z };
        double v3[3] = { triangles[i].v3.x, triangles[i].v3.y, triangles[i].v3.z };

        this->writer->addTriangle(v1, v2, v3, 0);
    }
#endif
}

void UnstructuredGridWrapper::addGridPoints(double grid[], int nx, int ny, int nz)
{
#ifndef __unix__
    this->writer->addGridPoints(grid, nx, ny, nz);
#endif
}

void UnstructuredGridWrapper::addGridPoint(int x, int y, int z, int type)
{
#ifndef __unix__
    this->writer->addGridPoint(x, y, z, type);
#endif
}

void UnstructuredGridWrapper::addGridPoint(Vertex v, int type)
{
#ifndef __unix__
    this->writer->addGridPoint((int)v.x, (int)v.y, (int)v.z, type);
#endif
}

void UnstructuredGridWrapper::writeUnstructuredGridToFile(std::string filename)
{
#ifndef __unix__
    std::string path = PATH_TO_DATA;
    filename = path + filename;
    this->writer->writeUnstructuredGridToFile(filename);
#endif
}

void UnstructuredGridWrapper::displayUnstructuredGrid()
{
#ifndef __unix__
    this->writer->displayUnstructuredGrid();
#endif
}

void UnstructuredGridWrapper::displayUnstructuredGrid(std::string filename)
{
#ifndef __unix__
    std::string path = PATH_TO_DATA;
    filename = path + filename;
    this->writer->displayUnstructuredGrid(filename);
#endif
}
