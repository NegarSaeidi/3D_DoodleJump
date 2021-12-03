#pragma once

#include "Ogre.h"
#include <stack>
using namespace Ogre;
using namespace std;
class Doodle
{
public:
 
	bool isFalling;


	Doodle();
	~Doodle();
	Vector3 getScale();
	void Move(Ogre::SceneNode* sn,Ogre::Real evt,Vector3 dir, Ogre::SceneNode* cam);
	void checkBound(Ogre::SceneNode* sn, Ogre::SceneNode* left, Ogre::SceneNode* right, Ogre::SceneNode* bottom);
	void onPlatform(Ogre::SceneNode* sn, stack<Ogre::SceneNode*> platforms);
	void MoveCamera(Ogre::SceneNode* sn, Ogre::Real evt);
	bool hasCameraMoved();
	void setCameraHasMoved(bool b);

private:

	float speed, gravity,jumpSpeed,doubleJump,tempSpeed;
	Vector3 position, scale,velocity;
	bool bottomColliding, leftColliding, rightColliding,jumpOnPlatform,isOnPlatform,cameraMoved;


};