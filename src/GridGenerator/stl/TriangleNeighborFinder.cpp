#include "TriangleNeighborFinder.h"

#include "Triangle.h"
#include <grid/kernel/Grid.h>

struct IDS {
    enum IDs{ vertexID = 0, firstVertexID = 1, coordinateID = 2, uniqueCoordID = 3, x = 3, y = 4, z = 5 };
};


int compare2DArrayAccordingToXYZ(const void *pa, const void *pb) {

    doubflo *a = *((doubflo **)pa);
    doubflo *b = *((doubflo **)pb);

    //compare X
    if (a[IDS::x] < b[IDS::x]) return -1;
    else if (a[IDS::x] > b[IDS::x]) return +1;
    //compare Y
    else if (a[IDS::y] < b[IDS::y]) return -1;
    else if (a[IDS::y] > b[IDS::y]) return +1;
    //compare Z
    else if (a[IDS::z] < b[IDS::z]) return -1;
    else if (a[IDS::z] > b[IDS::z]) return +1;
    //compare Index
    else if (a[IDS::vertexID] < b[IDS::vertexID]) return -1;
    else if (a[IDS::vertexID] > b[IDS::vertexID]) return +1;

    return 0;
}

int compare2DArrayAccordingToIndex(const void *pa, const void *pb) {

    doubflo *a = *((doubflo **)pa);
    doubflo *b = *((doubflo **)pb);

    if (a[IDS::vertexID] < b[IDS::vertexID]) return -1;
    else if (a[IDS::vertexID] > b[IDS::vertexID]) return +1;
    return 0;
}

TriangleNeighborFinder::TriangleNeighborFinder(struct Triangle *triangles_ptr, int size)
{
    numberOfRows = size*DIMENSION;

    this->initalSortedInSpaceWithCoords(triangles_ptr, size);

    qsort(sortedInSpace, numberOfRows, sizeof sortedInSpace[0], compare2DArrayAccordingToXYZ);

    this->fillSortedInSpaceWithFirstVertexAndCoordinateIDs(numberOfRows);

    //copy the array:
    sortedToTriangles = new doubflo*[numberOfRows];
    for (int i = 0; i < numberOfRows; i++) {
        sortedToTriangles[i] = new doubflo[4];
        sortedToTriangles[i][IDS::vertexID] = sortedInSpace[i][IDS::vertexID];
        sortedToTriangles[i][IDS::firstVertexID] = sortedInSpace[i][IDS::firstVertexID];
        sortedToTriangles[i][IDS::coordinateID] = sortedInSpace[i][IDS::coordinateID];
        sortedToTriangles[i][IDS::uniqueCoordID] = (doubflo)i;
    }

    qsort(sortedToTriangles, numberOfRows, sizeof sortedToTriangles[0], compare2DArrayAccordingToIndex);

    indicesOfTriangleNeighbors.resize(size);

    this->fillVectorWithIndicesOfTriangleNeighbors();
}


void TriangleNeighborFinder::initalSortedInSpaceWithCoords(struct Triangle *triangles_ptr, int size)
{
    sortedInSpace = new doubflo*[numberOfRows];

    int vertexCounter = 0;
    int numberOfColumns = 6;
    for (int i = 0; i < size; i++){
        sortedInSpace[vertexCounter] = new doubflo[numberOfColumns];
        sortedInSpace[vertexCounter][IDS::vertexID] = (doubflo)vertexCounter;
        sortedInSpace[vertexCounter][IDS::firstVertexID] = 0.0f;                  
        sortedInSpace[vertexCounter][IDS::coordinateID]  = 0.0f;                   
        sortedInSpace[vertexCounter][IDS::x] = triangles_ptr[i].v1.x;
        sortedInSpace[vertexCounter][IDS::y] = triangles_ptr[i].v1.y;
        sortedInSpace[vertexCounter][IDS::z] = triangles_ptr[i].v1.z;

        vertexCounter++;
        sortedInSpace[vertexCounter] = new doubflo[numberOfColumns];
        sortedInSpace[vertexCounter][IDS::vertexID]      = (doubflo)vertexCounter;
        sortedInSpace[vertexCounter][IDS::firstVertexID] = 0.0f;
        sortedInSpace[vertexCounter][IDS::coordinateID]  = 0.0f;
        sortedInSpace[vertexCounter][IDS::x] = triangles_ptr[i].v2.x;
        sortedInSpace[vertexCounter][IDS::y] = triangles_ptr[i].v2.y;
        sortedInSpace[vertexCounter][IDS::z] = triangles_ptr[i].v2.z;

        vertexCounter++;
        sortedInSpace[vertexCounter] = new doubflo[numberOfColumns];
        sortedInSpace[vertexCounter][IDS::vertexID]      = (doubflo)vertexCounter;
        sortedInSpace[vertexCounter][IDS::firstVertexID] = 0.0f;
        sortedInSpace[vertexCounter][IDS::coordinateID]  = 0.0f;
        sortedInSpace[vertexCounter][IDS::x] = triangles_ptr[i].v3.x;
        sortedInSpace[vertexCounter][IDS::y] = triangles_ptr[i].v3.y;
        sortedInSpace[vertexCounter][IDS::z] = triangles_ptr[i].v3.z;
        vertexCounter++;
    }
}

