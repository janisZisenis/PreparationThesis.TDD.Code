#include <vector>

#include "Exception.h"
#include "gmock/gmock.h"
#include "Triangle.h"
#include "TriangleNeighborFinder.h"
#include <utilities/io/STLReaderWriter.h>
#include <utilities/io/GridVTKWriter.h>
#include <utilities/Transformator.h>

using namespace testing;


class TriangleNeighborFinderTest : public Test {
public:
    TriangleNeighborFinder *finder;
    std::vector<struct Triangle> triangles;
    struct IntegerPtr2D indices;
    std::string absolutePath;

    void SetUp() {
        absolutePath = PATH_TO_DATA;
        triangles = STLReaderWriter::readSTL(absolutePath +  "TESTSUITE/STL/TriangleNeighborFinderTest/quadarASCII1x1.stl", Transformator());
        finder = new TriangleNeighborFinder(&triangles[0], (int)triangles.size());
        indices.size = (int) triangles.size();
        indices.DIM = DIMENSION;
        indices.ptr = new int[indices.DIM * triangles.size()];
    }

    void TearDown() {
        delete[] indices.ptr;
        delete finder;
    }
};

TEST_F(TriangleNeighborFinderTest, getNeighboursFromTriangle) {
    unsigned int triangleID = 0;
    finder->fillWithNeighborIndices(&indices, &triangles[0]);

    EXPECT_THAT(indices.ptr[triangleID * indices.DIM + 0], Eq(3));
    EXPECT_THAT(indices.ptr[triangleID * indices.DIM + 1], Eq(1));
    EXPECT_THAT(indices.ptr[triangleID * indices.DIM + 2], Eq(9));
}

