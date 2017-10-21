#include "PolyDataWriter.h"
#include "gmock/gmock.h"
#include <fstream>

#include "ExceptionVtkWriter.h"

using namespace testing;

class PolyDataWriterTest : public Test {
public:
    PolyDataWriter writer;
};

TEST_F(PolyDataWriterTest, writeAnPolyDataFileWithoutConent_ShoultThrowException) {
    ASSERT_THROW(writer.writePolyDataToFile("emptyFile"), writePolyDataFileWithoutContent);
}

TEST_F(PolyDataWriterTest, writeAnPolyDataFileWithTwoArrows_ShoutlWriteFileWith_38_Points) {
    double startpoint[3] = { 1, 2, 3 };
    double endpoint[3] = { 5, 5, 5 };
    double startpoint2[3] = { 2, 2, 2 };
    double endpoint2[3] = { -5.0, -5.0, -5.0 };
    writer.addVectorArrow(startpoint, endpoint);
    writer.addVectorArrow(startpoint2, endpoint2);

    std::string filename = "file";
    writer.writePolyDataToFile(filename);


    std::ifstream file("file.vtp");
    std::string keyWord = "NumberOfPoints=\"38\"";
    std::string word;

    bool findCoorectValue = false;
    while (file >> word)
    {
        if (word == keyWord)
        {
            findCoorectValue = true;
        }
    }
    ASSERT_TRUE(findCoorectValue);
}
