#ifndef Partition_H
#define Partition_H

#include "global.h"
#include <vector>
#include <string>
#include "Core_Export.h"

struct BoundingBox;
struct Triangle;
class Transformator;

class Core_EXPORT Partition
{
public:
    static void partitionGridMesh(const struct Grid &grid);
    static void partitionGrid(const struct Grid &grid);

    static std::vector<std::vector<int> > partitionBoxes(std::vector<std::vector<struct BoundingBox> >, int processes, std::vector<Transformator> transformators);

    static std::vector<struct BoundingBox> getProcessBoxes(const int numberOfProcesses, const int globalNx, const int globalNy, const int globalNz);
    static std::vector<std::vector<struct Triangle> >getTrianglesPerProcess(std::vector<struct BoundingBox> &boxes, struct Triangle *triangles, int nTriangles);

    static void printBoxes(std::vector<struct BoundingBox>, std::string name);

    static std::vector<std::vector<struct Triangle> >  splitTriangles(std::vector<struct Triangle> &triangleVec, std::vector<struct BoundingBox> boxes);
    
private:
    Partition(){};
    ~Partition(){};

    static int calcEdgesFromGraph(const struct Grid &grid);

    static void splitAllBoxesInThreePieces(std::vector<struct BoundingBox> &boxes, bool splitX, bool splitY, bool splitZ);
    static void splitAllBoxesInTwoPieces(std::vector<struct BoundingBox> &boxes, bool splitX, bool splitY, bool splitZ);
    static void findMaxBoxSize(std::vector<struct BoundingBox> &boxes, bool &splitX, bool &splitY, bool &splitZ);


    static void splitAndPushTriangle(struct BoundingBox &box, std::vector<struct Triangle> &trianglesPerProcess, std::vector<struct Triangle> &triangleVec, int indexTriangle);
    static void sliceTriangle(std::vector<Triangle> &out, std::vector<Triangle>& triangleVec, int index, const struct Vertex& a, const struct Vertex& b, const struct Vertex& c, doubflo d1, doubflo d2, doubflo d3);

};

#endif