TriangleNeighborFinder::~TriangleNeighborFinder()
{
    for (int i = 0; i < numberOfRows; i++){
        delete[] sortedToTriangles[i];
        delete[] sortedInSpace[i];
    }
    delete[] sortedToTriangles;
    delete[] sortedInSpace;
}

void TriangleNeighborFinder::fillSortedInSpaceWithFirstVertexAndCoordinateIDs(int numberOfRows)
{
    int firstVertexID = 0;
    int compareID = 0;
    int coordinateID = 0;
    int duplicates = 0;
    
    while (firstVertexID < numberOfRows) {
        Vertex a = Vertex(sortedInSpace[firstVertexID][IDS::x], sortedInSpace[firstVertexID][IDS::y], sortedInSpace[firstVertexID][IDS::z]);
        Vertex b = Vertex(sortedInSpace[compareID][IDS::x], sortedInSpace[compareID][IDS::y], sortedInSpace[compareID][IDS::z]);
        while (a.getEuclideanDistanceTo(b) < 1e-7)
        {
            sortedInSpace[compareID][IDS::firstVertexID] = sortedInSpace[firstVertexID][0];
            sortedInSpace[compareID][IDS::coordinateID] = (doubflo)coordinateID;
            duplicates++;
            
            compareID++;
            if (compareID == numberOfRows)
                break;
            b = Vertex(sortedInSpace[compareID][IDS::x], sortedInSpace[compareID][IDS::y], sortedInSpace[compareID][IDS::z]);
        }
        firstVertexID += duplicates;
        duplicates = 0;
        coordinateID++;
    }
}

void TriangleNeighborFinder::fillVectorWithIndicesOfTriangleNeighbors()
{
    for (unsigned int triangleID = 0; triangleID < indicesOfTriangleNeighbors.size(); triangleID++){

        struct Vertex coordinateIDsFromTriangle = getCoordinatesIDfromTriangle(triangleID);

        for (unsigned int vertex = 0; vertex < DIMENSION; vertex++){
            unsigned int vertexID = triangleID * DIMENSION + vertex;
            unsigned int firstVertexID = (int)sortedToTriangles[vertexID][IDS::firstVertexID];
            unsigned int uniqueCoordID = (int)sortedToTriangles[firstVertexID][IDS::uniqueCoordID];

            while (firstVertexID == sortedInSpace[uniqueCoordID][IDS::firstVertexID]){
                unsigned int jTriangle = findTriangleID(uniqueCoordID);

                uniqueCoordID++;
                if (uniqueCoordID >= indicesOfTriangleNeighbors.size()*DIMENSION)
                    break;
                if (jTriangle == triangleID)
                    continue;

                struct Vertex coordinateIDsFromTriangleNeighbor = getCoordinatesIDfromTriangle(jTriangle);

                if (isTriangleNeighborOfParentTriangle(coordinateIDsFromTriangle, coordinateIDsFromTriangleNeighbor)
                    &&  isNeighborNotAlreadyInside(triangleID, jTriangle))
                {
                    indicesOfTriangleNeighbors[triangleID].push_back(jTriangle);
                }
            }

        }
    }
}

