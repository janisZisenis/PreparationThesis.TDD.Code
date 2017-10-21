#include "PolyDataWriter.h"

#include <vtkSmartPointer.h>
#include <vtkMath.h>
#include <vtkArrowSource.h>
#include <vtkXMLPolyDataWriter.h>
#include <vtkTransformPolyDataFilter.h>
#include <vtkTransform.h>
#include <vtkCleanPolyData.h>
#include <vtkAppendPolyData.h>

#include "ExceptionVtkWriter.h"


class PolyDataWriter::impl {
    public:
    std::vector<double> startVector;
    std::vector<double> endVector;
    std::vector<vtkSmartPointer<vtkPolyData> > arrowsPolyData;

    void addTransformPolyDataObjects();
    vtkSmartPointer<vtkPolyData> buildPolyDataObject(int arrow);
    vtkSmartPointer<vtkMatrix4x4> getTransformationMatrix(double startPoint[3], double endPoint[3]);
    double getArrowLength(double startPoint[3], double endPoint[3]);
    vtkSmartPointer<vtkTransform> getVtkTransformObject(double startPoint[3], vtkSmartPointer<vtkMatrix4x4> matrix, double length);
    vtkSmartPointer<vtkTransformPolyDataFilter> getVtkTransformPdFilter(vtkSmartPointer<vtkTransform> transform, vtkSmartPointer<vtkArrowSource> arrowSource);
    vtkSmartPointer<vtkPolyData> getVtkPolyDataInput(vtkSmartPointer<vtkTransformPolyDataFilter> transformPD);

    vtkSmartPointer<vtkCleanPolyData> movePolyDatasToCleanPolyData();
    void writeOutPutToFile(std::string &filename, vtkSmartPointer<vtkCleanPolyData> cleanFilter);
};

PolyDataWriter::PolyDataWriter() : pimpl(new impl())
{
}

PolyDataWriter::~PolyDataWriter()
{
    delete pimpl;
}

void PolyDataWriter::addVectorArrow(double start[3], double end[3]) {
    pimpl->startVector.push_back((double)start[0]);
    pimpl->startVector.push_back((double)start[1]);
    pimpl->startVector.push_back((double)start[2]);

    pimpl->endVector.push_back((double)end[0]);
    pimpl->endVector.push_back((double)end[1]);
    pimpl->endVector.push_back((double)end[2]);   
}

void PolyDataWriter::writePolyDataToFile(std::string filename)
{
    std::cout << "write " << (pimpl->startVector.size() / 3) <<" Q - vector arrows to file : " << filename << std::endl;
    if (pimpl->startVector.size() == 0)
        throw writePolyDataFileWithoutContent();

    pimpl->addTransformPolyDataObjects();
    vtkSmartPointer<vtkCleanPolyData> cleanFilter = pimpl->movePolyDatasToCleanPolyData();
    pimpl->writeOutPutToFile(filename, cleanFilter);
    std::cout << "write Q-vector arrows finish! " << filename << std::endl;
}

/*#################################################################################*/
/*---------------------------------private methods---------------------------------*/
/*---------------------------------------------------------------------------------*/
void PolyDataWriter::impl::addTransformPolyDataObjects()
{
    for (int arrow = 0; arrow < startVector.size(); arrow += 3)
        arrowsPolyData.push_back(buildPolyDataObject(arrow));
}

vtkSmartPointer<vtkPolyData> PolyDataWriter::impl::buildPolyDataObject(int arrow)
{
    double startPoint[3] = { startVector[arrow], startVector[arrow + 1], startVector[arrow + 2] };
    double endPoint[3] = { endVector[arrow], endVector[arrow + 1], endVector[arrow + 2] };
    vtkSmartPointer<vtkMatrix4x4> matrix = getTransformationMatrix(startPoint, endPoint);
    double length = getArrowLength(startPoint, endPoint);

    vtkSmartPointer<vtkTransform> transform = getVtkTransformObject(startPoint, matrix, length);
    vtkSmartPointer<vtkTransformPolyDataFilter> transformPD = getVtkTransformPdFilter(transform, vtkSmartPointer<vtkArrowSource>::New());
    return getVtkPolyDataInput(transformPD);
}

