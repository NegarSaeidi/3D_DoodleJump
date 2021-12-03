
#include "Ogre.h"
#include "OgreApplicationContext.h"
#include "OgreInput.h"
#include "OgreRTShaderSystem.h"
#include "Platform.h"
#include "Doodle.h"
#include "Bounds.h"
#include "SoundManager.h"
#include <stack>
#include "OgreTrays.h"
#include <iostream>

using namespace Ogre;
using namespace OgreBites;
#pragma once
class Game
	: public ApplicationContext
	, public InputListener
{
private:
	OgreBites::TrayListener myTrayListener;


	OgreBites::Label* mScoreLabel;
	OgreBites::Label* mScore;

	OgreBites::Label* mTpuLabel;
	OgreBites::Label* mTpu;

	OgreBites::Label* mLivesLabel;
	OgreBites::Label* mLives;
	SceneNode* SinbadNode;
	SceneNode* camNode;
	SceneManager* scnMgr;
	Camera* cam;
	Root* root;
	Doodle* player;
	Platform* DoodlePlatform1, * DoodlePlatform2, * DoodlePlatform3, * DoodlePlatform4, * DoodlePlatform5;
	SceneNode* PlatformNode1, * PlatformNode2, * PlatformNode3, * PlatformNode4, * PlatformNode5;
	Bounds* left, * right, * bottom;
	SceneNode* LeftNode, * RightNode, * BottomNode;
	SceneNode* SceneNodesArray[1000];
	stack<SceneNode*> SceneNodesStack;
	Ogre::Entity* platformEntity;

public:
	Game();
	virtual ~Game() {}

	void setup();
	bool keyPressed(const KeyboardEvent& evt);
	bool mouseMoved(const MouseMotionEvent& evt);
	void createScene();
	SceneNode* addPlatforms(SceneManager* _scnMgr, int index);
	void generatePlatforms();
	void CreateBounds();
	void createCamera();
	void createFrameListener();
};
