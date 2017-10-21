#include "Partition.h"

#include <metis.h>
#include <stdio.h>
#include <iostream>

#include <common/global.h>
#include <grid/kernel/Grid.h>
#include <stl/Triangle.h>
#include <stl/BoundingBox.h>
#include <utilities/io/GridVTKWriter.h>
#include <utilities/io/VTKWriterWrapper/UnstructuredGridWrapper.h>
#include <utilities/Transformator.h>
#include <utilities/Logger.h>

int Partition::calcEdgesFromGraph(const struct Grid &grid) {
    int insideNeighbors = 6;
    int cornerNeighbors = 3;
    int outsideEdgesNeighbors = 4;
    int ousiteAreaNeighbors = 5;

    int corner = 8;
    int outsiteEdges = grid.nx * 4 + grid.ny * 4 + grid.nz * 4 - 24;
    int outsideArea = 2 * grid.nx*grid.ny + 2 * grid.nx*grid.nz + 2 * grid.ny*grid.nz - 8 * grid.nx - 8 * grid.ny - 8 * grid.nz + 24;
    int inside = grid.size - corner - outsiteEdges - outsideArea;
    return inside * insideNeighbors + outsideArea * ousiteAreaNeighbors + outsiteEdges * outsideEdgesNeighbors + corner * cornerNeighbors;
}

void Partition::partitionGridMesh(const struct Grid &grid) {

    printf("MESH\n");

    idx_t nelements = (grid.nx - 1) * (grid.ny - 1) * (grid.nz - 1);
    idx_t nNodes = nelements * 8;
    idx_t nWeightsMesh = 1;
    idx_t nPartsMesh = 2;

    idx_t *partMeshNodes = new idx_t[nNodes];
    idx_t *partMeshElements = new idx_t[nelements];
    idx_t objval;

    // Indexes of starting points in adjacent array
    idx_t *eptr = new idx_t[nelements + 1];

    for (int i = 0; i < nelements + 1; i++) {
        eptr[i] = i * 8;
    }

    // Adjacent vertices in consecutive index order
    idx_t *eind = new idx_t[nNodes];

    int x, y, z, newX, newY, newZ;
    int nIndex;
    int numberNode = 0;
    for (unsigned int index = 0; index < grid.size; index++) {
        grid.transIndexToCoords(index, x, y, z);

        newX = x + 1;
        newY = y + 1;
        newZ = z + 1;
        if (newX >= grid.nx || newY >= grid.ny || newZ >= grid.nz)
            continue;

        // self
        eind[numberNode] = index;
        numberNode++;

        //+x
        nIndex = grid.transCoordToIndex2(newX, y, z);
        eind[numberNode] = nIndex;
        numberNode++;

        //x//+y
        nIndex = grid.transCoordToIndex2(newX, newY, z);
        eind[numberNode] = nIndex;
        numberNode++;

        //+y
        nIndex = grid.transCoordToIndex2(x, newY, z);
        eind[numberNode] = nIndex;
        numberNode++;

        //+z
        nIndex = grid.transCoordToIndex2(x, y, newZ);
        eind[numberNode] = nIndex;
        numberNode++;

        //+z//+x
        nIndex = grid.transCoordToIndex2(newX, y, newZ);
        eind[numberNode] = nIndex;
        numberNode++;

        //+z//+x//+y
        nIndex = grid.transCoordToIndex2(newX, newY, newZ);
        eind[numberNode] = nIndex;
        numberNode++;

        //+z//+y
        nIndex = grid.transCoordToIndex2(x, newY, newZ);
        eind[numberNode] = nIndex;
        numberNode++;

    }


    //for (int i = 0; i < nelements; i++) {
    //    printf("element %d: ", i);
    //    for (int v = eptr[i]; v < eptr[i + 1]; v++) {
    //        printf("%d ", eind[v]);
    //    }
    //    printf("\n");
    //}

    // Weights of vertices
    // if all weights are equal then can be set to NULL
    //idx_t vwgtMesh[nNodes * nWeightsMesh] = { 1, 1, 1, 1, 1, 1, 1, 1, 1 };

    idx_t ncommon = 4;

    rstatus_et ret = (rstatus_et)METIS_PartMeshDual(&nelements, &nNodes, eptr, eind,
        NULL, NULL, &ncommon, &nPartsMesh,
        NULL, NULL, &objval, partMeshElements, partMeshNodes);

    std::cout << ret << std::endl;

    for (int part_i = 0; part_i < nelements; part_i++){
        std::cout << part_i << " " << partMeshElements[part_i] << std::endl;
    }


    for (unsigned int part_i = 0; part_i < grid.size; part_i++){
        grid.field[part_i] = partMeshNodes[part_i];
    }

    GridVTKWriter::writeGridToVTK(grid, "../../../../metisGridMesh.vtk", Transformator(), true);

    delete[] partMeshNodes;
    delete[] partMeshElements;
    delete[] eptr;
    delete[] eind;
}

