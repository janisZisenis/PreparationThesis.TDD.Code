#include "Transformator.h"
#include "Exception.h"

#include <stl/Vertex.h>
#include <stl/BoundingBox.h>

Transformator::Transformator()
{
    this->delta = 1.0;
    this->translate.x = 0;
    this->translate.y = 0;
    this->translate.z = 0;
}

Transformator::Transformator(doubflo delta, struct Vertex translate)
{
    this->verifyDelta(delta);
    this->delta = delta;
    this->translate = translate;
}

void Transformator::verifyDelta(doubflo delta) const
{
    if (delta <= 0.0)
        throw invalidDelta();
}

Transformator::~Transformator()
{

}



void Transformator::transformWorldToView(struct Vertex &value) const
{
    //translate
    value.x = value.x + translate.x;
    value.y = value.y + translate.y;
    value.z = value.z + translate.z;

    //scale
    value.x = value.x * (1.0f / this->delta);
    value.y = value.y * (1.0f / this->delta);
    value.z = value.z * (1.0f / this->delta);
}

void Transformator::transformViewToWorld(struct Vertex &value) const
{
    //scale
    value.x = value.x * (this->delta);
    value.y = value.y * (this->delta);
    value.z = value.z * (this->delta);

    //translate
    value.x = value.x - translate.x;
    value.y = value.y - translate.y;
    value.z = value.z - translate.z;
}

void Transformator::transformViewToWorld(struct BoundingBox &box) const
{
    //scale
    box.minX *= this->delta;
    box.minY *= this->delta;
    box.minZ *= this->delta;

    box.maxX *= this->delta;
    box.maxY *= this->delta;
    box.maxZ *= this->delta;

    //translate
    box.minX -= this->translate.x;
    box.minY -= this->translate.y;
    box.minZ -= this->translate.z;
                
    box.maxX -= this->translate.x;
    box.maxY -= this->translate.y;
    box.maxZ -= this->translate.z;
}

doubflo Transformator::getDelta() const
{
    return this->delta;
}

struct Vertex Transformator::getTranslate() const
{
    return this->translate;
}
