#ifndef BoundingBox_h
#define BoundingBox_h

#include <vector>


#include "Triangle.h"
#include "Vertex.h"

#include "Core_EXPORT.h"


struct Core_EXPORT BoundingBoxExact {
    doubflo minX;
    doubflo maxX;
    doubflo minY; 
    doubflo maxY;
    doubflo minZ;
    doubflo maxZ;
    BoundingBoxExact(doubflo minX, doubflo maxX, doubflo minY, doubflo maxY, doubflo minZ, doubflo maxZ) : minX(minX), maxX(maxX), minY(minY), maxY(maxY), minZ(minZ), maxZ(maxZ) {}
    BoundingBoxExact(){
        minX = 0.0f;
        maxX = 0.0f;
        minY = 0.0f;
        maxY = 0.0f;
        minZ = 0.0f;
        maxZ = 0.0f;
    }

    BoundingBoxExact(const struct Triangle &t) {
        calculateMinMaxFrom(t.v1.x, t.v2.x, t.v3.x, minX, maxX);
        calculateMinMaxFrom(t.v1.y, t.v2.y, t.v3.y, minY, maxY);
        calculateMinMaxFrom(t.v1.z, t.v2.z, t.v3.z, minZ, maxZ);
    }

    void calculateMinMaxFrom(const doubflo value1, const doubflo value2, const doubflo value3, doubflo &min, doubflo &max)
    {
        min = value1;
        max = value2;
        if (value1 > value2){
            min = value2;
            max = value1;
        }
        if (min > value3){
            min = value3;
        }
        if (max < value3){
            max = value3;
        }
    }
};

struct Core_EXPORT BoundingBox {
    int minX;
    int maxX;
    int minY;
    int maxY;
    int minZ;
    int maxZ;
    BoundingBox(int minX, int maxX, int minY, int maxY, int minZ, int maxZ) : minX(minX), maxX(maxX), minY(minY), maxY(maxY), minZ(minZ), maxZ(maxZ) {}
    BoundingBox(){
        minX = 0;
        maxX = 0;
        minY = 0;
        maxY = 0;
        minZ = 0;
        maxZ = 0;
    }

     BoundingBox(const struct Triangle &t) {
        calculateMinMaxFrom(t.v1.x, t.v2.x, t.v3.x, minX, maxX);
        calculateMinMaxFrom(t.v1.y, t.v2.y, t.v3.y, minY, maxY);
        calculateMinMaxFrom(t.v1.z, t.v2.z, t.v3.z, minZ, maxZ);
    }

     void calculateMinMaxFrom(const doubflo value1, const doubflo value2, const doubflo value3, int &min, int &max)
    {
        min = (int)ceil(value1 - 1.0);
        max = (int)floor(value2 + 1.0);
        if (value1 > value2){
            min = (int)ceil(value2 - 1.0);;
            max = (int)floor(value1 + 1.0);
        }
        if (min > value3){
            min = (int)ceil(value3 - 1.0);
        }
        if (max < value3){
            max = (int)floor(value3 + 1.0);
        }
    };

    bool isInside(const struct Triangle t) const{
        if (pointIsInside(t.v1) && pointIsInside(t.v2) && pointIsInside(t.v3))
            return true;
        return false;
    }

    bool pointIsInside(const struct Vertex v) const{
        if (v.x < minX || v.x > maxX)
            return false;
        if (v.y < minY || v.y > maxY)
            return false;
        if (v.z < minZ || v.z > maxZ)
            return false;
        return true;
    }

    bool intersect(const struct Triangle t) const{
        if (pointIsInside(t.v1) || pointIsInside(t.v2) || pointIsInside(t.v3))
            return true;

        return false;
    }


    void getPoints(struct Vertex v[8]) const 
    {
        v[0] = Vertex(minX, minY, minZ);
        v[1] = Vertex(maxX, minY, minZ);
        v[2] = Vertex(minX, maxY, minZ);
        v[3] = Vertex(maxX, maxY, minZ);

        v[4] = Vertex(minX, minY, maxZ);
        v[5] = Vertex(maxX, minY, maxZ);
        v[6] = Vertex(minX, maxY, maxZ);
        v[7] = Vertex(maxX, maxY, maxZ);
    }