void Partition::partitionGrid(const struct Grid &grid) {
    idx_t nVertices = grid.size;
    idx_t nEdges = calcEdgesFromGraph(grid);
    idx_t nWeights = 1;
    idx_t nParts = 4;

    idx_t objval;
    idx_t* part = new idx_t[nVertices];
    idx_t* xadj = new idx_t[nVertices + 1];
    idx_t* adjncy = new idx_t[nEdges];

    xadj[0] = 0;
    int x, y, z, newX, newY, newZ;
    int nIndex;
    int numberOfNeighbors = 0;
    int counter = 0;
    for (int index = 0; index < nVertices; index++) {
        grid.transIndexToCoords(index, x, y, z);
        //+x 
        newX = x + 1;
        if (newX >= 0 && newX < grid.nx) {
            nIndex = grid.transCoordToIndex2(newX, y, z);
            adjncy[numberOfNeighbors] = nIndex;
            numberOfNeighbors++;
        }
        //-x
        newX = x - 1;
        if (newX >= 0 && newX < grid.nx) {
            nIndex = grid.transCoordToIndex2(newX, y, z);
            adjncy[numberOfNeighbors] = nIndex;
            numberOfNeighbors++;
        }

        //+y
        newY = y + 1;
        if (newY >= 0 && newY < grid.ny) {
            nIndex = grid.transCoordToIndex2(x, newY, z);
            adjncy[numberOfNeighbors] = nIndex;
            numberOfNeighbors++;
        }

        //-y
        newY = y - 1;
        if (newY >= 0 && newY < grid.ny) {
            nIndex = grid.transCoordToIndex2(x, newY, z);
            adjncy[numberOfNeighbors] = nIndex;
            numberOfNeighbors++;
        }

        //+z
        newZ = z + 1;
        if (newZ >= 0 && newZ < grid.nz) {
            nIndex = grid.transCoordToIndex2(x, y, newZ);
            adjncy[numberOfNeighbors] = nIndex;
            numberOfNeighbors++;
        }

        //-z
        newZ = z - 1;
        if (newZ >= 0 && newZ < grid.nz) {
            nIndex = grid.transCoordToIndex2(x, y, newZ);
            adjncy[numberOfNeighbors] = nIndex;
            numberOfNeighbors++;
        }
        xadj[index + 1] = numberOfNeighbors;
    }


    // Indexes of starting points in adjacent array
    //idx_t xadj[nVertices + 1] = { 0, 2, 5, 7, 9, 12, 14 };

    // Adjacent vertices in consecutive index order
    //idx_t adjncy[2 * nEdges] = { 1, 3, 0, 4, 2, 1, 5, 0, 4, 3, 1, 5, 4, 2 };


    //for (int index = 0; index < nVertices; index++) {
    //    printf("vertexNachbarn von %d: ", index);
    //    printf("Grenzen: %d - %d, ", xadj[index], xadj[index + 1]);
    //    for (int v = xadj[index]; v < xadj[index + 1]; v++) {
    //        printf("%d ", adjncy[v]);
    //    }
    //    printf("\n");
    //}

    // Weights of vertices
    // if all weights are equal then can be set to NULL
    //idx_t* vwgt = new idx_t[nVertices * nWeights];

    idx_t options[METIS_NOPTIONS];
    METIS_SetDefaultOptions(options);

    options[METIS_OPTION_OBJTYPE] = METIS_OBJTYPE_CUT; //minimizing the edge-cut communication

    options[METIS_OPTION_NCUTS] = 1; // number of different partitioning //default 1
    options[METIS_OPTION_CONTIG] = 1; // force contiguous partitions
    options[METIS_OPTION_DBGLVL] = 0; //print debugging information

    rstatus_et ret = (rstatus_et)METIS_PartGraphKway(&nVertices, &nWeights, xadj, adjncy,
        NULL, NULL, NULL, &nParts, NULL,
        NULL, options, &objval, part);

    std::cout << ret << std::endl;

    //for (unsigned part_i = 0; part_i < nVertices; part_i++){
    //    std::cout << part_i << " " << part[part_i] << std::endl;
    //}

    for (int part_i = 0; part_i < nVertices; part_i++){
        grid.field[part_i] = part[part_i];
    }

    GridVTKWriter::writeGridToVTK(grid, "../../../../metisGridFineFourParts.vtk", Transformator(), true);
}

