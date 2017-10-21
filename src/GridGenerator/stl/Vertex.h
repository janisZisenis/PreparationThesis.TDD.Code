#ifndef Vertex_h
#define Vertex_h

#include "global.h"

#include <stdio.h>
#include "GridGenerator/utilities/CudaMath.h"

#include "Core_EXPORT.h"

struct Core_EXPORT Vertex {

    doubflo x, y, z;

    Vertex(doubflo x, doubflo y, doubflo z) : x(x), y(y), z(z){}
    Vertex(){}

     doubflo getEuclideanDistanceTo(Vertex &w) const{
        return CudaMath::sqrt((x - w.x)*(x - w.x) + (y - w.y)*(y - w.y) + (z - w.z)*(z - w.z));
    }

    Vertex operator-(const Vertex &v) const{
        return Vertex(x - v.x, y - v.y, z - v.z);
    }

    Vertex operator+(const Vertex &v) const{
        return Vertex(this->x + v.x, this->y + v.y, this->z + v.z);
    }

    Vertex operator*(const doubflo value) const{
        return Vertex(value * this->x, value * this->y, value * this->z);
    }

    doubflo operator*(const Vertex &w) const{
        return x*w.x + y*w.y + z*w.z;
    }

    struct Vertex crossProduct(const struct Vertex &w) const{
        doubflo a = y*w.z - z*w.y;
        doubflo b = z*w.x - x*w.z;
        doubflo c = x*w.y - y*w.x;
        return Vertex(a, b, c);
    }

    doubflo length() const {
        return std::sqrt(x * x + y * y + z * z);
    }

    void normalize(){
        doubflo len = length();

        if (len > EPSILON)
        {
            doubflo invLen = 1.0f / len;
            x *= invLen;
            y *= invLen;
            z *= invLen;
        }
    }

    doubflo getMagnitude() const{
        doubflo temp = x*x + y*y + z*z;
        return CudaMath::sqrt(temp);
    }

    int isEqual(const struct Vertex &w) const{
        return CudaMath::equal(x, w.x) && CudaMath::equal(y, w.y) && CudaMath::equal(z, w.z);
    }

    doubflo getInnerAngle(const struct Vertex &w) const{
        if (isEqual(w))
            return 0.0;
        if (this->getMagnitude() == 0 || w.getMagnitude() == 0)
            return 0.0;

        doubflo mag = this->getMagnitude() * w.getMagnitude();
        doubflo skal = *this * w;
        if (mag - fabs(skal) < 0.0001)
            return 0.0f;
        return  CudaMath::acos(skal / mag) * 180.0f / CudaMath::acos(-1.0f); // acos(-1.0f) = PI 
    }

    void print() const{
        printf("(%2.8f,%2.8f,%2.8f)\n", x, y, z);
    }

};

	inline Vertex operator*(doubflo s, const Vertex& v)
{
    return Vertex(s * v.x, s * v.y, s * v.z);
}


#endif
