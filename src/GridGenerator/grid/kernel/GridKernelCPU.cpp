#include "GridKernelCPU.h"

#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stack>

#include <grid/NodeValues.h>
#include <grid/distributions/Distribution.h>

#include <stl/TriangleNeighborFinder.h>
#include <stl/BoundingBox.h>

#include <utilities/Transformator.h>
#include <utilities/io/VTKWriterWrapper/UnstructuredGridWrapper.h>

#include <grid/Partition.h>
#include <utilities/Logger.h>


GridKernelCPU::GridKernelCPU(struct BoundingBox &box, Transformator &trans, std::string direction, bool isCoarse){

    /*-------------------------------alloc grid------------------------------------*/
    int nx = box.maxX - box.minX;
    int ny = box.maxY - box.minY;
    int nz = box.maxZ - box.minZ;
    Distribution d = DistributionHelper::getDistribution(direction);
    this->grid = Grid(NULL, box.minX, box.minY, box.minZ, nx, ny, nz, d);
    this->grid.field = new char[this->grid.size];

    if (isCoarse)
        this->initalUniformGrid3d();
    else
        this->initalUniformGrid3dOnlyFluids();
    /*------------------------------alloc Qs------------------------------------*/
    int size = (this->grid.d.dir_end + 1) * this->grid.size;
    doubflo sizeInMB = (int)(size * sizeof(doubflo) / (1024.f*1024.f));
    Logger::getInstance()->logTerminal("Allocating " + SSTR(sizeInMB) + " [MB] device memory for distributions.\n\n");
    this->grid.d.f = new doubflo[size](); // automatic initialized with zeros
}

GridKernelCPU::GridKernelCPU(struct BoundingBox &box, Transformator &trans, std::string direction){

    /*-------------------------------alloc grid------------------------------------*/
    int nx = box.maxX - box.minX;
    int ny = box.maxY - box.minY;
    int nz = box.maxZ - box.minZ;
    Distribution d = DistributionHelper::getDistribution(direction);
    this->grid = Grid(NULL, box.minX, box.minY, box.minZ, nx, ny, nz, d);
    this->grid.field = new char[this->grid.size];

    this->initalUniformGrid3d();
    /*------------------------------alloc Qs------------------------------------*/
    int size = (this->grid.d.dir_end + 1) * this->grid.size;
    doubflo sizeInMB = (int)(size * sizeof(doubflo) / (1024.f*1024.f));
    Logger::getInstance()->logTerminal("Allocating " + SSTR(sizeInMB) + " [MB] device memory for distributions.\n\n");
    this->grid.d.f = new doubflo[size](); // automatic initialized with zeros
}

GridKernelCPU::~GridKernelCPU() {
    delete[] this->grid.field;
    delete[] this->grid.d.f;
}

void GridKernelCPU::initalUniformGrid3d()
{
    Logger::getInstance()->logTerminal("-------------------------------------------\n");
    Logger::getInstance()->logTerminal("Initial field with fluid: \n");
    Logger::getInstance()->logTerminal("Field offset: " + SSTR(grid.startX) + "," + SSTR(grid.startY) + ", " + SSTR(grid.startZ) + "\n");
    Logger::getInstance()->logTerminal("Field dimension: " + SSTR(grid.nx) + ", " + SSTR(grid.ny) + ", " + SSTR(grid.ny) + "\n");
    Logger::getInstance()->logTerminal("Number of Nodes: " +  SSTR(grid.size) + "\n");
    time_t begin = clock();
    #pragma omp parallel for
    for (unsigned int i = 0; i < grid.size; i++){
        int x, y, z;
        grid.transIndexToCoords(i, x, y, z);
        if (x == grid.nx - 1) grid.field[i] = SOLID;
        else if (y == grid.ny - 1) grid.field[i] = SOLID;
        else if (z == grid.nz - 1) grid.field[i] = SOLID;
        else grid.field[i] = FLUID;
    }
    time_t end = clock();
    doubflo time = doubflo(end - begin) / CLOCKS_PER_SEC;
    Logger::getInstance()->logTerminal("time grid initialization: " + SSTR(time) + "s\n");
    Logger::getInstance()->logTerminal("-------------------------------------------\n\n");
}

void GridKernelCPU::initalUniformGrid3dOnlyFluids() {
    Logger::getInstance()->logTerminal("-------------------------------------------\n");
    Logger::getInstance()->logTerminal("Initial field with fluid: \n");
    Logger::getInstance()->logTerminal("Field offset: " + SSTR(grid.startX) + "," + SSTR(grid.startY) + ", " + SSTR(grid.startZ) + "\n");
    Logger::getInstance()->logTerminal("Field dimension: " + SSTR(grid.nx) + ", " + SSTR(grid.ny) + ", " + SSTR(grid.ny) + "\n");
    Logger::getInstance()->logTerminal("Number of Nodes: " + SSTR(grid.size) + "\n");
    time_t begin = clock();
    #pragma omp parallel for
    for (unsigned int i = 0; i < grid.size; i++){
        int x, y, z;
        grid.transIndexToCoords(i, x, y, z);
        grid.field[i] = FLUID;
    }
    time_t end = clock();
    doubflo time = (doubflo) (doubflo(end - begin) / CLOCKS_PER_SEC);
    Logger::getInstance()->logTerminal("time grid initialization: " + SSTR(time) + "s\n");
    Logger::getInstance()->logTerminal("-------------------------------------------\n\n");
}

