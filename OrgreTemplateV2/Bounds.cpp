
#include "..\Bounds.h"

Bounds::Bounds(): position(100, 100, 0), scale(0.1f, 0.1f, 0.1f)
{
}

Bounds::~Bounds()
{
}

Vector3 Bounds::getPosition()
{
    return position;
}

Vector3 Bounds::getScale()
{
    return scale;
}

ManualObject* Bounds::CreateShape(ManualObject* cube)
{
    cube->begin("FlatVertexColour");


    cube->position(0.5, -0.5, 1.0); cube->colour(0, 0, 0); 
    cube->position(-0.5, -0.5, 0.0); cube->colour(0, 0, 0);
    cube->position(0.5, -0.5, 0.0); cube->colour(0, 0, 0);
    cube->position(-0.5, -0.5, 1.0); cube->colour(0, 0, 0); 
    cube->position(0.5, 0.5, 1.0); cube->colour(0, 0, 0); 
    cube->position(-0.5, -0.5, 1.0); cube->colour(0, 0, 0); 
    cube->position(0.5, -0.5, 1.0); cube->colour(0, 0, 0); 
    cube->position(-0.5, 0.5, 1.0); cube->colour(0, 0, 0); 
    cube->position(-0.5, 0.5, 0.0); cube->colour(0, 0, 0); 
    cube->position(-0.5, -0.5, 0.0); cube->colour(0, 0, 0); 
    cube->position(-0.5, -0.5, 1.0); cube->colour(0, 0, 0); 
    cube->position(0.5, -0.5, 0.0); cube->colour(0, 0, 0); 
    cube->position(0.5, 0.5, 0.0); cube->colour(0, 0, 0);
    cube->position(0.5, -0.5, 1.0); cube->colour(0, 0, 0);
    cube->position(0.5, -0.5, 0.0); cube->colour(0, 0, 0); 
    cube->position(-0.5, -0.5, 0.0); cube->colour(0, 0, 0); 
    cube->position(-0.5, 0.5, 1.0); cube->colour(0, 0, 0); 
    cube->position(0.5, 0.5, 0.0); cube->colour(0, 0, 0); 
    cube->position(-0.5, 0.5, 0.0); cube->colour(0, 0, 0);
    cube->position(0.5, 0.5, 1.0); cube->colour(0, 0, 0);

    cube->triangle(0, 1, 2);		cube->triangle(3, 1, 0);
    cube->triangle(4, 5, 6);		cube->triangle(4, 7, 5);
    cube->triangle(8, 9, 10);		cube->triangle(10, 7, 8);
    cube->triangle(4, 11, 12);	cube->triangle(4, 13, 11);
    cube->triangle(14, 8, 12);	cube->triangle(14, 15, 8);
    cube->triangle(16, 17, 18);	cube->triangle(16, 19, 17);
    cube->end();

    cube->convertToMesh("bounds");


    return cube;
}

void Bounds::setPosition(Vector3 pos)
{
    position = pos;
}
