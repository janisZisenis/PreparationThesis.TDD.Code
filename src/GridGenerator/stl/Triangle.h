#ifndef Triangle_h
#define Triangle_h

#include "global.h"
#include "Vertex.h"

#include "Core_EXPORT.h"



struct Core_EXPORT Triangle{
    struct Vertex v1, v2, v3, normal;
    
    Triangle(struct Vertex v1, struct Vertex v2, struct Vertex v3, struct Vertex normal) : v1(v1), v2(v2), v3(v3), normal(normal) {}
    Triangle(struct Vertex v1, struct Vertex v2, struct Vertex v3) : v1(v1), v2(v2), v3(v3) { calcNormal(); }
    Triangle(){}

    void set(const struct Vertex &v1, const struct Vertex &v2, const struct Vertex &v3){
        this->v1 = v1;
        this->v2 = v2;
        this->v3 = v3;
        this->calcNormal();
    }

    void calcNormal(){
        Vertex edge1 = v2 - v1;
        Vertex edge2 = v3 - v1;
        normal = edge1.crossProduct(edge2);
        normal.normalize();
    }

    void getAnglesBetweenVectorAndClosestPointOnEdge(const struct Vertex &P, doubflo(&betaAngles)[3]) const
    {
        struct Vertex Pci[3];
        getClosestPointsOnEdges(Pci, P);
        struct Vertex Pb = getPerpedicularPointFrom(P);

        struct Vertex q[3];
        struct Vertex r[3];

        for (int i = 0; i < 3; i++){
            q[i] = P - Pci[i];
            r[i] = Pb - Pci[i];
            betaAngles[i] = q[i].getInnerAngle(r[i]);
        }
    }

    void getClosestPointsOnEdges(struct Vertex arr[], const struct Vertex &P) const
    {
        struct Vertex Pc1, Pc2, Pc3;
        struct Vertex v4 = P - v1;
        struct Vertex v5 = P - v2;
        struct Vertex v6 = P - v3;

        struct Vertex d1 = v2 - v1;
        struct Vertex d2 = v3 - v2;
        struct Vertex d3 = v1 - v3;

        doubflo temp = (v4 * d1) / (d1 * d1);
        struct Vertex tempV = d1 * temp;
        Pc1 = v1 + tempV;

        temp = (v5 * d2) / (d2 * d2);
        tempV = d2 * temp;
        Pc2 = v2 + tempV;

        temp = (v6 * d3) / (d3 * d3);
        tempV = d3 * temp;
        Pc3 = v3 + tempV;

        arr[0] = Pc1;
        arr[1] = Pc2;
        arr[2] = Pc3;
    }

    doubflo getPerpedicularDistanceFrom(const struct Vertex &P) const
    {
        struct Vertex v = P - v1;
        return -1.0f * v * normal;
    }

    struct Vertex getPerpedicularPointFrom(const struct Vertex &P) const
    {
        return P + normal * getPerpedicularDistanceFrom(P);
    }

    void getDistanceToMeasureIfPointIsWithin(doubflo &d1, doubflo &d2, doubflo &d3, const struct Vertex &P) const
    {
        struct Vertex Pb = getPerpedicularPointFrom(P);

        struct Vertex w1 = Pb - v1;
        struct Vertex w2 = Pb - v2;
        struct Vertex w3 = Pb - v3;

        struct Vertex t1 = w1.crossProduct(v2 - v1);
        struct Vertex t2 = w2.crossProduct(v3 - v2);
        struct Vertex t3 = w3.crossProduct(v1 - v3);

        d1 = t1 * normal;
        d2 = t2 * normal;
        d3 = t3 * normal;
    }


    Vertex getCenterOfMass() const {
        return (v1 + v2 + v3) * (1.0f / 3.0f);
    }

    enum NormalsPointingToEachOther{ INPOINTING, OUTPOINTING, PARALLEL };

    doubflo getHalfAngleBetweenToAdjacentTriangle(const struct Triangle &t2) const
    {
        if (isEqual(t2)) return 0.0f;

        doubflo alpha = normal.getInnerAngle(t2.normal);
        if (alpha == 180.0f)
            return alpha / 2.0f;

        enum NormalsPointingToEachOther X = howNormalVectorsPointToEachOther(t2);
        if (X == INPOINTING){
            //printf("Inpointing\n");
            return (180.0f + alpha) / 2.0f;
        }
        else if (X == OUTPOINTING) {
            //printf("Outpointing\n");
            return (180.0f - alpha) / 2.0f;
        }
        return 0.0f;
    }