std::vector<std::vector<int> > Partition::partitionBoxes(std::vector<std::vector<struct BoundingBox> > boxes, int processes, std::vector<Transformator> transformators)
{
    if (processes == 1){
        std::vector<std::vector<int> > tasks;
        tasks.resize(processes);
        tasks[0].push_back(0);
        tasks[0].push_back(0);
        return tasks;
    }

    std::vector<idx_t> xadj;
    std::vector<idx_t> adjncy;

    int numberOfNeighbors = 0;
    xadj.push_back(0);
    for (int level = 0; level < boxes.size(); level++) {
        for (int i = 0; i < boxes[level].size(); i++) {
        	
            BoundingBox box = boxes[level][i];
            transformators[level].transformViewToWorld(box);

            int index = i + boxes[level].size() * level;
            for (int levelCompare = 0; levelCompare < boxes.size(); levelCompare++) {
                for (int iCompare = 0; iCompare < boxes[levelCompare].size(); iCompare++) {
                    int indexCompare = iCompare + boxes[levelCompare].size() * levelCompare;
                    if (index == indexCompare)
                        continue;

                    BoundingBox boxCompare = boxes[levelCompare][iCompare];
                    transformators[level].transformViewToWorld(boxCompare);
                    if (box.intersect(boxCompare)) {
                        adjncy.push_back(indexCompare);
                        numberOfNeighbors++;
                    }
                }
            }
            xadj.push_back(numberOfNeighbors);
        }
    }

    //Logger::getInstance()->logTerminal("Metis Graph Structure:");
    //for (int index = 0; index < xadj.size() - 1; index++) {
    //    Logger::getInstance()->logTerminal("vertex neighbor [" + SSTR(index) + "]");
    //    Logger::getInstance()->logTerminal(" boundary: " + SSTR(xadj[index]) + " - " + SSTR(xadj[index + 1]) + ",");
    //    for (int v = xadj[index]; v < xadj[index + 1]; v++) {
    //        Logger::getInstance()->logTerminal(SSTR(adjncy[v]) + " ");
    //    }
    //    Logger::getInstance()->logTerminal("\n");
    //}

    // Weights of vertices
    // if all weights are equal then can be set to NULL
    //idx_t* vwgt = new idx_t[nVertices * nWeights];

    idx_t options[METIS_NOPTIONS];
    METIS_SetDefaultOptions(options);

    options[METIS_OPTION_OBJTYPE] = METIS_OBJTYPE_CUT; //minimizing the edge-cut communication

    options[METIS_OPTION_NCUTS] = 1; // number of different partitioning //default 1
    options[METIS_OPTION_CONTIG] = 1; // force contiguous partitions
    options[METIS_OPTION_DBGLVL] = 0; //print debugging information

    idx_t nVertices = xadj.size() - 1;
    idx_t nWeights = 1;
    idx_t nParts = processes;

    idx_t objval;
    idx_t* part = new idx_t[nVertices];

    //rstatus_et ret = (rstatus_et)METIS_PartGraphKway(&nVertices, &nWeights, xadj.data(), adjncy.data(),
    //    NULL, NULL, NULL, &nParts, NULL,
    //    NULL, options, &objval, part);

    rstatus_et ret = (rstatus_et)METIS_PartGraphRecursive(&nVertices, &nWeights, xadj.data(), adjncy.data(),
        NULL, NULL, NULL, &nParts, NULL,
        NULL, options, &objval, part);

    if (ret == METIS_OK)
        Logger::getInstance()->logTerminal("Metis Status: OK\n");
    

    for (unsigned int part_i = 0; part_i < nVertices; part_i++){
        Logger::getInstance()->logTerminal("Block: " + SSTR(part_i) + " - Partition: " + SSTR(part[part_i]) + "\n");
    }

    std::vector<std::vector<int> > tasks;
    tasks.resize(processes);
    
    for (int i = 0; i < nVertices; i++) {
        int x = i % boxes[0].size();
        int level = (i - x) / boxes[0].size();
        tasks[part[i]].push_back(level);
        tasks[part[i]].push_back(x);
    }

    return tasks;
}

