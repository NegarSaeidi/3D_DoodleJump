#include "CollisionManager.h"
CollisionManager* CollisionManager::s_pInstance = nullptr;
bool CollisionManager::checkCollision(SceneNode* node1, SceneNode* node2)
{
	Ogre::AxisAlignedBox FirstNodeBox = node1->_getWorldAABB();
	Ogre::AxisAlignedBox SecondNodeBox = node2->_getWorldAABB();

	if (FirstNodeBox.intersects(SecondNodeBox))
		return true;
	else
		return false;

}

CollisionManager::CollisionManager()
{
}

CollisionManager::~CollisionManager()
{
}


