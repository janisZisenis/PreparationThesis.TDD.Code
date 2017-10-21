#include "UnstructuredGridWriter.h"
#include <vtkSmartPointer.h>

//VTK - Reading and rendering
#include <vtkXMLUnstructuredGridReader.h>
#include <vtkDataSetMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>

//VTK - writing unstructured grid with ...
#include <vtkUnstructuredGrid.h>
#include <vtkXMLUnstructuredGridWriter.h>
#include <vtkPointData.h>
#include <vtkDoubleArray.h>
#include <vtkVertex.h> //Points
#include <vtkVoxel.h>  // Voxel (Bounding Box)
#include <vtkTriangle.h> //Triangles


class UnstructuredGridWriter::impl {
    public:
    vtkSmartPointer<vtkPoints> points;
    vtkSmartPointer<vtkUnstructuredGrid> unstructuredGrid;
    vtkSmartPointer<vtkDoubleArray> types;

    impl() {
        points = vtkSmartPointer<vtkPoints>::New();
        unstructuredGrid = vtkSmartPointer<vtkUnstructuredGrid>::New();
        types = vtkSmartPointer<vtkDoubleArray>::New();
    }

    void insertGridPoints(int nz, int ny, int nx);
    void insertCellsPerNode(int numberOfVertices, double * grid);
};

UnstructuredGridWriter::UnstructuredGridWriter() : pimpl(new impl())
{
}

UnstructuredGridWriter::~UnstructuredGridWriter()
{
    delete pimpl;
}


void UnstructuredGridWriter::addVoxel(double node[3], double nodeNX[3], double nodeNY[3], double nodeNYNX[3], double nodeNZ[3], double nodeNZNX[3], double nodeNZNY[3], double nodeNZNYNX[3], int nodeTypes[8])
{
    vtkSmartPointer<vtkVoxel> voxel =
        vtkSmartPointer<vtkVoxel>::New();

    int numberOfActualPoints = pimpl->points->GetNumberOfPoints();
    int numberOfVertices = 8;
    for (int i = numberOfActualPoints; i < (numberOfActualPoints + numberOfVertices); ++i)
        voxel->GetPointIds()->SetId(i - numberOfActualPoints, i);

    pimpl->points->InsertNextPoint(node[0], node[1], node[2]);
    pimpl->points->InsertNextPoint(nodeNX[0], nodeNX[1], nodeNX[2]);
    pimpl->points->InsertNextPoint(nodeNY[0], nodeNY[1], nodeNY[2]);
    pimpl->points->InsertNextPoint(nodeNYNX[0], nodeNYNX[1], nodeNYNX[2]);
    pimpl->points->InsertNextPoint(nodeNZ[0], nodeNZ[1], nodeNZ[2]);
    pimpl->points->InsertNextPoint(nodeNZNX[0], nodeNZNX[1], nodeNZNX[2]);
    pimpl->points->InsertNextPoint(nodeNZNY[0], nodeNZNY[1], nodeNZNY[2]);
    pimpl->points->InsertNextPoint(nodeNZNYNX[0], nodeNZNYNX[1], nodeNZNYNX[2]);

    pimpl->unstructuredGrid->SetPoints(pimpl->points);
    pimpl->unstructuredGrid->InsertNextCell(voxel->GetCellType(), voxel->GetPointIds());

    for (int i = 0; i < 8; i++) {
        pimpl->types->InsertNextValue(nodeTypes[i]);
    }
    
}


void UnstructuredGridWriter::addCellCoords(std::vector<float> coordX, std::vector<float> coordY, std::vector<float> coordZ, std::vector<unsigned int> type)
{
    if (pimpl->points->GetNumberOfPoints() > 0) printf("\n\n\nWarning: there are already points in points-list. Will cause bad output-results!\n\n");

    for (int i = 0; i < coordX.size(); i++) {
        pimpl->points->InsertNextPoint(coordX[i], coordY[i], coordZ[i]);
        pimpl->types->InsertNextValue(type[i]);
    }
    pimpl->unstructuredGrid->SetPoints(pimpl->points);
}