void GridKernelCPU::meshGrid(struct Triangle *triangles, int nTriangles)
{
        /*-----------------------------find Neighbor-----------------------------------*/
        Logger::getInstance()->logTerminal("start calculating neighbors ...\n");
        clock_t  begin = clock();
        struct DoubfloPtr1D neighborAngles;
        neighborAngles.size = nTriangles * DIMENSION;
        neighborAngles.ptr = new doubflo[neighborAngles.size];
        TriangleNeighborFinder* finder = new TriangleNeighborFinder(triangles, nTriangles);
        finder->fillWithNeighborAngles(&neighborAngles, triangles);
        delete finder;

        clock_t end = clock();
        doubflo time = (doubflo)(doubflo(end - begin) / CLOCKS_PER_SEC);
        Logger::getInstance()->logTerminal("time calculating neighbors: "+ SSTR(time) + "s\n");
        Logger::getInstance()->logTerminal("... calculating neighbors finish...\n");

        /*-----------------------------start gridGen------------------------------------*/
        begin = clock();
        forEachTriangleCreateBoundingBox(triangles, nTriangles, neighborAngles);
        end = clock();
        time = (doubflo)(doubflo(end - begin) / CLOCKS_PER_SEC);
        Logger::getInstance()->logTerminal("time grid generation: " + SSTR(time) + "s\n");

        delete[] neighborAngles.ptr;
}


void GridKernelCPU::writeArrows(std::string name)
{
    
}


void GridKernelCPU::forEachTriangleCreateBoundingBox(struct Triangle *triangles, int nTriangles, struct DoubfloPtr1D neighborAngles){
    
    //#pragma omp parallel for shared(neighborAngles)
	for (int i = 0; i < nTriangles; i++){
        doubflo alphaAngles[3];
        alphaAngles[0] = neighborAngles.ptr[i * 3 + 0];
        alphaAngles[1] = neighborAngles.ptr[i * 3 + 1];
        alphaAngles[2] = neighborAngles.ptr[i * 3 + 2];
        grid.createBoundingBox(alphaAngles, triangles[i]);
    }
}


void GridKernelCPU::floodFill(Vertex vec)
{

    printf("start flood...\n");
    std::stack<Vertex> floodFillStack;
    floodFillStack.push(vec);

    int i = 0;
    while (!floodFillStack.empty() && i <= 1000){

        vec = floodFillStack.top();
        floodFillStack.pop();

        unsigned int x = (unsigned int)floor(vec.x);
        unsigned int y = (unsigned int)floor(vec.y);
        unsigned int z = (unsigned int)floor(vec.z);

        int index = this->grid.transCoordToIndex(Vertex(x, y, z));
        if (this->grid.field[index] == FLUID){
            this->grid.field[index] = SOLID;

            floodFillStack.push(Vertex(x, y, z + 1));
            floodFillStack.push(Vertex(x, y, z - 1));
            floodFillStack.push(Vertex(x, y + 1, z));
            floodFillStack.push(Vertex(x, y - 1, z));
            floodFillStack.push(Vertex(x + 1, y, z));
            floodFillStack.push(Vertex(x - 1, y, z));
        }
        //i++;
    }
    printf("...end flood\n");
}


void GridKernelCPU::buildTrianglesAroundTheChannel() {
    Vertex node = Vertex(0.5f, 0.5f, 0.5f);
    Vertex nodeX = Vertex(grid.nx - 1.5f, 0.5f, 0.5f);
    Vertex nodeY = Vertex(0.5f, grid.ny - 1.5f, 0.5f);
    Vertex nodeXY = Vertex(grid.nx - 1.5f, grid.ny - 1.5f, 0.5f);

    Vertex nodeZ = Vertex(0.5f, 0.5f, grid.nz - 1.5f);
    Vertex nodeZX = Vertex(grid.nx - 1.5f, 0.5f, grid.nz - 1.5f);
    Vertex nodeZY = Vertex(0.5f, grid.ny - 1.5f, grid.nz - 1.5f);
    Vertex nodeZXY = Vertex(grid.nx - 1.5f, grid.ny - 1.5f, grid.nz - 1.5f);

    std::vector<Triangle> rbTriangles;
    rbTriangles.push_back(Triangle(node, nodeZ, nodeY)); //inlet
    rbTriangles.push_back(Triangle(nodeY, nodeZ, nodeZY)); //inlet

    rbTriangles.push_back(Triangle(nodeZX, nodeX, nodeXY)); //outlet 
    rbTriangles.push_back(Triangle(nodeXY, nodeZXY, nodeZX)); //outlet

    rbTriangles.push_back(Triangle(node, nodeX, nodeZX)); //front
    rbTriangles.push_back(Triangle(nodeZ, node, nodeZX)); //front

    rbTriangles.push_back(Triangle(nodeY, nodeZY, nodeXY)); //back
    rbTriangles.push_back(Triangle(nodeZY, nodeZXY, nodeXY)); //back

    rbTriangles.push_back(Triangle(nodeZ, nodeZX, nodeZXY)); //top
    rbTriangles.push_back(Triangle(nodeZY, nodeZ, nodeZXY)); //top

    rbTriangles.push_back(Triangle(nodeXY, nodeX, node)); //bottom 
    rbTriangles.push_back(Triangle(node, nodeY, nodeXY)); //bottom

    UnstructuredGridWrapper writer;
    writer.addTriangles(rbTriangles);
    writer.writeUnstructuredGridToFile("rbTriangles");

    struct DoubfloPtr1D neighborAnglesRB;
    neighborAnglesRB.size = rbTriangles.size() * DIMENSION;
    neighborAnglesRB.ptr = new doubflo[neighborAnglesRB.size];
    TriangleNeighborFinder* finderRRB = new TriangleNeighborFinder(&rbTriangles[0], rbTriangles.size());
    finderRRB->fillWithNeighborAngles(&neighborAnglesRB, &rbTriangles[0]);
    delete finderRRB;
}

