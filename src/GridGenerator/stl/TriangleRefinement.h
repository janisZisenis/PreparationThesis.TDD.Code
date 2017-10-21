#ifndef TriangleRefinement_h
#define TriangleRefinement_h

#include <vector>

#include "TriangleNeighborFinder.h"
#include "Core_Export.h"

struct Triangle;
struct Vertex;
struct IntegerPtr2D;

class  TriangleRefinement
{
public:
    Core_EXPORT TriangleRefinement(std::vector<struct Triangle> *triangles);
    Core_EXPORT ~TriangleRefinement();

    void Core_EXPORT refine(int iTriangle);
    static void Core_EXPORT refine(struct Triangle t, struct Triangle &firstNewTriangle, struct Triangle &secondNewTriangle);
    
    void Core_EXPORT refineUntilMinDistance(double d_min);
    void Core_EXPORT refineUntilcountTriangle(int countTri);
    void Core_EXPORT redoubleTriangles();

    static Core_EXPORT Vertex getHalfVertex(const Vertex &v, const Vertex &w);

private:
    std::vector<struct Triangle> *triangles;
    struct IntegerPtr2D indices;

    int findIndexFromTriangleWithLongestEdge(double *d);
    std::vector<struct Vertex> getVertexArray(int iTriangle);
    struct Vertex getNewhalfVertexFromTrianglesEdge(std::vector<struct Vertex> v, int edge);
    void sortNeighborIndices();
    void createTwoTriangles(std::vector<struct Vertex> v, int edge, struct Vertex newEdge);
    void eraseOldTrianglesFromVector(int iTriangle, int indexNeighbor);
    int findCommonEdgeFromTriangles(int indexNeighbor, int iTriangle);

public:
    static int Core_EXPORT getEdgeWithLongestDistance(struct Triangle &t);
    static doubflo Core_EXPORT getLongestEdgeDistance(struct Triangle &t);
};


#endif