void UnstructuredGridWriter::buildCell(int index, int indexX, int indexY, int indexYX, int indexZ, int indexZX, int indexZY, int indexZYX)
{
    vtkSmartPointer<vtkVoxel> voxel = vtkSmartPointer<vtkVoxel>::New();
    int i = 0;
    voxel->GetPointIds()->SetId(i++, index);
    voxel->GetPointIds()->SetId(i++, indexX);
    voxel->GetPointIds()->SetId(i++, indexY);
    voxel->GetPointIds()->SetId(i++, indexYX);
    voxel->GetPointIds()->SetId(i++, indexZ);
    voxel->GetPointIds()->SetId(i++, indexZX);
    voxel->GetPointIds()->SetId(i++, indexZY);
    voxel->GetPointIds()->SetId(i++, indexZYX);

    pimpl->unstructuredGrid->InsertNextCell(voxel->GetCellType(), voxel->GetPointIds());
}

void UnstructuredGridWriter::addBoundingBox(double boundingBox[6], int type)
{
    vtkSmartPointer<vtkVoxel> voxel =
        vtkSmartPointer<vtkVoxel>::New();

    int numberOfActualPoints = pimpl->points->GetNumberOfPoints();
    int numberOfVertices = 8;
    for (int i = numberOfActualPoints; i < (numberOfActualPoints + numberOfVertices); ++i) {
        voxel->GetPointIds()->SetId(i - numberOfActualPoints, i);
        pimpl->types->InsertNextValue(type);
    }   

    pimpl->points->InsertNextPoint(boundingBox[0], boundingBox[2], boundingBox[4]); //0,0,0
    pimpl->points->InsertNextPoint(boundingBox[1], boundingBox[2], boundingBox[4]); //1,0,0
    pimpl->points->InsertNextPoint(boundingBox[0], boundingBox[3], boundingBox[4]); //0,1,0
    pimpl->points->InsertNextPoint(boundingBox[1], boundingBox[3], boundingBox[4]); //1,1,0
    pimpl->points->InsertNextPoint(boundingBox[0], boundingBox[2], boundingBox[5]);
    pimpl->points->InsertNextPoint(boundingBox[1], boundingBox[2], boundingBox[5]);
    pimpl->points->InsertNextPoint(boundingBox[0], boundingBox[3], boundingBox[5]);
    pimpl->points->InsertNextPoint(boundingBox[1], boundingBox[3], boundingBox[5]);

    pimpl->unstructuredGrid->SetPoints(pimpl->points);
    pimpl->unstructuredGrid->InsertNextCell(voxel->GetCellType(), voxel->GetPointIds());
}

void UnstructuredGridWriter::addTriangle(double v1[3], double v2[3], double v3[3], int type[3])
{
    vtkSmartPointer<vtkTriangle> triangle = vtkSmartPointer<vtkTriangle>::New();

    int numberOfActualPoints = pimpl->points->GetNumberOfPoints();
    int numberOfVertices = 3;
    for (int i = numberOfActualPoints; i < (numberOfActualPoints + numberOfVertices); ++i)
        triangle->GetPointIds()->SetId(i - numberOfActualPoints, i);

    pimpl->points->InsertNextPoint(v1[0], v1[1], v1[2]);
    pimpl->points->InsertNextPoint(v2[0], v2[1], v2[2]);
    pimpl->points->InsertNextPoint(v3[0], v3[1], v3[2]);

    pimpl->types->InsertNextValue(type[0]);
    pimpl->types->InsertNextValue(type[1]);
    pimpl->types->InsertNextValue(type[2]);

    pimpl->unstructuredGrid->SetPoints(pimpl->points);
    pimpl->unstructuredGrid->InsertNextCell(triangle->GetCellType(), triangle->GetPointIds());
}

void UnstructuredGridWriter::addGridPoints(double grid[], int nx, int ny, int nz)
{
    pimpl->insertGridPoints(nz, ny, nx);
    pimpl->insertCellsPerNode(nx * ny * nz, grid);
}

