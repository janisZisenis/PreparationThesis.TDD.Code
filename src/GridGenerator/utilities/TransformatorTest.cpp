#include "Transformator.h"
#include "Exception.h"

#include "gmock/gmock.h"
using namespace testing;

class TransformatorTest : public Test {
public:

};


TEST_F(TransformatorTest, transformVectorWithStandartConstructor_ExpectnoVectorChange) {
    Transformator trafo;
    doubflo mx = 2.0f;
    doubflo my = -3.2f;
    doubflo mz = 4.6f;
    struct Vertex v = Vertex(mx, my, mz);
    trafo.transformWorldToView(v);
    EXPECT_THAT((double)mx, DoubleEq(v.x));
    EXPECT_THAT((double)my, DoubleEq(v.y));
    EXPECT_THAT((double)mz, DoubleEq(v.z));
}

TEST_F(TransformatorTest, transformVectorWithSmallDelta_ExpectVectorChanges) {
    doubflo delta = 0.01f;
    Transformator trafo(delta, Vertex(0, 0, 0));
    doubflo mx = 2.0f;
    doubflo my = -3.2f;
    doubflo mz = 4.6f;
    struct Vertex v = Vertex(mx, my, mz);
    trafo.transformWorldToView(v);
    EXPECT_THAT((double)(mx / delta), DoubleEq(v.x));
    EXPECT_THAT((double)(my / delta), DoubleEq(v.y));
    EXPECT_THAT((double)(mz / delta), DoubleEq(v.z));
}

TEST_F(TransformatorTest, transformVectorWithNullDelta_ExpectExcpetion) {
    doubflo delta = 0.0f;
    ASSERT_THROW(Transformator trafo(delta, Vertex(0, 0, 0)), invalidDelta);
}

TEST_F(TransformatorTest, transformVectorWithNEgativeDelta_ExpectExcpetion) {
    doubflo delta = -1.0f;
    ASSERT_THROW(Transformator trafo(delta, Vertex(0, 0, 0)), invalidDelta);
}

TEST_F(TransformatorTest, transformVectorWithTranslations) {
    doubflo dx = -2.6f;
    doubflo dy = 3434.0f;
    doubflo dz = 0.1f;
    Transformator trafo(1.0f, Vertex(dx, dy, dz));
    doubflo mx = 2.0f;
    doubflo my = -3.2f;
    doubflo mz = 4.6f;
    Vertex v = Vertex(mx, my, mz);
    trafo.transformWorldToView(v);
    EXPECT_THAT((double)(mx + dx), DoubleEq(v.x));
    EXPECT_THAT((double)(my + dy), DoubleEq(v.y));
    EXPECT_THAT((double)(mz + dz), DoubleEq(v.z));
}

TEST_F(TransformatorTest, transformVectorWithTranslationsAndSmallDelta) {
    doubflo delta = 0.0001f;
    doubflo dx = -2.6f;
    doubflo dy = 3434.0f;
    doubflo dz = 0.1f;
    Transformator trafo(delta, Vertex(dx, dy, dz));
    doubflo mx = 2.0f;
    doubflo my = -3.2f;
    doubflo mz = 4.6f;
    Vertex v = Vertex(mx, my, mz);
    trafo.transformWorldToView(v);
    EXPECT_THAT((double)((mx + dx) / delta), DoubleEq(v.x));
    EXPECT_THAT((double)((my + dy) / delta), DoubleEq(v.y));
    EXPECT_THAT((double)((mz + dz) / delta), DoubleEq(v.z));
}

TEST_F(TransformatorTest, transformVectorToWorldCoodinates) {
    doubflo delta = 0.0001f;
    doubflo dx = -2.6f;
    doubflo dy = 3434.0f;
    doubflo dz = 0.1f;
    Transformator trafo(delta, Vertex(dx, dy, dz));
    doubflo mx = 2.0f;
    doubflo my = -3.2f;
    doubflo mz = 4.6f;
    Vertex v = Vertex(mx, my, mz);
    trafo.transformViewToWorld(v);
    EXPECT_THAT((double)(mx  * delta - dx), DoubleEq(v.x));
    EXPECT_THAT((double)(my  * delta - dy), DoubleEq(v.y));
    EXPECT_THAT((double)(mz  * delta - dz), DoubleEq(v.z));
}
