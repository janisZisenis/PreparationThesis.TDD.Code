#ifndef STLReaderWriter_h
#define STLReaderWriter_h

#include <vector>
#include <string>
#include "Core_Export.h"

class Transformator;
struct Triangle;
struct BoundingBox;

class Core_EXPORT STLReaderWriter
{
public:
    static void writeBinarySTL(std::vector<struct Triangle> vec, std::string name, Transformator trans);
    static void writeTrianglesToSTL(std::vector<struct Triangle>, std::string name, Transformator trans);
    static void writeTrianglesToSTL(struct Triangle *triangles, int &size, std::string name, Transformator trans);
    static std::vector<struct Triangle> readSTL(std::string name, Transformator trans);
    static std::vector<struct Triangle> readSTL(BoundingBox &box, std::string name, Transformator trans);

    static std::vector<struct Triangle> readBinarySTL(std::string name, Transformator trans);
    static std::vector<struct Triangle> readASCIISTL(std::string name, Transformator trans);
    static std::vector<struct Triangle> readBinarySTL(BoundingBox &box, std::string name, Transformator trans);
    static std::vector<struct Triangle> readASCIISTL(BoundingBox &box, std::string name, Transformator trans);

private:
    STLReaderWriter(){};
    ~STLReaderWriter(){};

    static int countLinesInFile(std::string name);
    static struct Vertex parseLineToCoordinates(std::ifstream& file, std::string format);
    static struct Vertex getVertexFromChar(const char* facet);
};

#endif