    int isEqual(const struct Triangle &t2) const
    {
        return getNumberOfCommonEdge(t2) == 3;
    }

    NormalsPointingToEachOther howNormalVectorsPointToEachOther(const struct  Triangle &t2) const
    {
        struct Vertex s1 = getCenterOfMass();
        struct Vertex s2 = t2.getCenterOfMass();

        struct Vertex s1s2 = s1 - s2;
        doubflo X = s1s2 * t2.normal;
        return X > 0 ? INPOINTING : OUTPOINTING;
    }



    int getCommonEdge(const struct Triangle &t2) const {
        int edgeOneCommon = 0;
        int edgeTwoCommon = 0;
        int edgeThreeCommon = 0;

        if (v1.isEqual(t2.v1))
            edgeOneCommon = 1;
        else if (v1.isEqual(t2.v2))
            edgeOneCommon = 1;
        else if (v1.isEqual(t2.v3))
            edgeOneCommon = 1;

        if (v2.isEqual(t2.v1))
            edgeTwoCommon = 1;
        else if (v2.isEqual(t2.v2))
            edgeTwoCommon = 1;
        else if (v2.isEqual(t2.v3))
            edgeTwoCommon = 1;

        if (v3.isEqual(t2.v1))
            edgeThreeCommon = 1;
        else if (v3.isEqual(t2.v2))
            edgeThreeCommon = 1;
        else if (v3.isEqual(t2.v3))
            edgeThreeCommon = 1;

        if (edgeOneCommon && edgeTwoCommon)
            return 0;
        else if (edgeTwoCommon && edgeThreeCommon)
            return 1;
        else if (edgeThreeCommon && edgeOneCommon)
            return 2;
        else
            return -1;
    }


    int getNumberOfCommonEdge(const struct Triangle &t2) const
    {
        int commonEdge = 0;
        if (v1.isEqual(t2.v1))
            commonEdge++;
        else if (v1.isEqual(t2.v2))
            commonEdge++;
        else if (v1.isEqual(t2.v3))
            commonEdge++;

        if (v2.isEqual(t2.v1))
            commonEdge++;
        else if (v2.isEqual(t2.v2))
            commonEdge++;
        else if (v2.isEqual(t2.v3))
            commonEdge++;

        if (v3.isEqual(t2.v1))
            commonEdge++;
        else if (v3.isEqual(t2.v2))
            commonEdge++;
        else if (v3.isEqual(t2.v3))
            commonEdge++;

        if (commonEdge == 2 || commonEdge == 3) return commonEdge;
        return 0;
    }


    int getTriangleIntersection(const struct Vertex &P, const struct Vertex &direction, struct Vertex &pointOnTri, doubflo &qVal) {
        struct Vertex edge1, edge2, tvec, pvec, qvec, tuv;
        float det, inv_det;

        edge1 = v2 - v1;
        edge2 = v3 - v1;

        pvec = direction.crossProduct(edge2);
        det = edge1 * pvec;

        if (det < EPSILON)
            return 0;

        inv_det = 1 / det;

        tvec = P - v1;
        tuv.y = (tvec * pvec) * inv_det;

        if (tuv.y < 0.0 || tuv.y > 1.0)
            return 0;

        qvec = tvec.crossProduct(edge1);
        tuv.z = (direction * qvec) * inv_det;

        if (tuv.z < 0.0 || (tuv.y + tuv.z) > 1.0)
            return 0;

        tuv.x = (edge2 * qvec) * inv_det;

        pointOnTri.x = (1 - tuv.y - tuv.z) * v1.x + tuv.y * v2.x + tuv.z * v3.x;
        pointOnTri.y = (1 - tuv.y - tuv.z) * v1.y + tuv.y * v2.y + tuv.z * v3.y;
        pointOnTri.z = (1 - tuv.y - tuv.z) * v1.z + tuv.y * v2.z + tuv.z * v3.z;
  
        qVal = tuv.x;

        return 1;
    }

    void print() const{
        printf("v1: ");
        v1.print();
        printf("v2: ");
        v2.print();
        printf("v3: ");
        v3.print();
        printf("normal: ");
        normal.print();
    }

};



#endif
