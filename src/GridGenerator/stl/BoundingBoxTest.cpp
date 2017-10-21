#include "gmock/gmock.h"

#include <stl/Triangle.h>
#include <stl/BoundingBox.h>
#include <stl/Vertex.h>
#include "TriangleRefinement.h"

using namespace testing;


TEST(BoundingBoxTest, initWithTriangle_whenTheValueIsIntegerBoxHasToPLUS_or_MINUS_ONE) {
    doubflo minX = 1.0f;
    doubflo minY = 23.0f;
    doubflo minZ = 1.1222f;

    doubflo maxX = 110.0f;
    doubflo maxY = 50.0f;
    doubflo maxZ = 12122.23f;
    struct BoundingBox box = BoundingBox(Triangle(Vertex(maxX, maxY - 10, minZ + 2), Vertex(minX, maxY, maxZ), Vertex(minX + 3, minY, minZ), Vertex(0.0f, 0.0f, 0.0f)));
    EXPECT_THAT(box.minX, Eq(minX - 1));
    EXPECT_THAT(box.minY, Eq(minY - 1));
    EXPECT_THAT(box.minZ, Eq((int)minZ));

    EXPECT_THAT(box.maxX, Eq(maxX + 1));
    EXPECT_THAT(box.maxY, Eq(maxY + 1));
    EXPECT_THAT(box.maxZ, Eq((int)maxZ + 1));
}

TEST(BoundingBoxTest, initWithTriangle2) {

    struct Triangle t = Triangle(Vertex(20.0f, 1.0f, 1.0f), Vertex(1.0f, 1.0f, 1 + 1e-006f), Vertex(20.0f, 20.0f, 1.0f), Vertex(1.0f, 0.0f, 0.0f));

    struct BoundingBox box = BoundingBox(t);
    EXPECT_THAT(box.minX, Eq(0));
    EXPECT_THAT(box.minY, Eq(0));
    EXPECT_THAT(box.minZ, Eq(0));

    EXPECT_THAT(box.maxX, Eq(21));
    EXPECT_THAT(box.maxY, Eq(21));
    EXPECT_THAT(box.maxZ, Eq(2));
}


TEST(BoundingBoxTest, initWithTriangle3) {

    struct Triangle t = Triangle(Vertex(20.0f, 20.0f, 20.0f), Vertex(1.0f, 20.0f, 20.0f), Vertex(20.0f, 1.0f, 20.0f), Vertex(1.0f, 0.0f, 0.0f));

    struct BoundingBox box = BoundingBox(t);
    EXPECT_THAT(box.minX, Eq(0));
    EXPECT_THAT(box.minY, Eq(0));
    EXPECT_THAT(box.minZ, Eq(19));

    EXPECT_THAT(box.maxX, Eq(21));
    EXPECT_THAT(box.maxY, Eq(21));
    EXPECT_THAT(box.maxZ, Eq(21));
}

TEST(BoundingBoxTest, whenAllValueIsFloatBoxHasToCEIL_OR_FLOOR) {

    doubflo minX = 1.5f;
    doubflo minY = 23.2f;
    doubflo minZ = 1.1222f;

    doubflo maxX = 110.4f;
    doubflo maxY = 50.5f;
    doubflo maxZ = 12122.23f;
    struct BoundingBox box = BoundingBox(Triangle(Vertex(maxX, maxY - 10, minZ + 2), Vertex(minX, maxY, maxZ), Vertex(minX + 3, minY, minZ), Vertex(0.0f, 0.0f, 0.0f)));
    EXPECT_THAT(box.minX, Eq((int)minX));
    EXPECT_THAT(box.minY, Eq((int)minY));
    EXPECT_THAT(box.minZ, Eq((int)minZ));

    EXPECT_THAT(box.maxX, Eq((int)maxX + 1));
    EXPECT_THAT(box.maxY, Eq((int)maxY + 1));
    EXPECT_THAT(box.maxZ, Eq((int)maxZ + 1));

}



TEST(BoundingBoxTest, whenBoxIntesectInOnePoint_ShouldReturnTrue) {

    doubflo minX = 0;
    doubflo minY = 0;
    doubflo minZ = 0;

    doubflo maxX = 5;
    doubflo maxY = 5;
    doubflo maxZ = 5;
    struct BoundingBox box = BoundingBox(minX, maxX, minY, maxY, minZ, maxZ);

    minX = 5;
    minY = 5;
    minZ = 5;

    maxX = 10;
    maxY = 10;
    maxZ = 10;
    struct BoundingBox boxCompare = BoundingBox(minX, maxX, minY, maxY, minZ, maxZ);

    EXPECT_TRUE(box.intersect(boxCompare));

}


TEST(BoundingBoxTest, whenBoxNotIntesect_ShouldReturnFalse) {

    doubflo minX = 0;
    doubflo minY = 0;
    doubflo minZ = 0;

    doubflo maxX = 5;
    doubflo maxY = 5;
    doubflo maxZ = 5;
    struct BoundingBox box = BoundingBox(minX, maxX, minY, maxY, minZ, maxZ);

    minX = 7;
    minY = 8;
    minZ = 12;

    maxX = 10;
    maxY = 10;
    maxZ = 10;
    struct BoundingBox boxCompare = BoundingBox(minX, maxX, minY, maxY, minZ, maxZ);

    EXPECT_FALSE(box.intersect(boxCompare));

}
