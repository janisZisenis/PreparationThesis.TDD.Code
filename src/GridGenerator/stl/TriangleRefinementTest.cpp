#include <vector>

#include "Exception.h"
#include "gmock/gmock.h"
#include "Vertex.h"
#include "Triangle.h"
#include "TriangleRefinement.h"
#include "TriangleNeighborFinder.h"
#include <utilities/io/STLReaderWriter.h>
#include <utilities/io/GridVTKWriter.h>
#include <utilities/Transformator.h>

using namespace testing;



class TriangleRefinementTest : public Test {
public:
    TriangleRefinement *refiner;
    std::vector<struct Triangle> triangles;

    std::string absolutePath;

    void SetUp() {
        absolutePath = PATH_TO_DATA;
        triangles = STLReaderWriter::readSTL(absolutePath + "TESTSUITE/STL/TriangleNeighborFinderTest/quadarASCII1x1.stl", Transformator());
        refiner = new TriangleRefinement(&triangles);
    }
};

TEST_F(TriangleRefinementTest, refineOneTriangle_shouldCreateTwoMoreTriangle) {
    int oldSize = (int)triangles.size();
    refiner->refine(0);

    ASSERT_THAT(triangles.size(), Eq(oldSize + 2));
}


TEST_F(TriangleRefinementTest, refineOneTriangle_triangleShouldBeDeleteAfterRefine) {
    int refine = 0;
    struct Triangle oldTriangle = triangles[refine];
    refiner->refine(refine);

    ASSERT_FALSE(oldTriangle.getNumberOfCommonEdge(triangles[refine]) == 3);
}

TEST_F(TriangleRefinementTest, refineOneTriangle_newTrianglesAtTheEndMustHaveTwoCommonEdgesWithOld) {
    int refine = 0;
    struct Triangle oldTriangle = triangles[refine];
    refiner->refine(refine);

    struct Triangle firstNewTriangle = triangles[triangles.size() - 3];
    struct Triangle secondNewTriangle = triangles[triangles.size() - 4];
    EXPECT_THAT(oldTriangle.getNumberOfCommonEdge(firstNewTriangle), Eq(2));
    EXPECT_THAT(oldTriangle.getNumberOfCommonEdge(secondNewTriangle), Eq(2));
}

TEST_F(TriangleRefinementTest, refineQuadar_shouldDoubleTheTriangles_PlusTwoCauseOfFirstLoop) {
    int oldSize = (int)triangles.size();
    refiner->refineUntilMinDistance(1);

    ASSERT_THAT(triangles.size(), Eq(oldSize * 2 + 2));
}


TEST_F(TriangleRefinementTest, getHalfVertex){
    Vertex v1(10.0, 5.0, -2.0);
    Vertex v2(5.0, 0.0, 10);

    Vertex half = TriangleRefinement::getHalfVertex(v1, v2);


    EXPECT_THAT((double)half.x, DoubleEq(7.5));
    EXPECT_THAT((double)half.y, DoubleEq(2.5));
    EXPECT_THAT((double)half.z, DoubleEq(4));
}


TEST_F(TriangleRefinementTest, getLongestDistance){

    struct Triangle t = Triangle(Vertex(0, 0, 0), Vertex(10, 0, 0), Vertex(1, 1, 0), Vertex(0, 0, 0));

    doubflo d = TriangleRefinement::getLongestEdgeDistance(t);
    ASSERT_THAT((double)d, DoubleEq(10.0));
}

TEST_F(TriangleRefinementTest, getLongestDistanceEdge_ExpectEdgeZero){

    struct Triangle t = Triangle(Vertex(0, 0, 0), Vertex(10, 0, 0), Vertex(4, 4, 0), Vertex(0, 0, 0));

    int edge = TriangleRefinement::getEdgeWithLongestDistance(t);
    ASSERT_THAT(edge, Eq(0));
}

TEST_F(TriangleRefinementTest, getLongestDistanceEdge_ExpectEdgeOne){

    struct Triangle t = Triangle(Vertex(4, 4, 0), Vertex(10, 0, 0), Vertex(0, 0, 0), Vertex(0, 0, 0));

    int edge = TriangleRefinement::getEdgeWithLongestDistance(t);
    ASSERT_THAT(edge, Eq(1));
}

TEST_F(TriangleRefinementTest, getLongestDistanceEdge_ExpectEdgeTwo){

    struct Triangle t = Triangle(Vertex(0, 0, 0), Vertex(4, 4, 0), Vertex(10, 0, 0), Vertex(0, 0, 0));

    int edge = TriangleRefinement::getEdgeWithLongestDistance(t);
    ASSERT_THAT(edge, Eq(2));
}
