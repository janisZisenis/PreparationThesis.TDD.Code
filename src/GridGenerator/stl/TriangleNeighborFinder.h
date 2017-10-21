#ifndef TriangleNeighborFinder_h
#define TriangleNeighborFinder_h

#include <vector>
#include "global.h"
#include "Core_Export.h"



struct Triangle;
struct Vertex;
struct DoubfloPtr1D;

struct IntegerPtr2D {
    int *ptr;
    int size;
    int DIM;
};

class TriangleNeighborFinder
{
public:
    Core_EXPORT TriangleNeighborFinder(struct Triangle *triangles_ptr, int size);
    Core_EXPORT ~TriangleNeighborFinder();
    
    void Core_EXPORT fillWithNeighborIndices(struct IntegerPtr2D *indices, struct Triangle *triangles);
    void Core_EXPORT fillWithNeighborAngles(struct DoubfloPtr1D *neighborAngles, struct Triangle *triangles);

private:
   

    void initalSortedInSpaceWithCoords(struct Triangle *triangles_ptr, int size);
    void fillSortedInSpaceWithFirstVertexAndCoordinateIDs(int numberOfRows);
    void fillVectorWithIndicesOfTriangleNeighbors();
    unsigned int findTriangleID(unsigned int uniqueCoordID);
    struct Vertex getCoordinatesIDfromTriangle(int triangleID);
    bool isNeighborNotAlreadyInside(unsigned int iTriangle, unsigned int jTriangle);
    std::vector<std::vector<unsigned int> > indicesOfTriangleNeighbors;

    bool isTriangleNeighborOfParentTriangle(struct Vertex, struct Vertex);

    int numberOfRows;
    doubflo **sortedToTriangles;
    doubflo **sortedInSpace;
};

#endif
