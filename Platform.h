#pragma once
#include "Ogre.h"
using namespace Ogre;
using namespace std;
class Platform
{

public:
	Platform();
	~Platform();
	Vector3 getPosition();
	Vector3 getScale();
	ManualObject* CreateShape(ManualObject* obj, string materialName);
	void setPosition(Vector3 pos);
	

private:
	
	Vector3 position,scale;
	

};