std::vector<struct BoundingBox> Partition::getProcessBoxes(const int numberOfProcesses, const int globalNx, const int globalNy, const int globalNz){
    std::vector<struct BoundingBox> boxes;
    BoundingBox b(0, globalNx, 0, globalNy, 0, globalNz);
    boxes.push_back(b);
    if (numberOfProcesses == 1)
        return boxes;

    bool splitX, splitY, splitZ;
    while (boxes.size() < numberOfProcesses){
        findMaxBoxSize(boxes, splitX, splitY, splitZ);
        if (numberOfProcesses % 3 == 0)
            splitAllBoxesInThreePieces(boxes, splitX, splitY, splitZ);
        else 
            splitAllBoxesInTwoPieces(boxes, splitX, splitY, splitZ);
    }
    return boxes;
}

std::vector<std::vector<struct Triangle> > Partition::getTrianglesPerProcess(std::vector<struct BoundingBox> &boxes, struct Triangle *triangles, int nTriangles)
{
    std::vector<struct Triangle> triangleVec;
    triangleVec.resize(nTriangles);
    for (int i = 0; i < nTriangles; i++)
        triangleVec[i] = triangles[i];

    std::vector<std::vector<struct Triangle> > trianglesPerProcess;
    trianglesPerProcess.resize(boxes.size());

    for (int j = 0; j < triangleVec.size(); j++) {
        for (int i = 0; i < boxes.size(); i++) {
            if (boxes[i].isInside(triangleVec[j])) {
                trianglesPerProcess[i].push_back(triangleVec[j]);
                triangleVec.erase(triangleVec.begin() + j);
                j--;
                break;
            }
            else if (boxes[i].intersect(triangleVec[j])) {
                //splitAndPushTriangle(boxes[i], trianglesPerProcess[i], triangleVec, j);
                trianglesPerProcess[i].push_back(triangleVec[j]);
            }
        }
    }
    return trianglesPerProcess;
}

void Partition::printBoxes(std::vector<struct BoundingBox> boxes, std::string name)
{
    UnstructuredGridWrapper writer;
    for (int i = 0; i < boxes.size(); i++) {
        writer.addBoundingBox(boxes[i], 0);
    }
    writer.writeUnstructuredGridToFile(name);
}