    bool intersect(const struct BoundingBox box) const
    {
        struct Vertex v[8];
        box.getPoints(v);

        for (int i = 0; i < 8; i++) {
            if (pointIsInside(v[i]))
                return true;
        }

        return false;
    }

    bool isInside(const struct Vertex v) const{
        if (v.x >= minX && v.x <= maxX && v.y >= minY && v.y <= maxY && v.z >= minZ && v.z <= maxZ)
            return true;
        return false;
    }


    std::vector<std::vector<Vertex> > getIntersectionPoints(const BoundingBoxExact b) const {
        std::vector<std::vector<Vertex> > intersectionBox;
        intersectionBox.resize(6);

        int intersects = 0;
        if (b.minX < maxX && b.maxX > maxX) { //maxX is intersect
            intersectionBox[intersects].push_back(Vertex((doubflo)maxX, (doubflo)minY, (doubflo)minZ));
            intersectionBox[intersects].push_back(Vertex((doubflo)maxX, (doubflo)maxY, (doubflo)minZ));
            intersectionBox[intersects].push_back(Vertex((doubflo)maxX, (doubflo)minY, (doubflo)maxZ));
            intersects++;                                              
        }
        if (b.minX < minX && b.maxX > minX) { //minX is intersect
            intersectionBox[intersects].push_back(Vertex((doubflo)minX, (doubflo)minY, (doubflo)minZ));
            intersectionBox[intersects].push_back(Vertex((doubflo)minX, (doubflo)maxY, (doubflo)minZ));
            intersectionBox[intersects].push_back(Vertex((doubflo)minX, (doubflo)minY, (doubflo)maxZ));
            intersects++;
        }
        if (b.minY < minY && b.maxY > minY) { //minY is intersect
            intersectionBox[intersects].push_back(Vertex((doubflo)minX, (doubflo)minY, (doubflo)minZ));
            intersectionBox[intersects].push_back(Vertex((doubflo)maxX, (doubflo)minY, (doubflo)minZ));
            intersectionBox[intersects].push_back(Vertex((doubflo)minX, (doubflo)minY, (doubflo)maxZ));
            intersects++;
        }
        if (b.minY < maxY && b.maxY > maxY) { //maxY is intersect
            intersectionBox[intersects].push_back(Vertex((doubflo)minX, (doubflo)maxY, (doubflo)minZ));
            intersectionBox[intersects].push_back(Vertex((doubflo)maxX, (doubflo)maxY, (doubflo)minZ));
            intersectionBox[intersects].push_back(Vertex((doubflo)minX, (doubflo)maxY, (doubflo)maxZ));
            intersects++;
        }
        if (b.minZ < minZ && b.maxZ > minZ) { //minZ is intersect
            intersectionBox[intersects].push_back(Vertex((doubflo)minX, (doubflo)minY, (doubflo)minZ));
            intersectionBox[intersects].push_back(Vertex((doubflo)maxX, (doubflo)minY, (doubflo)minZ));
            intersectionBox[intersects].push_back(Vertex((doubflo)minX, (doubflo)maxY, (doubflo)minZ));
            intersects++;
        }
        if (b.minZ < maxZ && b.maxZ > maxZ) { //maxZ is intersect
            intersectionBox[intersects].push_back(Vertex((doubflo)minX, (doubflo)minY, (doubflo)maxZ));
            intersectionBox[intersects].push_back(Vertex((doubflo)maxX, (doubflo)minY, (doubflo)maxZ));
            intersectionBox[intersects].push_back(Vertex((doubflo)minX, (doubflo)maxY, (doubflo)maxZ));
            intersects++;
        }

        return intersectionBox;
    }

	void print(){
        printf("min/max - x: %d/ %d, y: %d, %d, z: %d, %d \n", minX, maxX, minY, maxY, minZ, maxZ);
    }

	void printNumberofNodes() {
		int nodes = ((maxX + 1) - minX) * ((maxY + 1) - minY) * ((maxZ + 1) - minZ);
		printf("Nodes in Box: %d\n", nodes);
	}

};



#endif