void UnstructuredGridWriter::addGridPoint(int x, int y, int z, int type)
{
    int numberOfActualPoints = pimpl->points->GetNumberOfPoints();
    pimpl->points->InsertNextPoint(x, y, z);
    pimpl->unstructuredGrid->SetPoints(pimpl->points);

    vtkSmartPointer<vtkVertex> vertex = vtkSmartPointer<vtkVertex>::New();

    vertex->GetPointIds()->SetId(0, numberOfActualPoints);
    pimpl->unstructuredGrid->InsertNextCell(vertex->GetCellType(), vertex->GetPointIds());
    pimpl->types->InsertNextValue(type);
}

void UnstructuredGridWriter::writeUnstructuredGridToFile(std::string filename)
{
    pimpl->unstructuredGrid->GetPointData()->SetScalars(pimpl->types);
    filename = filename + ".vtu";
    printf("write unstructured grid to %s ...\n", filename.c_str());
    vtkSmartPointer<vtkXMLUnstructuredGridWriter> writer = vtkSmartPointer<vtkXMLUnstructuredGridWriter>::New();
    writer->SetFileName(filename.c_str());
    writer->SetInputData(pimpl->unstructuredGrid);
    writer->Write();
    printf("...finish writing unstructured grid!\n");
}


void UnstructuredGridWriter::impl::insertCellsPerNode(int numberOfVertices, double * grid)
{
    int numberOfActualPoints = points->GetNumberOfPoints();
    vtkSmartPointer<vtkVertex> vertex;
    vtkSmartPointer<vtkDoubleArray> types = vtkSmartPointer<vtkDoubleArray>::New();

    for (int i = 0; i < numberOfVertices; i++) {
        vertex = vtkSmartPointer<vtkVertex>::New();
        vertex->GetPointIds()->SetId(0, numberOfActualPoints - i - 1);
        unstructuredGrid->InsertNextCell(vertex->GetCellType(), vertex->GetPointIds());
        types->InsertNextValue(grid[i]);
    }
    unstructuredGrid->GetPointData()->SetScalars(types);
}

void UnstructuredGridWriter::impl::insertGridPoints(int nz, int ny, int nx)
{
    for (int z = 0; z < nz; z++){
        for (int y = 0; y < ny; y++){
            for (int x = 0; x < nx; x++){
                points->InsertNextPoint(x, y, z);
            }
        }
    }
    unstructuredGrid->SetPoints(points);
}

void UnstructuredGridWriter::displayUnstructuredGrid()
{
    vtkSmartPointer<vtkDataSetMapper> mapper =
        vtkSmartPointer<vtkDataSetMapper>::New();
    mapper->SetInputData(pimpl->unstructuredGrid);

    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);

    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    renderer->AddActor(actor);

    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(renderer);

    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
        vtkSmartPointer<vtkRenderWindowInteractor>::New();
    renderWindowInteractor->SetRenderWindow(renderWindow);

    renderer->SetBackground(.3, .6, .3); // Background color green

    renderWindow->Render();
    renderWindowInteractor->Start();
}

void UnstructuredGridWriter::displayUnstructuredGrid(std::string filename)
{
    vtkSmartPointer<vtkXMLUnstructuredGridReader> reader =
        vtkSmartPointer<vtkXMLUnstructuredGridReader>::New();
    reader->SetFileName(filename.c_str());
    reader->Update();

    vtkSmartPointer<vtkDataSetMapper> mapper =
        vtkSmartPointer<vtkDataSetMapper>::New();
    mapper->SetInputData(pimpl->unstructuredGrid);

    vtkSmartPointer<vtkActor> actor =
        vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);

    vtkSmartPointer<vtkRenderer> renderer =
        vtkSmartPointer<vtkRenderer>::New();
    vtkSmartPointer<vtkRenderWindow> renderWindow =
        vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(renderer);
    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
        vtkSmartPointer<vtkRenderWindowInteractor>::New();
    renderWindowInteractor->SetRenderWindow(renderWindow);

    renderer->AddActor(actor);
    renderer->SetBackground(.3, .6, .3); // Background color green

    renderWindow->Render();
    renderWindowInteractor->Start();
}