void Partition::findMaxBoxSize(std::vector<struct BoundingBox> &boxes, bool &splitX, bool &splitY, bool &splitZ)
{
    int lengthX, lengthY, lengthZ;
    lengthX = boxes[0].maxX - boxes[0].minX;
    lengthY = boxes[0].maxY - boxes[0].minY;
    lengthZ = boxes[0].maxZ - boxes[0].minZ;

    splitX = true, splitY = false, splitZ = false;
    if (lengthX < lengthY){
        splitX = splitZ = false;
        splitY = true;
    }
    else if (lengthY < lengthZ){
        splitX = splitY = false;
        splitZ = true;
    }
}

void Partition::splitAllBoxesInThreePieces(std::vector<struct BoundingBox> &boxes, bool splitX, bool splitY, bool splitZ)
{
    std::vector<struct BoundingBox> boxesTemp;
    for (int i = 0; i < boxes.size(); i++) {
        if (splitX) {
            int newLengthX = (boxes[i].maxX - boxes[i].minX) / 3;
            BoundingBox splitBox1(boxes[i].minX, boxes[i].minX + newLengthX, boxes[i].minY, boxes[i].maxY, boxes[i].minZ, boxes[i].maxZ);
            BoundingBox splitBox2(boxes[i].minX, boxes[i].minX + newLengthX + newLengthX, boxes[i].minY, boxes[i].maxY, boxes[i].minZ, boxes[i].maxZ);
            BoundingBox splitBox3(boxes[i].minX + newLengthX + newLengthX, boxes[i].maxX, boxes[i].minY, boxes[i].maxY, boxes[i].minZ, boxes[i].maxZ);
            boxesTemp.push_back(splitBox1);
            boxesTemp.push_back(splitBox2);
            boxesTemp.push_back(splitBox3);
        }
        if (splitY) {
            int newLengthY = (boxes[i].maxY - boxes[i].minY) / 3;
            BoundingBox splitBox1(boxes[i].minX, boxes[i].maxX, boxes[i].minY, boxes[i].minY + newLengthY, boxes[i].minZ, boxes[i].maxZ);
            BoundingBox splitBox2(boxes[i].minX, boxes[i].maxX, boxes[i].minY + newLengthY, boxes[i].minY + newLengthY + newLengthY, boxes[i].minZ, boxes[i].maxZ);
            BoundingBox splitBox3(boxes[i].minX, boxes[i].maxX, boxes[i].minY + newLengthY + newLengthY, boxes[i].maxY, boxes[i].minZ, boxes[i].maxZ);
            boxesTemp.push_back(splitBox1);
            boxesTemp.push_back(splitBox2);
            boxesTemp.push_back(splitBox3);
        }
        if (splitZ) {
            int newLengthZ = (boxes[i].maxZ - boxes[i].minZ) / 3;
            BoundingBox splitBox1(boxes[i].minX, boxes[i].maxX, boxes[i].minY, boxes[i].maxY, boxes[i].minZ, boxes[i].minZ + newLengthZ);
            BoundingBox splitBox2(boxes[i].minX, boxes[i].maxX, boxes[i].minY, boxes[i].maxY, boxes[i].minZ + newLengthZ, boxes[i].minZ + newLengthZ + newLengthZ);
            BoundingBox splitBox3(boxes[i].minX, boxes[i].maxX, boxes[i].minY, boxes[i].maxY, boxes[i].minZ + newLengthZ + newLengthZ, boxes[i].maxZ);
            boxesTemp.push_back(splitBox1);
            boxesTemp.push_back(splitBox2);
            boxesTemp.push_back(splitBox3);
        }
    }
    boxes.clear();
    boxes = boxesTemp;
}

