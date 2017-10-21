#ifndef GridBuilder_H
#define GridBuilder_H

#include "global.h"
#include "mpi.h"
#include <vector>
#include <string>
#include <utilities/Logger.h>
#ifdef __unix__
#include <tr1/memory>
#include <unistd.h>
#else
#include <memory>
#endif
#include "Core_EXPORT.h"

#include "GridGenerator/grid/kernel/GridKernel.h"
#include "Partition.h"
#include <utilities/io/VTKWriterWrapper/UnstructuredGridWrapper.h>

class Transformator;
struct BoundingBox;

class Core_EXPORT GridBuilder
{
public:
    GridBuilder();
    ~GridBuilder();

    template <typename KernelType>
    void addGrid(doubflo length, doubflo width, doubflo high, doubflo delta, std::string distribution, Transformator &trans, bool isCoarsestGrid)
    {
        int numProcess, rank;
        MPI_Comm_size(MPI_COMM_WORLD, &numProcess);
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        
      

        int addNode = 0;
        if (isCoarsestGrid) addNode = 1;
        int nx = (int)(length / delta) + addNode;
        int ny = (int)(width / delta) + addNode;
        int nz = (int)(high / delta) + addNode;

		Logger::getInstance()->logTerminal("global field dimension: " + SSTR(nx) + ", " + SSTR(ny) + ", " + SSTR(nz) + "\n", MASTER);
		Logger::getInstance()->logTerminal("global field size : " + SSTR(nx * ny * nz) + "\n", MASTER);
		Logger::getInstance()->logTerminal("-------------------------------------------\n", MASTER);
		Logger::getInstance()->logTerminal("Number of processes: " + SSTR( numProcess) + "\n", MASTER);
		Logger::getInstance()->logTerminal("-------------------------------------------\n", MASTER);

        std::vector<int> dim;
        dim.push_back(nx);
        dim.push_back(ny);
        dim.push_back(nz);
        this->gridDimensions.push_back(dim);
        this->transformators.push_back(trans);

        int actualLevelSize = this->boxes.size() + 1;
        this->boxes.resize(actualLevelSize);
        this->gridKernels.resize(actualLevelSize);
   
        
        //for each level rebuild boxes 
        for (int i = 0; i < actualLevelSize; i++) {
            this->boxes[i] = Partition::getProcessBoxes(numProcess / actualLevelSize, gridDimensions[i][0], gridDimensions[i][1], gridDimensions[i][2]);
            this->gridKernels[i].resize(this->boxes[i].size());
        }
        if (rank == 0) {
            std::vector<std::vector<int> >tasks = Partition::partitionBoxes(this->boxes, numProcess, transformators);

            rankTasks.resize(tasks[0].size());
            for (int i = 0; i < rankTasks.size(); i++) {
                rankTasks[i] = tasks[0][i];
            }

            for (int i = 1; i < numProcess; i++) {
                int numOfBoxes = tasks[i].size();
                MPI_Send(&numOfBoxes, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
                MPI_Send(&tasks[i][0], numOfBoxes, MPI_INT, i, 1, MPI_COMM_WORLD);
            }
        }
        else {
            int numOfBoxes;
            MPI_Status status;
            MPI_Recv(&numOfBoxes, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
            rankTasks.resize(numOfBoxes);

            int *boxNumbers = new int[numOfBoxes];
            MPI_Recv(boxNumbers, numOfBoxes, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);

            for (int i = 0; i < numOfBoxes; i++) {
                rankTasks[i] = boxNumbers[i];
            }
            delete[] boxNumbers;
        }
        
        //for (rank = 0; rank < numProcess; rank++) { // statt MPI
        	       
        for (int i = 0; i < rankTasks.size(); i+=2) {
            int level = rankTasks[i];
            int index = rankTasks[i + 1];
            this->gridKernels[level][index] = std::shared_ptr<GridKernel>(new KernelType(this->boxes[level][index], trans, distribution, isCoarsestGrid));
        }
        
        //} // statt MPI


        //if (!isCoarsestGrid) {
        //    UnstructuredGridWrapper writer;
        //    for (int rank = 0; rank < tasks.size(); rank++) {
        //        for (int j = 0; j < tasks[rank].size(); j++) {
        //            int level = std::get<0>(tasks[rank][j]);
        //            int index = std::get<1>(tasks[rank][j]);
        //            BoundingBox box = boxes[level][index];
        //            transformators[level].transformViewToWorld(box);
        //            writer.addBoundingBox(box, rank);
        //        }
        //    }
        //    writer.writeUnstructuredGridToFile("fineCoarseMu");
        //}
    }

    void meshGeometry(std::string input, int level);
    void flood(struct Vertex startFlood, int level);

    void writeGridToVTK(std::string output, int level);
    void writeArrows(std::string output, int level);
    void writeSimulationFiles(std::string output, struct BoundingBox &nodesDelete, bool writeFilesBinary, int level);
    void writeCells(std::string input, std::string name, bool writeFilesBinary);

    std::shared_ptr<GridKernel> getKernel(int level, int box);

private:
    std::vector<std::vector<std::shared_ptr<GridKernel> > >gridKernels;
    std::vector<Transformator> transformators;
    std::vector<std::vector<struct BoundingBox> > boxes;

    std::vector<int> rankTasks;

    std::vector<std::vector<int> > gridDimensions;

    void checkLevel(int level);
};

#endif
