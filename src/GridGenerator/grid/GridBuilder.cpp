#include "GridBuilder.h"
#include "mpi.h"

#include <stdio.h>
#include <iostream>
#include <grid/kernel/Grid.h>
#include <grid/kernel/GridKernelCPU.h>
#include <grid/Partition.h>

#include <stl/Triangle.h>
#include <stl/BoundingBox.h>
#include <utilities/io/GridVTKWriter.h>
#include <utilities/io/VTKWriterWrapper/UnstructuredGridWrapper.h>
#include <utilities/Transformator.h>
#include <utilities/Logger.h>

#include <utilities/io/STLReaderWriter.h>


GridBuilder::GridBuilder()
{

}

GridBuilder::~GridBuilder()
{

}

void GridBuilder::meshGeometry(std::string input, int level)
{
    checkLevel(level);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    //int numProcess = 8;
    //for (rank = 0; rank < numProcess; rank++) { // instead of MPI

        for (int i = 0; i < rankTasks.size(); i+=2) {

            int levelTask = rankTasks[i];
            int index = rankTasks[i+1];

            if (levelTask == level) {
                std::vector<struct Triangle>  triangles = STLReaderWriter::readSTL(boxes[level][index], input, transformators[level]);
                
                if (triangles.size() > 0)
                    this->gridKernels[level][index]->meshGrid(&triangles[0], (int)triangles.size());
                this->gridKernels[level][index]->copyDataFromGPU();
            }
        }

    //} // instead of MPI
  
}

void GridBuilder::flood(struct Vertex startFlood, int level)
{
    checkLevel(level);
    this->gridKernels[level][0]->floodFill(startFlood);
}

void GridBuilder::writeGridToVTK(std::string output, int level)
{
    checkLevel(level);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    for (int i = 0; i < rankTasks.size(); i += 2) {

        int levelTask = rankTasks[i];
        int index = rankTasks[i + 1];

        if (levelTask == level) {
            std::stringstream ss;
            ss << output << rank;
            GridVTKWriter::writeGridToVTK(this->gridKernels[level][index]->grid, ss.str(), this->transformators[level], false);
        }
    }
}

void GridBuilder::writeArrows(std::string output, int level)
{
    checkLevel(level);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    for (int i = 0; i < rankTasks.size(); i += 2) {

        int levelTask = rankTasks[i];
        int index = rankTasks[i + 1];

        if (levelTask == level) {
            this->gridKernels[level][index]->writeArrows(output);
        }
    }
    
}

void GridBuilder::writeSimulationFiles(std::string output, struct BoundingBox &nodesDelete, bool writeFilesBinary, int level)
{
    //checkLevel(level);
    //UnstructuredGridBuilder builder;
    //builder.buildUnstructuredGrid(this->gridKernels[level]->grid, nodesDelete);

    //std::vector<Node> coords = builder.getCoordsVec();
    //std::vector<std::vector<std::vector<doubflo> > > qs = builder.getQsValues();
    //SimulationFileWriter::writeSimulationFiles(output, coords, qs, writeFilesBinary, this->gridKernels[level]->grid, this->transformators[level]);
}

void GridBuilder::writeCells(std::string input, std::string name, bool writeFilesBinary)
{

}

std::shared_ptr<GridKernel> GridBuilder::getKernel(int level, int box)
{
    return this->gridKernels[level][box];
}

void GridBuilder::checkLevel(int level)
{
    if (level >= boxes.size()) { std::cout << "wrong level input... return to caller\n"; return; }
}
