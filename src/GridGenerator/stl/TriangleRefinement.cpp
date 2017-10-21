#include "TriangleRefinement.h"

#include "Triangle.h"

TriangleRefinement::TriangleRefinement(std::vector<struct Triangle> *triangles)
{
    this->triangles = triangles;
}

TriangleRefinement::~TriangleRefinement()
{

}

void TriangleRefinement::redoubleTriangles()
{
    int counter = 0;
    for (size_t i = 0; i < triangles->size(); i++)
    {
        refine((int)i);
        counter++;
        if (counter % 50 == 0)
            printf("triangle refine: %d\n", (counter / 2.0));
    }
}

void TriangleRefinement::refineUntilMinDistance(double d_min)
{
    double d = 10e9;
	int counter = 0;

	while (d > d_min) {
        int triangleToRefine = findIndexFromTriangleWithLongestEdge(&d);
        refine(triangleToRefine);

        counter++;
		if (counter % 50 == 0)
            printf("triangle refine: %d, actual dMAX = %2.6f, d_min = %2.6f\n", counter, d, d_min);

    }
}

void TriangleRefinement::refineUntilcountTriangle(int countTri)
{
    double d = 10e9;
    int counter = 0;

    while (counter < countTri) {
        int triangleToRefine = findIndexFromTriangleWithLongestEdge(&d);
        refine(triangleToRefine);

        counter++;
        if (counter % 100 == 0)
            printf("triangle refine: %d, countTri = %d\n", counter, countTri);
    }
}

int TriangleRefinement::findIndexFromTriangleWithLongestEdge(double *d)
{
    *d = 0;
    double dTemp;
    int triangleToRefine = 0;
    for (size_t i = 0; i < triangles->size(); i++)
    {
        dTemp = getLongestEdgeDistance((*triangles)[i]);
        if (*d < dTemp) {
            *d = dTemp;
            triangleToRefine = (int)i;
        }
    }
    return triangleToRefine;
}


void TriangleRefinement::refine(int iTriangle)
{
    sortNeighborIndices();

    struct Triangle t = (*triangles)[iTriangle];
    int edge = getEdgeWithLongestDistance(t);

    std::vector<struct Vertex> v = getVertexArray(iTriangle);
    struct Vertex newVertex = getNewhalfVertexFromTrianglesEdge(v, edge);

    createTwoTriangles(v, edge, newVertex);

    int indexNeighbor = this->indices.ptr[iTriangle * indices.DIM + edge];
    v = getVertexArray(indexNeighbor);
    int commonEdgeNeigbor = findCommonEdgeFromTriangles(indexNeighbor, iTriangle);
    createTwoTriangles(v, commonEdgeNeigbor, newVertex);

    eraseOldTrianglesFromVector(iTriangle, indexNeighbor);
}

void TriangleRefinement::sortNeighborIndices()
{
    indices.DIM = 3;
    indices.size = (int)triangles->size();
    indices.ptr = new int[indices.DIM * indices.size];
    TriangleNeighborFinder neighbors((*triangles).data(), indices.size);
    neighbors.fillWithNeighborIndices(&indices, (*triangles).data());
}

std::vector<struct Vertex> TriangleRefinement::getVertexArray(int iTriangle)
{
    struct Triangle t = (*triangles)[iTriangle];

    std::vector<struct Vertex> v;
    v.resize(4);
    v[0] = t.v1;
    v[1] = t.v2;
    v[2] = t.v3;
    v[3] = t.normal;
    return v;
}

struct Vertex TriangleRefinement::getNewhalfVertexFromTrianglesEdge(std::vector<struct Vertex>  v, int edge)
{
    return getHalfVertex(v[edge], v[edge == 2 ? 0 : edge + 1]);
}

void TriangleRefinement::createTwoTriangles(std::vector<struct Vertex> v, int edge, struct Vertex newEdge)
{
    struct Vertex againstNewEdge = v[edge - 1 < 0 ? 2 : edge - 1];
    struct Vertex firstOldVertex = v[edge];
    struct Vertex secondOldVertex = v[edge + 1 > 2 ? 0 : edge + 1];

    struct Triangle firstNewTriangle(newEdge, againstNewEdge, firstOldVertex, v[3]);
    struct Triangle secondNewTriangle(newEdge, secondOldVertex, againstNewEdge, v[3]);

    (*triangles).push_back(firstNewTriangle);
    (*triangles).push_back(secondNewTriangle);
}

int TriangleRefinement::findCommonEdgeFromTriangles(int indexNeighbor, int iTriangle)
{
    int commonEdgeNeigbor = -1;
    for (int i = 0; i < indices.DIM; i++) {
        if (indices.ptr[indexNeighbor * indices.DIM + i] == iTriangle)
            commonEdgeNeigbor = i;
    }
    return commonEdgeNeigbor;
}

void TriangleRefinement::eraseOldTrianglesFromVector(int iTriangle, int indexNeighbor)
{
    (*triangles).erase((*triangles).begin() + iTriangle);
    if (iTriangle < indexNeighbor)
        indexNeighbor--;
    (*triangles).erase((*triangles).begin() + indexNeighbor);
}


// static method for test bounding box:

void TriangleRefinement::refine(struct Triangle t, struct Triangle &firstNewTriangle, struct Triangle &secondNewTriangle) {

    int edge = getEdgeWithLongestDistance(t);

    std::vector<struct Vertex> v;
    v.resize(4);
    v[0] = t.v1;
    v[1] = t.v2;
    v[2] = t.v3;
    v[3] = t.normal;
    struct Vertex newEdge = getHalfVertex(v[edge], v[edge == 2 ? 0 : edge + 1]);

    struct Vertex againstNewEdge = v[edge - 1 < 0 ? 2 : edge - 1];
    struct Vertex firstOldVertex = v[edge];
    struct Vertex secondOldVertex = v[edge + 1 > 2 ? 0 : edge + 1];

    firstNewTriangle = Triangle(newEdge, againstNewEdge, firstOldVertex, v[3]);
    secondNewTriangle = Triangle(newEdge, secondOldVertex, againstNewEdge, v[3]);
}


int TriangleRefinement::getEdgeWithLongestDistance(Triangle &t) {

    doubflo d1 = t.v2.getEuclideanDistanceTo(t.v1);
    doubflo d2 = t.v3.getEuclideanDistanceTo(t.v2);
    doubflo d3 = t.v1.getEuclideanDistanceTo(t.v3);

    doubflo max = d1;
    int edge = 0;

    if (d2 > d1) {
        edge = 1;
        max = d2;
    }

    if (d3 > max){
        edge = 2;
        max = d3;
    }

    return edge;
}

doubflo TriangleRefinement::getLongestEdgeDistance(struct Triangle &t) {

    int edge = getEdgeWithLongestDistance(t);
    struct Vertex v[3];
    v[0] = t.v1;
    v[1] = t.v2;
    v[2] = t.v3;

    if (edge == 2)
        return v[0].getEuclideanDistanceTo(v[2]);

    return v[edge + 1].getEuclideanDistanceTo(v[edge]);
}

Vertex TriangleRefinement::getHalfVertex(const Vertex &v, const Vertex &w){
    Vertex r;
    r.x = (v.x + w.x) / 2.0f;
    r.y = (v.y + w.y) / 2.0f;
    r.z = (v.z + w.z) / 2.0f;
    return r;
}
