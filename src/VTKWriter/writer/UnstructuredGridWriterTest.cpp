#include "UnstructuredGridWriter.h"
#include "gmock/gmock.h"
#include <fstream>

#include "ExceptionVtkWriter.h"

using namespace testing;

class UnstructuredGridWriterTest : public Test {
public:
    UnstructuredGridWriter writer;
};

TEST_F(UnstructuredGridWriterTest, initalTest) {
}
