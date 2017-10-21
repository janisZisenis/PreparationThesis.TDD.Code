#ifndef Transformator_h
#define Transformator_h

#include "Core_Export.h"
#include "global.h"

#include <stl/Vertex.h>

struct Vertex;

class Core_EXPORT Transformator
{
public:
	Transformator();
    Transformator(doubflo delta, struct Vertex translate);
	~Transformator();
    void transformWorldToView(struct Vertex &value) const;
    void transformViewToWorld(struct Vertex &value) const;
    void transformViewToWorld(struct BoundingBox &box) const;

    doubflo getDelta() const;
    struct Vertex getTranslate() const;
private:
    doubflo delta;
    struct Vertex translate;
    void verifyDelta(doubflo delta) const;
};


#endif
