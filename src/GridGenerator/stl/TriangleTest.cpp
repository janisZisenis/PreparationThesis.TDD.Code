#include "gmock/gmock.h"
#include <utilities/io/STLReaderWriter.h>
#include <utilities/io/GridVTKWriter.h>
#include <utilities/Transformator.h>

#include "Triangle.h"

using namespace testing;

class TriangleTest : public Test {
public:
    std::string absolutePath;

    void SetUp() {
        std::string path = PATH_TO_DATA;
        std::string test = TESTSUITE;
        absolutePath = path + test + "STL/TriangleTest/";

    }
};

TEST_F(TriangleTest, getClosestPointsOnEdgesFromTriangle){
    struct Triangle  t = Triangle(Vertex(0, 0, 0), Vertex(10, 0, 0), Vertex(0, 10, 0), Vertex(0, 0, 1));
    struct Vertex P4 = Vertex(0, 1, 5);

    struct Vertex p[3];
    t.getClosestPointsOnEdges(p, P4);
    EXPECT_THAT((double)p[0].x, DoubleEq(0.0));
    EXPECT_THAT((double)p[0].y, DoubleEq(0.0));
    EXPECT_THAT((double)p[0].z, DoubleEq(0.0));

    EXPECT_THAT((double)p[1].x, DoubleEq(4.5));
    EXPECT_THAT((double)p[1].y, DoubleEq(5.5));
    EXPECT_THAT((double)p[1].z, DoubleEq(0.0));

    EXPECT_THAT((double)p[2].x, DoubleEq(0.0));
    EXPECT_THAT((double)p[2].y, DoubleEq(1.0));
    EXPECT_THAT((double)p[2].z, DoubleEq(0.0));
}

TEST_F(TriangleTest, getAngleBetweenVectorAndClosestPointOnEdgeWhenPointIsOnTriangle_ExpectNull){

    struct Triangle t = Triangle(Vertex(0, 0, 0), Vertex(10, 0, 0), Vertex(0, 10, 0), Vertex(0, 0, 1));
    struct Vertex P4 = Vertex(5, 5, 0);

    struct Triangle n1 = Triangle(Vertex(0, 0, 0), Vertex(10, 0, 0), Vertex(22, 10, 0), Vertex(0, 0, 1));
    struct Triangle n2 = Triangle(Vertex(22, 0, 0), Vertex(10, 0, 0), Vertex(0, 10, 0), Vertex(0, 0, 1));
    struct Triangle n3 = Triangle(Vertex(0, 0, 0), Vertex(10, 22, 0), Vertex(0, 10, 0), Vertex(0, 0, 1));

    int size = 3;

    doubflo angles[3];
    t.getAnglesBetweenVectorAndClosestPointOnEdge(P4, angles);
    EXPECT_THAT((double)angles[0], DoubleEq(0.0));
    EXPECT_THAT((double)angles[1], DoubleEq(0.0));
    EXPECT_THAT((double)angles[2], DoubleEq(0.0));
}

TEST_F(TriangleTest, PointIsNotWithinTriangle){

    struct Triangle t = Triangle(Vertex(0, 0, 0), Vertex(10, 0, 0), Vertex(0, 10, 0), Vertex(0, 0, 1));
    struct Vertex P4 = Vertex(1, 1, -2);

    doubflo d1, d2, d3;
    t.getDistanceToMeasureIfPointIsWithin(d1, d2, d3, P4);
    EXPECT_TRUE(d1 < 0.0);
    EXPECT_TRUE(d2 < 0.0);
    EXPECT_TRUE(d3 < 0.0);
}

TEST_F(TriangleTest, calculatePerpendicularPoint){

    struct Triangle t = Triangle(Vertex(0, 0, 0), Vertex(10, 0, 0), Vertex(0, 10, 0), Vertex(0, 0, 1));
    struct Vertex  P4 = Vertex(8, 5, -3);

    struct Vertex distPbances = t.getPerpedicularPointFrom(P4);
    EXPECT_THAT((double)distPbances.x, DoubleEq(8.0));
    EXPECT_THAT((double)distPbances.y, DoubleEq(5.0));
    EXPECT_THAT((double)distPbances.z, DoubleEq(0.0));
}

TEST_F(TriangleTest, pointintersectTriangle_directionIntoTriangle_ExpectReturn1){

    struct Vertex normal = Vertex(-1.0f, 0.0f, 0.0f);
    struct Triangle t = Triangle(Vertex(3.5, 0, 0), Vertex(3.5, 0, 9), Vertex(3.5, 9, 9), normal);
    struct Vertex v = Vertex(3, 5, 5);
    struct Vertex direction = Vertex(-normal.x, 0, 0);
    struct Vertex intersect;

    doubflo q;
    int err = t.getTriangleIntersection(v, direction, intersect, q);
    ASSERT_THAT(err, Eq(1));
}


