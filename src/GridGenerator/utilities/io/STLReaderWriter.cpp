#define _CRT_SECURE_NO_DEPRECATE
#include "STLReaderWriter.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include "GridGenerator/utilities/Transformator.h"
#include <stl/Vertex.h>
#include <stl/Triangle.h>
#include <stl/BoundingBox.h>
#include <grid/Partition.h>
#include <utilities/Logger.h>
#include <string.h>

void STLReaderWriter::writeTrianglesToSTL(std::vector<struct Triangle> vec, std::string name, Transformator trans) 
{
    Logger::getInstance()->logTerminal("Write " + SSTR(vec.size()) + " Triangles to STL : " + name + "\n");
    FILE *file = fopen(name.c_str(), "w");
    if (!file)
        Logger::getInstance()->logTerminal(" Output file not open - exit function\n");
    else {
        fprintf(file, "solid ascii\n");
        for (size_t i = 0; i < vec.size(); i++) {
            trans.transformViewToWorld(vec[i].v1);
            trans.transformViewToWorld(vec[i].v2);
            trans.transformViewToWorld(vec[i].v3);

            fprintf(file, "facet normal %f %f %f\n", vec[i].normal.x, vec[i].normal.y, vec[i].normal.z);
            fprintf(file, "outer loop\n");

            fprintf(file, "vertex %f %f %f\n", vec[i].v1.x, vec[i].v1.y, vec[i].v1.z);
            fprintf(file, "vertex %f %f %f\n", vec[i].v2.x, vec[i].v2.y, vec[i].v2.z);
            fprintf(file, "vertex %f %f %f\n", vec[i].v3.x, vec[i].v3.y, vec[i].v3.z);

            fprintf(file, "endloop\n");
            fprintf(file, "endfacet\n");
        }
        fprintf(file, "endsolid\n");
        fclose(file);
        Logger::getInstance()->logTerminal("Output file closed\n");
    }
}

void STLReaderWriter::writeTrianglesToSTL(struct Triangle *triangles, int &size, std::string name, Transformator trans)
{
    Logger::getInstance()->logTerminal("Write " + SSTR(size) + " Triangles to STL : " + name + "\n");
    FILE *file = fopen(name.c_str(), "w");
    if (!file)
        Logger::getInstance()->logTerminal(" Output file not open - exit function\n");
    else {
        fprintf(file, "solid ascii\n");
        for (size_t i = 0; i < size; i++) {
            trans.transformViewToWorld(triangles[i].v1);
            trans.transformViewToWorld(triangles[i].v2);
            trans.transformViewToWorld(triangles[i].v3);

            fprintf(file, "facet normal %f %f %f\n", triangles[i].normal.x, triangles[i].normal.y, triangles[i].normal.z);
            fprintf(file, "outer loop\n");

            fprintf(file, "vertex %f %f %f\n", triangles[i].v1.x, triangles[i].v1.y, triangles[i].v1.z);
            fprintf(file, "vertex %f %f %f\n", triangles[i].v2.x, triangles[i].v2.y, triangles[i].v2.z);
            fprintf(file, "vertex %f %f %f\n", triangles[i].v3.x, triangles[i].v3.y, triangles[i].v3.z);

            fprintf(file, "endloop\n");
            fprintf(file, "endfacet\n");
        }
        fprintf(file, "endsolid\n");
        fclose(file);
        Logger::getInstance()->logTerminal("Output file closed\n");
    }
}


void STLReaderWriter::writeBinarySTL(std::vector<struct Triangle> vec, std::string name, Transformator trans)
{
    char header_info[80] = "GridGeneration-File iRMB";

    Logger::getInstance()->logTerminal("start writing binary STL file: " + name + "\n");

    unsigned long nTriLong = vec.size();

    std::ofstream myfile;

    myfile.open(name.c_str(), std::ios::out | std::ios::binary);
    myfile.write(header_info, sizeof(header_info));
    myfile.write((char*)&nTriLong, 4);
    char attribute[2] = "0";

    for (std::vector<struct Triangle>::iterator it = vec.begin(); it != vec.end(); it++){
        //normal vector coordinates

        myfile.write((char*)&it->normal.x, 4);
        myfile.write((char*)&it->normal.y, 4);
        myfile.write((char*)&it->normal.z, 4);

        //p1 coordinates
        myfile.write((char*)&it->v1.x, 4);
        myfile.write((char*)&it->v1.y, 4);
        myfile.write((char*)&it->v1.z, 4);

        //p2 coordinates
        myfile.write((char*)&it->v2.x, 4);
        myfile.write((char*)&it->v2.y, 4);
        myfile.write((char*)&it->v2.z, 4);

        //p3 coordinates
        myfile.write((char*)&it->v3.x, 4);
        myfile.write((char*)&it->v3.y, 4);
        myfile.write((char*)&it->v3.z, 4);

        myfile.write(attribute, 2);
    }

    myfile.close();
    Logger::getInstance()->logTerminal("Complete writing binary STL file.\n");
}