void Partition::splitAllBoxesInTwoPieces(std::vector<struct BoundingBox> &boxes, bool splitX, bool splitY, bool splitZ)
{
    std::vector<struct BoundingBox> boxesTemp;
    for (int i = 0; i < boxes.size(); i++) {
        if (splitX) {
            int newLengthX = (boxes[i].maxX - boxes[i].minX) / 2;
            BoundingBox splitBox1(boxes[i].minX, boxes[i].minX + newLengthX, boxes[i].minY, boxes[i].maxY, boxes[i].minZ, boxes[i].maxZ);
            BoundingBox splitBox2(boxes[i].minX + newLengthX, boxes[i].maxX, boxes[i].minY, boxes[i].maxY, boxes[i].minZ, boxes[i].maxZ);
            boxesTemp.push_back(splitBox1);
            boxesTemp.push_back(splitBox2);
        }
        if (splitY) {
            int newLengthY = (boxes[i].maxY - boxes[i].minY) / 2;
            BoundingBox splitBox1(boxes[i].minX, boxes[i].maxX, boxes[i].minY, boxes[i].minY + newLengthY, boxes[i].minZ, boxes[i].maxZ);
            BoundingBox splitBox2(boxes[i].minX, boxes[i].maxX, boxes[i].minY + newLengthY, boxes[i].maxY, boxes[i].minZ, boxes[i].maxZ);
            boxesTemp.push_back(splitBox1);
            boxesTemp.push_back(splitBox2);
        }
        if (splitZ) {
            int newLengthZ = (boxes[i].maxZ - boxes[i].minZ) / 2;
            BoundingBox splitBox1(boxes[i].minX, boxes[i].maxX, boxes[i].minY, boxes[i].maxY, boxes[i].minZ, boxes[i].minZ + newLengthZ);
            BoundingBox splitBox2(boxes[i].minX, boxes[i].maxX, boxes[i].minY, boxes[i].maxY, boxes[i].minZ + newLengthZ, boxes[i].maxZ);
            boxesTemp.push_back(splitBox1);
            boxesTemp.push_back(splitBox2);
        }
    }
    boxes.clear();
    boxes = boxesTemp;
}

std::vector<std::vector<struct Triangle> >  Partition::splitTriangles(std::vector<struct Triangle> &triangleVec, std::vector<struct BoundingBox> boxes)
{
    std::vector<std::vector<struct Triangle> > trianglesPerProcess;
    trianglesPerProcess.resize(boxes.size());

    for (int j = 0; j < triangleVec.size(); j++) {
        for (int i = 0; i < boxes.size(); i++) {
            if (boxes[i].isInside(triangleVec[j])) {
                trianglesPerProcess[i].push_back(triangleVec[j]);
                triangleVec.erase(triangleVec.begin() + j);
                j--;
                break;
            }
            else if (boxes[i].intersect(triangleVec[j])) {
                splitAndPushTriangle(boxes[i], trianglesPerProcess[i], triangleVec, j);
                //trianglesPerProcess[i].push_back(triangleVec[j]);
            }
        }
    }

    return trianglesPerProcess;

}