unsigned int TriangleNeighborFinder::findTriangleID(unsigned int uniqueCoordID)
{
    return (int)sortedInSpace[uniqueCoordID][IDS::vertexID] / DIMENSION;
}

struct Vertex TriangleNeighborFinder::getCoordinatesIDfromTriangle(int triangleID)
{
    doubflo coordinateID1 = sortedToTriangles[triangleID * DIMENSION + 0][IDS::coordinateID];
    doubflo coordinateID2 = sortedToTriangles[triangleID * DIMENSION + 1][IDS::coordinateID];
    doubflo coordinateID3 = sortedToTriangles[triangleID * DIMENSION + 2][IDS::coordinateID];
    return Vertex(coordinateID1, coordinateID2, coordinateID3);
}


bool TriangleNeighborFinder::isTriangleNeighborOfParentTriangle(struct Vertex v1, struct Vertex v2)
{
    int countSameID = 0;
    if (v1.x == v2.x)
        countSameID++;
    else if (v1.x == v2.y)
        countSameID++;
    else if (v1.x == v2.z)
        countSameID++;

    if (v1.y == v2.x)
        countSameID++;
    else if (v1.y == v2.y)
        countSameID++;
    else if (v1.y == v2.z)
        countSameID++;

    if (v1.z == v2.x)
        countSameID++;
    else if (v1.z == v2.y)
        countSameID++;
    else if (v1.z == v2.z)
        countSameID++;

    if (countSameID == 2 || countSameID == 3)
        return true;

    return false;
}

bool TriangleNeighborFinder::isNeighborNotAlreadyInside(unsigned int iTriangle, unsigned int jTriangle)
{
    for (unsigned int i = 0; i < indicesOfTriangleNeighbors[iTriangle].size(); i++){
        if (indicesOfTriangleNeighbors[iTriangle][i] == jTriangle)
            return false;
    }
    return true;
}

void TriangleNeighborFinder::fillWithNeighborIndices(struct IntegerPtr2D *neighborIndices, struct Triangle *triangles)
{
    for (unsigned int i = 0; i < indicesOfTriangleNeighbors.size(); i++){
        int row = i * neighborIndices->DIM;
        neighborIndices->ptr[row + 0] = neighborIndices->ptr[row + 1] = neighborIndices->ptr[row + 2] = -1;
        for (unsigned int j = 0; j < indicesOfTriangleNeighbors[i].size(); j++){
            int index = triangles[i].getCommonEdge(triangles[indicesOfTriangleNeighbors[i][j]]);
            neighborIndices->ptr[row + index] = indicesOfTriangleNeighbors[i][j];
        }
    }
}


void TriangleNeighborFinder::fillWithNeighborAngles(struct DoubfloPtr1D *neighborAngles, struct Triangle *triangles)
{
    int j, row, index, indexNeighbor;
   // #pragma omp parallel for private(j, row, index, indexNeighbor) shared(neighborAngles->ptr)
    for (int i = 0; i < indicesOfTriangleNeighbors.size(); i++){
        row = i * 3;
        neighborAngles->ptr[row + 0] = neighborAngles->ptr[row + 1] = neighborAngles->ptr[row + 2] = 90.0f;
        for (j = 0; j < indicesOfTriangleNeighbors[i].size(); j++){
            indexNeighbor = indicesOfTriangleNeighbors[i][j];
            index = triangles[i].getCommonEdge(triangles[indexNeighbor]);
            neighborAngles->ptr[row + index] = triangles[i].getHalfAngleBetweenToAdjacentTriangle(triangles[indexNeighbor]);
        }
    }

    //for (size_t i = 0; i < neighborAngles->size; i++)
    //{
    //    int row = i * 3;
    //    printf("triangle : %d\n", i);
    //    for (size_t j = 0; j < 3; j++)
    //    {
    //        printf(" %d ", neighborAngles->ptr[row + j]);
    //    }
    //    printf("\n");
    //}
}