vtkSmartPointer<vtkMatrix4x4> PolyDataWriter::impl::getTransformationMatrix(double startPoint[3], double endPoint[3])
{
    // Compute a basis
    double normalizedX[3], normalizedY[3], normalizedZ[3];

    // The X axis is a vector from start to end
    vtkMath::Subtract(endPoint, startPoint, normalizedX);
    vtkMath::Normalize(normalizedX);

    // The Z axis is an arbitrary vector cross X
    double arbitrary[3];
    arbitrary[0] = vtkMath::Random(-10, 10);
    arbitrary[1] = vtkMath::Random(-10, 10);
    arbitrary[2] = vtkMath::Random(-10, 10);
    vtkMath::Cross(normalizedX, arbitrary, normalizedZ);
    vtkMath::Normalize(normalizedZ);

    // The Y axis is Z cross X
    vtkMath::Cross(normalizedZ, normalizedX, normalizedY);
    vtkSmartPointer<vtkMatrix4x4> matrix =
        vtkSmartPointer<vtkMatrix4x4>::New();

    // Create the direction cosine matrix
    matrix->Identity();
    for (unsigned int i = 0; i < 3; i++)
    {
        matrix->SetElement(i, 0, normalizedX[i]);
        matrix->SetElement(i, 1, normalizedY[i]);
        matrix->SetElement(i, 2, normalizedZ[i]);
    }
    return matrix;
}


double PolyDataWriter::impl::getArrowLength(double startPoint[3], double endPoint[3])
{
    double vec[3];
    vtkMath::Subtract(endPoint, startPoint, vec);
    return vtkMath::Norm(vec);
}

vtkSmartPointer<vtkTransform> PolyDataWriter::impl::getVtkTransformObject(double startPoint[3], vtkSmartPointer<vtkMatrix4x4> matrix, double length)
{
    vtkSmartPointer<vtkTransform> transform =
        vtkSmartPointer<vtkTransform>::New();

    transform->Translate(startPoint);
    transform->Concatenate(matrix);
    transform->Scale(length, length, length);
    return transform;
}

vtkSmartPointer<vtkTransformPolyDataFilter> PolyDataWriter::impl::getVtkTransformPdFilter(vtkSmartPointer<vtkTransform> transform, vtkSmartPointer<vtkArrowSource> arrowSource)
{
    vtkSmartPointer<vtkTransformPolyDataFilter> transformPD =
        vtkSmartPointer<vtkTransformPolyDataFilter>::New();
    transformPD->SetTransform(transform);
    transformPD->AddInputConnection(arrowSource->GetOutputPort());
    transformPD->Update();        
    return transformPD;
}


vtkSmartPointer<vtkPolyData> PolyDataWriter::impl::getVtkPolyDataInput(vtkSmartPointer<vtkTransformPolyDataFilter> transformPD)
{
    vtkSmartPointer<vtkPolyData> input =
        vtkSmartPointer<vtkPolyData>::New();
    input->ShallowCopy(transformPD->GetOutput());
    return input;
}

/*---------------------------------------------------------------------------------*/

vtkSmartPointer<vtkCleanPolyData> PolyDataWriter::impl::movePolyDatasToCleanPolyData()
{
    vtkSmartPointer<vtkAppendPolyData> appendFilter =
        vtkSmartPointer<vtkAppendPolyData>::New();
    for (int i = 0; i < arrowsPolyData.size(); i++) {
        appendFilter->AddInputData(arrowsPolyData[i]);
    }
    appendFilter->Update();

    // Remove any duplicate points.
    vtkSmartPointer<vtkCleanPolyData> cleanFilter =
        vtkSmartPointer<vtkCleanPolyData>::New();
    cleanFilter->SetInputConnection(appendFilter->GetOutputPort());
    cleanFilter->Update();
    return cleanFilter;
}

void PolyDataWriter::impl::writeOutPutToFile(std::string &filename, vtkSmartPointer<vtkCleanPolyData> cleanFilter)
{
    vtkSmartPointer<vtkXMLPolyDataWriter> writer = vtkSmartPointer<vtkXMLPolyDataWriter>::New();
    filename += ".vtp";
    writer->SetFileName(filename.c_str());
    writer->SetInputConnection(cleanFilter->GetOutputPort());
    writer->Write();
}
