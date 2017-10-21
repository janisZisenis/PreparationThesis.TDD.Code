#ifndef Grid_h
#define Grid_h

#include <Core_EXPORT.h>

#include "global.h"
#include <stdio.h>
#include <sstream>

#include <stl/Vertex.h>
#include <stl/Triangle.h>
#include <stl/BoundingBox.h>
#include <grid/NodeValues.h>
#include <grid/distributions/Distribution.h>


struct Core_EXPORT DoubfloPtr1D {
    doubflo *ptr;
    int size;
};


struct Core_EXPORT Grid{
    char *field;
    int startX, startY, startZ;
    unsigned int nx, ny, nz;
    unsigned int size;
    Distribution d;

    Grid(){};
    Grid(char *field, int startX, int startY, int startZ, int nx, int ny, int nz, Distribution &d)
        : field(field), startX(startX), startY(startY), startZ(startZ), nx(nx), ny(ny), nz(nz), d(d)
    {
        this->size = nx * ny * nz;
    }

    bool isFluid(int index) const{
        return field[index] == FLUID;
    }

    bool isSolid(int index) const{
        return field[index] == SOLID;
    }

    bool isQ(int index) const{
        return field[index] == Q;
    }

     bool isRB(int index) const{
        return field[index] == VELOCITY || field[index] == PRESSURE || field[index] == NOSLIP || field[index] == SOLID;
    }


    void setFieldEntry(const struct Vertex &v, char val)
    {
        this->field[transCoordToIndex(v)] = val;
    }

    char getFieldEntry(const struct Vertex &v)
    {
        return this->field[transCoordToIndex(v)];
    }

    int transCoordToIndex2(const int &x, const int &y, const int &z) const
    {
        return (int)(x + nx * (y + ny * z));
    }

    int transCoordToIndex(const struct Vertex &v) const
    {
        int gridX = (int)v.x - startX;
        int gridY = (int)v.y - startY;
        int gridZ = (int)v.z - startZ;
        if (gridX < 0 || gridY < 0 || gridZ < 0 || gridX >= (int)nx || gridY >= (int)ny || gridZ >= (int)nz)
            return -1;

        return (int)(gridX + nx * (gridY + ny * gridZ));
    }

    void transIndexToCoords(const int index, int &x, int &y, int &z) const
    {
        x = index % nx;
        y = (index / nx) % ny;
        z = ((index / nx) / ny) % nz;
    }

    char* toString(const char* name) const
    {
        std::stringstream ss;
        ss << "\n" << name << " " << nx << " " << ny << " " << nz;
        return strdup(ss.str().c_str());
    }

