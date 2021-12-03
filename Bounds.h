#pragma once
#include "Ogre.h"

using namespace Ogre;
using namespace std;
class Bounds
{
public:
	Bounds();
	~Bounds();
	Vector3 getPosition();
	Vector3 getScale();
	ManualObject* CreateShape(ManualObject* obj);
	void setPosition(Vector3 pos);


private:

	Vector3 position, scale;
};

