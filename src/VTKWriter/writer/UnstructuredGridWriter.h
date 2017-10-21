#ifndef UnstructuredGridWriter_h
#define UnstructuredGridWriter_h
#include <string>
#include <vector>
#include "VTKWriter/VTKWriter_EXPORT.h"

class UnstructuredGridWriter {
public:
    VTKWriter_EXPORT UnstructuredGridWriter();
    VTKWriter_EXPORT ~UnstructuredGridWriter();
    VTKWriter_EXPORT void addBoundingBox(double boundingBox[6], int type);
    VTKWriter_EXPORT void addVoxel(double node[3], double nodeNX[3], double nodeNY[3], double nodeNZ[3],
                                          double nodeNYNX[3], double nodeNZNY[3], double nodeNZNX[3], double nodeNZNYNX[3], int nodeTypes[8]);

    VTKWriter_EXPORT void addCellCoords(std::vector<float> coordX, std::vector<float> coordY, std::vector<float> coordZ, std::vector<unsigned int> type);
    VTKWriter_EXPORT void buildCell(int index, int indexX, int indexY, int indexYX, int indexZ, int indexZX, int indexZY, int indexZYX);

    VTKWriter_EXPORT void addTriangle(double v1[3], double v2[3], double v3[3], int type[3]);
    VTKWriter_EXPORT void addGridPoints(double grid[], int nx, int ny, int nz);
    VTKWriter_EXPORT void addGridPoint(int x, int y, int z, int type);
    VTKWriter_EXPORT void writeUnstructuredGridToFile(std::string filename);

    VTKWriter_EXPORT void displayUnstructuredGrid();
    VTKWriter_EXPORT void displayUnstructuredGrid(std::string filename);

private:
    class impl;
    impl* pimpl;
};

#endif
