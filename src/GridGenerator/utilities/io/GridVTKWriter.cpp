#define _CRT_SECURE_NO_DEPRECATE
#include "GridVTKWriter.h"
#include <iostream>
#include <fstream>
#include <sstream>

#include "GridGenerator/utilities/Transformator.h"
#include <utilities/Logger.h>
#include <grid/kernel/Grid.h>
#include <stl/Vertex.h>

FILE* GridVTKWriter::file = 0;
bool GridVTKWriter::binaer = true;
unsigned int GridVTKWriter::size = 0;
unsigned int GridVTKWriter::nx = 0;
unsigned int GridVTKWriter::ny = 0;
unsigned int GridVTKWriter::nz = 0;
unsigned int GridVTKWriter::startX = 0;
unsigned int GridVTKWriter::startY = 0;
unsigned int GridVTKWriter::startZ = 0;

GridVTKWriter::GridVTKWriter()
{

}

GridVTKWriter::~GridVTKWriter()
{

}

void GridVTKWriter::writeGridToVTK(const struct Grid &grid, std::string name, Transformator trans, bool binaer)
{
    GridVTKWriter::binaer = binaer;
    name += ".vtk";
    std::string output = "Write Grid to vtk output file : " + name + "\n";
    Logger::getInstance()->logTerminal(output);
    initalValues(grid);

    std::string mode = "w";
    if (binaer)
        mode = "wb";
    GridVTKWriter::openFile(name, mode);
    
    Logger::getInstance()->logTerminal("  Output file opened ...\n");

    GridVTKWriter::writeHeader();
    GridVTKWriter::writePoints(trans);
    GridVTKWriter::writeCells();
    GridVTKWriter::writeTypeHeader();
    GridVTKWriter::writeTypes(grid);
    GridVTKWriter::closeFile();

    Logger::getInstance()->logTerminal("Output file closed\n");
}

/*#################################################################################*/
/*---------------------------------private methods---------------------------------*/
/*---------------------------------------------------------------------------------*/
void GridVTKWriter::openFile(std::string name, std::string mode)
{
    file = fopen(name.c_str(), mode.c_str());
}

void GridVTKWriter::initalValues(const struct Grid &grid)
{
    GridVTKWriter::nx = grid.nx;
    GridVTKWriter::ny = grid.ny;
    GridVTKWriter::nz = grid.nz;
    GridVTKWriter::startX = grid.startX;
    GridVTKWriter::startY = grid.startY;
    GridVTKWriter::startZ = grid.startZ;

    GridVTKWriter::size = nx*ny*nz;
}

void GridVTKWriter::closeFile()
{
    GridVTKWriter::end_line();
	fclose(file);
}

void GridVTKWriter::writeHeader()
{
	fprintf(file, "# vtk DataFile Version 3.0\n");
	fprintf(file, "by MeshGenerator\n");
	if (binaer)
		fprintf(file, "BINARY\n");
	else
		fprintf(file, "ASCII\n");
	fprintf(file, "DATASET UNSTRUCTURED_GRID\n");
}

void GridVTKWriter::writePoints(Transformator trans)
{
	fprintf(file, "POINTS %d float\n", size);
    for (unsigned int z = startZ; z < startZ + nz; z++){
        for (unsigned int y = startY; y < startY + ny; y++){
            for (unsigned int x = startX; x < startX + nx; x++){
                Vertex v((doubflo)x, (doubflo)y, (doubflo)z);
				trans.transformViewToWorld(v);
				if (binaer) {
					write_float((float)v.x);
					write_float((float)v.y);
					write_float((float)v.z);
				}
				else
					fprintf(file, "%f %f %f\n", v.x, v.y, v.z);
			}
		}
	}
}

void GridVTKWriter::writeCells()
{
	fprintf(file, "\nCELLS %d %d\n", size, size * 2);
	for (unsigned int i = 0; i < size; ++i)
	{
		if (binaer){
			write_int(1);
			write_int(i);
		}
		else
			fprintf(file, "1 %d\n", i);
	}

	fprintf(file, "\nCELL_TYPES %d\n", size);
	for (unsigned int i = 0; i < size; ++i)
	{
		if (binaer)
			write_int(1);
		else
			fprintf(file, "1 ");
	}
	if (!binaer)
        GridVTKWriter::end_line();
}

void GridVTKWriter::writeTypeHeader()
{
	fprintf(file, "\nPOINT_DATA %d\n", size);
	fprintf(file, "SCALARS type int\n", size);
	fprintf(file, "LOOKUP_TABLE default\n", size);
}

void GridVTKWriter::writeTypes(const struct Grid &grid)
{
	for (unsigned int z = 0; z < nz; z++){
		for (unsigned int y = 0; y < ny; y++){
			for (unsigned int x = 0; x < nx; x++){
				if (binaer)
					write_int(grid.field[x + nx * (y + ny * z)]);
				else
					fprintf(file, "%d ", grid.field[x + nx * (y + ny * z)]);
			}
		}
	}
}

void GridVTKWriter::end_line()
{
	char str2[8] = "\n";
	fprintf(file, str2);
}

void GridVTKWriter::write_int(int val)
{
	force_big_endian((unsigned char *)&val);
	fwrite(&val, sizeof(int), 1, file);
}

void GridVTKWriter::write_float(float val)
{
	force_big_endian((unsigned char *)&val);
	fwrite(&val, sizeof(float), 1, file);
}

void GridVTKWriter::force_big_endian(unsigned char *bytes)
{
	bool shouldSwap = false;
	int tmp1 = 1;
	unsigned char *tmp2 = (unsigned char *)&tmp1;
	if (*tmp2 != 0)
		shouldSwap = true;

	if (shouldSwap)
	{
		unsigned char tmp = bytes[0];
		bytes[0] = bytes[3];
		bytes[3] = tmp;
		tmp = bytes[1];
		bytes[1] = bytes[2];
		bytes[2] = tmp;
	}
}
