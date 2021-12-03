#pragma once
#include "Ogre.h"

using namespace Ogre;
class CollisionManager
{
public:
	static CollisionManager* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new CollisionManager();
			return s_pInstance;
		}
		return s_pInstance;
	}

	bool checkCollision(SceneNode* node1, SceneNode* node2);

private:
	static CollisionManager* s_pInstance;



	CollisionManager();
	~CollisionManager();

};