TEST_F(TriangleTest, pointintersectTriangle_directionAgainstTriangle_ExpectReturn0){

    struct Vertex normal = Vertex(-1.0f, 0.0f, 0.0f);
    struct Triangle t = Triangle(Vertex(3.5, 0, 0), Vertex(3.5, 0, 9), Vertex(3.5, 9, 9), normal);
    struct Vertex v = Vertex(3, 5, 5);
    struct Vertex direction = Vertex(normal.x, 0, 0);
    struct Vertex intersect;

    doubflo q;
    int err = t.getTriangleIntersection(v, direction, intersect, q);
    ASSERT_THAT(err, Eq(0));
}


TEST_F(TriangleTest, getHalfAngleBetweenTwoEqualTriangles_ExpectNullAngle) {
    struct Triangle t1 = Triangle(Vertex(0, 0, 0), Vertex(10, 0, 0), Vertex(0, 10, 0), Vertex(0, 0, 1));
    struct Triangle t2 = Triangle(Vertex(0, 0, 0), Vertex(10, 0, 0), Vertex(0, 10, 0), Vertex(0, 0, 1));
    double angle = (double)t1.getHalfAngleBetweenToAdjacentTriangle(t2);
    ASSERT_THAT(angle, DoubleEq(0.0));
}

TEST_F(TriangleTest, checkSTLwith90degreeOutpointingNormal) {
    std::vector<struct Triangle> triangles;
    triangles = STLReaderWriter::readSTL(absolutePath + "90degreeOutpointingNormal.stl", Transformator());

    doubflo alpha = triangles[0].getHalfAngleBetweenToAdjacentTriangle(triangles[1]);
    ASSERT_THAT((double)alpha, DoubleEq(90.0 / 2.0));
}

TEST_F(TriangleTest, checkSTLwith90degreeInpointingNormal) {
    std::vector<struct Triangle> triangles;
    triangles = STLReaderWriter::readSTL(absolutePath + "90degreeInpointingNormal.stl", Transformator());

    doubflo alpha = triangles[0].getHalfAngleBetweenToAdjacentTriangle(triangles[1]);
    ASSERT_THAT((double)alpha, DoubleEq(270.0 / 2.0));
}

TEST_F(TriangleTest, checkSTLwith180degreeOutpointingNormal) {
    std::vector<struct Triangle> triangles;
    triangles = STLReaderWriter::readSTL(absolutePath + "180degreeOutpointingNormal.stl", Transformator());

    doubflo alpha = triangles[0].getHalfAngleBetweenToAdjacentTriangle(triangles[1]);
    ASSERT_THAT((double)alpha, DoubleEq(180.0 / 2.0));
}

TEST_F(TriangleTest, checkSTLwithSmallDegreeOutpointingNormal) {
    std::vector<struct Triangle> triangles;
    triangles = STLReaderWriter::readSTL(absolutePath + "SmallDegreeOutpointingNormal.stl", Transformator());

    doubflo alpha = triangles[0].getHalfAngleBetweenToAdjacentTriangle(triangles[1]);
    ASSERT_TRUE(alpha < 30.0);
}

TEST_F(TriangleTest, checkSTLwithBigDegreeInpointingNormal) {
    std::vector<struct Triangle> triangles;
    triangles = STLReaderWriter::readSTL(absolutePath + "BigDegreeInpointingNormal.stl", Transformator());

    doubflo alpha = triangles[0].getHalfAngleBetweenToAdjacentTriangle(triangles[1]);
    ASSERT_TRUE(alpha > 330.0 / 2);
}

TEST_F(TriangleTest, getCommonEdgesFromTheSameTriangle_ExpectThreeEdges){
    struct Triangle t1 = Triangle(Vertex(0.0f, 0.0f, 0.0f), Vertex(10.0f, 0.0f, 0.0f), Vertex(0.0f, 10.0f, 0.0f), Vertex(0.0f, 0.0f, 1.0f));
    struct Triangle t2 = Triangle(Vertex(0.0f, 0.0f, 0.0f), Vertex(10.0f, 0.0f, 0.0f), Vertex(0.0f, 10.0f, 0.0f), Vertex(0.0f, 0.0f, 1.0f));
    int num = t1.getNumberOfCommonEdge(t2);
    ASSERT_THAT(num, Eq(3));
}