std::vector<struct Triangle> STLReaderWriter::readSTL(std::string name, Transformator trans)
{
    std::ifstream file(name.c_str());
    if (file.is_open()) {
        std::string line;
        std::getline(file, line);
        line[strcspn(line.c_str(), "\r\n")] = 0;
        if (strcmp(line.c_str(), "solid ascii") == 0) {
            file.close();
            Logger::getInstance()->logTerminal("start reading ascii STL file: " + name + "\n");
            return readASCIISTL(name, trans);
        }
        else {
            file.close();
            Logger::getInstance()->logTerminal("start reading binary STL file: " + name + "\n");
            return readBinarySTL(name, trans);
        }
    }
    else {
        Logger::getInstance()->logTerminal("can't open STL-file" + name + "\n");
        exit(1);
    }
}

std::vector<struct Triangle> STLReaderWriter::readASCIISTL(std::string name, Transformator trans) 
{
    int lines = countLinesInFile(name);
    int nTriangles = (lines) / 7; // seven lines per triangle

    Logger::getInstance()->logTerminal("Number of Triangles: " + SSTR(nTriangles) + "\n");
    std::vector<struct Triangle> triangles;

    std::string line;
    std::ifstream file;
    file.open(name.c_str(), std::ifstream::in);
    std::getline(file, line); // solid ascii

    for (int t = 0; t < nTriangles; t++) {
        struct Vertex normal = parseLineToCoordinates(file, "%*s %*s %f %f %f");
        getline(file, line); // outer loop
        struct Vertex p1 = parseLineToCoordinates(file, "%*s %f %f %f");
        struct Vertex p2 = parseLineToCoordinates(file, "%*s %f %f %f");
        struct Vertex p3 = parseLineToCoordinates(file, "%*s %f %f %f");
        getline(file, line); //endloop
        getline(file, line); //endfacet
        trans.transformWorldToView(p1);
        trans.transformWorldToView(p2);
        trans.transformWorldToView(p3);
        Triangle tri = Triangle(p1, p2, p3, normal);
        tri.calcNormal();
        triangles.push_back(tri);
    }
    file.close();
    return triangles;
}

std::vector<struct Triangle> STLReaderWriter::readBinarySTL(std::string name, Transformator trans)
{
    FILE *file;
    std::string mode = "rb";
    file = fopen(name.c_str(), mode.c_str());

    char header_info[80] = "";
    char nTri[4];
    unsigned long nTriLong;

    fread(header_info, sizeof(char), 80, file);


    fread(nTri, sizeof(char), 4, file);
    nTriLong = *((unsigned long*)nTri);
    Logger::getInstance()->logTerminal("Number of Triangles: " + SSTR(nTriLong) + "\n");
    std::vector<struct Triangle> triangles;

    char facet[50];
    for (unsigned int i = 0; i < nTriLong; i++){
        fread(facet, sizeof(char), 50, file);

        struct Vertex normal = getVertexFromChar(facet);

        struct Vertex p1 = getVertexFromChar(facet + 12);
        struct Vertex p2 = getVertexFromChar(facet + 24);
        struct Vertex p3 = getVertexFromChar(facet + 36);

        trans.transformWorldToView(p1);
        trans.transformWorldToView(p2);
        trans.transformWorldToView(p3);

        triangles.push_back(Triangle(p1, p2, p3, normal));
    }
    return triangles;
}

std::vector<struct Triangle> STLReaderWriter::readSTL(BoundingBox &box, std::string name, Transformator trans)
{
    std::ifstream file(name.c_str());
    if (file.is_open()) {
        std::string line;
        std::getline(file, line);
        line[strcspn(line.c_str(), "\r\n")] = 0;
        if (strcmp(line.c_str(), "solid ascii") == 0) {
            file.close();
            Logger::getInstance()->logTerminal("start reading ascii STL file: " + name + "\n");
            return readASCIISTL(box, name, trans);
        }
        else {
            file.close();
            Logger::getInstance()->logTerminal("start reading binary STL file: " + name + "\n");
            std::vector<struct Triangle> triangles = readBinarySTL(box, name, trans);
            return triangles;
        }
    }
    else {
        Logger::getInstance()->logTerminal("can't open STL-file" + name + "\n");
        exit(1);
    }
}