    void print() const 
    {
        printf("Dimension: (%d, %d, %d), size: %d, offset: (%d, %d, %d)\n", nx, ny, nz, size, startX, startY, startZ);
    }
	
	
void createBoundingBox(doubflo(&alphaAngles)[3], struct Triangle &actualTriangle) 
{
    struct BoundingBox box = BoundingBox(actualTriangle);
    
    //if (DEBUG)
    //printTriangle(actualTriangle);
	//box.print();
	//box.printNumberofNodes();

    int x, y, z;
    struct Vertex actualPoint;
    for (x = box.minX; x <= box.maxX; x++){
        for (y = box.minY; y <= box.maxY; y++){
            for (z = box.minZ; z <= box.maxZ; z++){
                actualPoint = Vertex((doubflo)x, (doubflo)y,(doubflo)z);
                if (this->transCoordToIndex(actualPoint) == -1)
                    continue;
                //printVertexInt(actualPoint);
				if (this->getFieldEntry(actualPoint) != 1 && this->getFieldEntry(actualPoint) != 6)
					this->setFieldEntry(actualPoint, 2);
                analyzePointInBoundingBox_PerpendicularDistance(actualPoint, actualTriangle, alphaAngles);
            }
        }
    }
}
/*---------------------------------------------------------------------------------*/

void analyzePointInBoundingBox_PerpendicularDistance(struct Vertex &actualPoint, struct Triangle &actualTriangle, doubflo(&alphaAngles)[3])
{
    doubflo s = actualTriangle.getPerpedicularDistanceFrom(actualPoint);
    doubflo delta = abs(actualTriangle.normal.x) + abs(actualTriangle.normal.y) + abs(actualTriangle.normal.z);

    //printf("s: %2.4f, d: %2.4f \n", s, delta);
    if ((s + EPSILON) >= 0 && s <= (delta + EPSILON)){
        analyzePointInBoundingBox_PointUnderTriangle(actualPoint, actualTriangle, alphaAngles);
    }
    if ((s + EPSILON) < 0 && -s <= (delta + EPSILON)){
        this->setFieldEntry(actualPoint, Q);
        calculateQs(actualPoint, actualTriangle);
    }
}
/*---------------------------------------------------------------------------------*/

void analyzePointInBoundingBox_PointUnderTriangle(struct Vertex &actualPoint, struct Triangle &actualTriangle, doubflo(&alphaAngles)[3])
{
    doubflo g1, g2, g3;
    actualTriangle.getDistanceToMeasureIfPointIsWithin(g1, g2, g3, actualPoint);


    if (g1 <= EPSILON && g2 <= EPSILON && g3 <= EPSILON){
        analyzePointInBoundingBox_CompareAngles(actualPoint, actualTriangle, alphaAngles);
    }

}
/*---------------------------------------------------------------------------------*/

void analyzePointInBoundingBox_CompareAngles(struct Vertex &actualPoint, struct Triangle &actualTriangle, doubflo(&alphaAngles)[3])
{
    doubflo betaAngles[3];
    actualTriangle.getAnglesBetweenVectorAndClosestPointOnEdge(actualPoint, betaAngles);

    if (isBetaSmallerThanAlpha(alphaAngles, betaAngles)) {
        this->setFieldEntry(actualPoint, SOLID);
    }

}
/*---------------------------------------------------------------------------------*/

int isBetaSmallerThanAlpha(doubflo(&alphaAngles)[3], doubflo(&betaAngles)[3]) {

    //for (int i = 0; i < 3; i++)
    //    printf("alpha/beta: %2.4f, %2.4f\n", alphaAngles[i], betaAngles[i]);
    doubflo eps = EPSILON*100;
    if (betaAngles[0] <= alphaAngles[0] + eps && betaAngles[1] <= alphaAngles[1] + eps && betaAngles[2] <= alphaAngles[2] + eps)
        return 1; 
    
    return 0;
    //return 1;//just for CPU Q ONE TRIANGLE TEST
}
/*---------------------------------------------------------------------------------*/

void calculateQs(struct Vertex &actualPoint, struct Triangle &actualTriangle)
{
    struct Vertex pointOnTriangle, dir;
    //struct VertexInteger solid_node;
    doubflo qVal;
    int err, index;

    for (int i = this->d.dir_start; i <= this->d.dir_end; i++) {
        #if defined(__CUDA_ARCH__)
            dir = Vertex(DIRECTIONS[i][0], DIRECTIONS[i][1], DIRECTIONS[i][2]);
        #else
        dir = Vertex((doubflo)this->d.dirs[i * DIMENSION + 0], (doubflo)this->d.dirs[i * DIMENSION + 1], (doubflo)this->d.dirs[i * DIMENSION + 2]);
        #endif
        
        err = actualTriangle.getTriangleIntersection(actualPoint, dir, pointOnTriangle, qVal);

        if (err != 0 && qVal <= 1.0f) {
            //solid_node = VertexInteger(actualPoint.x + dir.x, actualPoint.y + dir.y, actualPoint.z + dir.z);
            index = i*this->size + this->transCoordToIndex(actualPoint);


            this->d.f[index] = qVal;
            //printf("Q%d %d: %2.8f \n", i, this->transCoordToIndex(actualPoint), grid.d.f[index]);
        }
    }
}
	
};


#endif