void Partition::splitAndPushTriangle(struct BoundingBox &box, std::vector<struct Triangle> &trianglesPerProcess, std::vector<struct Triangle> &triangleVec, int indexTriangle)
{
    struct Triangle triangleToSplit = triangleVec[indexTriangle];
    struct BoundingBoxExact triangleBox = BoundingBoxExact(triangleToSplit);
    std::vector<std::vector<Vertex> > intersectionsBox = box.getIntersectionPoints(triangleBox);

    //UnstructuredGridWriter writer;
    //double v1[3] = { triangleToSplit.v1.x, triangleToSplit.v1.y, triangleToSplit.v1.z };
    //double v2[3] = { triangleToSplit.v2.x, triangleToSplit.v2.y, triangleToSplit.v2.z };
    //double v3[3] = { triangleToSplit.v3.x, triangleToSplit.v3.y, triangleToSplit.v3.z };
    //writer.addTriangle(v1, v2, v3);
    //double b[6] = { box.minX, box.maxX, box.minY, box.maxY, box.minZ, box.maxZ };
    //writer.addBoundingBox(b);
    //double b2[6] = { triangleBox.minX, triangleBox.maxX, triangleBox.minY, triangleBox.maxY, triangleBox.minZ, triangleBox.maxZ };
    //writer.addBoundingBox(b2);
    //writer.writeUnstructuredGridToFile("testIntersectionTriangle");


    for (int i = 0; i < intersectionsBox.size(); i++) {
        if (intersectionsBox[i].size() == 0)
            continue;

        struct Vertex edge1 = intersectionsBox[i][0] - intersectionsBox[i][1];
        struct Vertex edge2 = intersectionsBox[i][1] - intersectionsBox[i][2];
        struct Vertex normal = edge1.crossProduct(edge2);
        normal.normalize();

        Vertex point(intersectionsBox[i][0].x, intersectionsBox[i][0].y, intersectionsBox[i][0].z);
        Vertex v4 = (triangleToSplit.v1 - point);
        Vertex v5 = (triangleToSplit.v2 - point);
        Vertex v6 = (triangleToSplit.v3 - point);

        doubflo d1 = v4 * normal;
        doubflo d2 = v5 * normal;
        doubflo d3 = v6 * normal;

        // a to b crosses the clipping plane
        if (d1 * d2 < 0.0f)
            sliceTriangle(trianglesPerProcess, triangleVec, indexTriangle, triangleToSplit.v1, triangleToSplit.v2, triangleToSplit.v3, d1, d2, d3);

        // a to c crosses the clipping plane
        else if (d1 * d3 < 0.0f)
            sliceTriangle(trianglesPerProcess, triangleVec, indexTriangle, triangleToSplit.v3, triangleToSplit.v1, triangleToSplit.v2, d3, d1, d2);

        // b to c crosses the clipping plane
        else if (d2 * d3 < 0.0f)
            sliceTriangle(trianglesPerProcess, triangleVec, indexTriangle, triangleToSplit.v2, triangleToSplit.v3, triangleToSplit.v1, d2, d3, d1);
    }
}


void Partition::sliceTriangle(
    std::vector<Triangle>& out,
    std::vector<Triangle>& triangleVec,
    int index,
    const Vertex& a, // First point on triangle, CCW order
    const Vertex& b, // Second point on triangle, CCW order
    const Vertex& c, // Third point on triangle, CCW order
    doubflo d1,        // Distance of point a to the splitting plane
    doubflo d2,        // Distance of point b to the splitting plane
    doubflo d3         // Distance of point c to the splitting plane
    )
{
    // Calculate the intersection point from a to b
    Vertex ab = a + (d1 / (d1 - d2)) * (b - a);
    Triangle tri;

    if (d1 < 0.0f)
    {
        // b to c crosses the clipping plane
        if (d3 < 0.0f)
        {
            // Calculate intersection point from b to c
            Vertex bc = b + (d2 / (d2 - d3)) * (c - b);

            tri.set(b, bc, ab);
            triangleVec.push_back(tri);

            tri.set(bc, c, a);
            triangleVec.push_back(tri);

            tri.set(ab, bc, a);
            triangleVec.push_back(tri);
        }

        // c to a crosses the clipping plane
        else
        {
            // Calculate intersection point from a to c
            Vertex ac = a + (d1 / (d1 - d3)) * (c - a);

            tri.set(a, ab, ac);
            triangleVec.push_back(tri);

            tri.set(ab, b, c);
            triangleVec.push_back(tri);

            tri.set(ac, ab, c);
            triangleVec.push_back(tri);
        }
    }
    else
    {
        // c to a crosses the clipping plane
        if (d3 < 0.0f)
        {
            // Calculate intersection point from a to c
            Vertex ac = a + (d1 / (d1 - d3)) * (c - a);

            tri.set(a, ab, ac);
            triangleVec.push_back(tri);

            tri.set(ac, ab, b);
            triangleVec.push_back(tri);

            tri.set(b, c, ac);
            triangleVec.push_back(tri);
        }

        // b to c crosses the clipping plane
        else
        {
            // Calculate intersection point from b to c
            Vertex bc = b + (d2 / (d2 - d3)) * (c - b);

            tri.set(b, bc, ab);
            triangleVec.push_back(tri);

            tri.set(a, ab, bc);
            triangleVec.push_back(tri);

            tri.set(c, a, bc);
            triangleVec.push_back(tri);
        }
    }
}