std::vector<struct Triangle> STLReaderWriter::readASCIISTL(BoundingBox &box, std::string name, Transformator trans) 
{
    int lines = countLinesInFile(name);
    int nTriangles = (lines) / 7; // seven lines per triangle
    std::cout << "Number of Triangles: " << nTriangles << std::endl;
    std::vector<struct Triangle> triangles;

    std::string line;
    std::ifstream file;
    file.open(name.c_str(), std::ifstream::in);
    std::getline(file, line); // solid ascii

    for (int i= 0; i < nTriangles; i++) {
        struct Vertex normal = parseLineToCoordinates(file, "%*s %*s %f %f %f");
        getline(file, line); // outer loop
        struct Vertex p1 = parseLineToCoordinates(file, "%*s %f %f %f");
        struct Vertex p2 = parseLineToCoordinates(file, "%*s %f %f %f");
        struct Vertex p3 = parseLineToCoordinates(file, "%*s %f %f %f");
        getline(file, line); //endloop
        getline(file, line); //endfacet
        trans.transformWorldToView(p1);
        trans.transformWorldToView(p2);
        trans.transformWorldToView(p3);

        struct Triangle t(p1, p2, p3, normal);
        t.calcNormal();
        if (box.isInside(t) || box.intersect(t))
            triangles.push_back(t);
    }
    file.close();
    return triangles;
}


std::vector<struct Triangle> STLReaderWriter::readBinarySTL(BoundingBox &box, std::string name, Transformator trans)
{
    FILE *file;
    std::string mode = "rb";
    file = fopen(name.c_str(), mode.c_str());

    char header_info[80] = "";
    char nTri[4];
    unsigned long nTriLong;
  
    fread(header_info, sizeof(char), 80, file);


    fread(nTri, sizeof(char), 4, file);
    nTriLong = *((unsigned long*)nTri);

    Logger::getInstance()->logTerminal("Number of Triangles complete geometry: " + SSTR(nTriLong) + "\n");
    std::vector<struct Triangle> triangles;

    char facet[50];
    for (unsigned int i = 0; i < nTriLong; i++){
        fread(facet, sizeof(char), 50, file);

        struct Vertex normal = getVertexFromChar(facet);

        struct Vertex p1 = getVertexFromChar(facet + 12);
        struct Vertex p2 = getVertexFromChar(facet + 24);
        struct Vertex p3 = getVertexFromChar(facet + 36);

        trans.transformWorldToView(p1);
        trans.transformWorldToView(p2);
        trans.transformWorldToView(p3);

        struct Triangle t(p1, p2, p3, normal);
        if (box.isInside(t) || box.intersect(t))
            triangles.push_back(t);
    }
    Logger::getInstance()->logTerminal("Number of Triangles in process: " + SSTR(triangles.size()) + "\n");
    Logger::getInstance()->logTerminal("Complete reading STL file. \n");

    return triangles;
}


/*#################################################################################*/
/*---------------------------------private methods---------------------------------*/
/*---------------------------------------------------------------------------------*/
struct Vertex STLReaderWriter::parseLineToCoordinates(std::ifstream& file, std::string format)
{
    std::string line;
    getline(file, line);
    const char* buffer = line.c_str();
    doubflo x, y, z;
    sscanf(buffer, format.c_str(), &x, &y, &z);
    return Vertex(x, y, z);
}

int STLReaderWriter::countLinesInFile(std::string name)
{
    std::ifstream file;
    file.open(name.c_str(), std::ifstream::in);
    int nTriLong = (int)std::count(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>(), '\n');
    file.close();
    return nTriLong;
}

struct Vertex STLReaderWriter::getVertexFromChar(const char* facet)
{
    char f1[4] = { facet[0],
        facet[1], facet[2], facet[3] };

    char f2[4] = { facet[4],
        facet[5], facet[6], facet[7] };

    char f3[4] = { facet[8],
        facet[9], facet[10], facet[11] };

    float xx = *((float*)f1);
    float yy = *((float*)f2);
    float zz = *((float*)f3);

    struct Vertex v;
    v.x = (doubflo)(xx);
    v.y = (doubflo)(yy);
    v.z = (doubflo)(zz);
    return v;
}
