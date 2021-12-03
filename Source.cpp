//Week3-8-CameraDemo
//We used our created camera in combination with user input.To be able to manipulate the
//camera, we needed to pass it to our FrameListener.This was done in ExampleFrameListener using
//the constructor.To control our camera, we wanted to use the mouse.So first we had to
//override mouseMoved interface.
//Mouse movement can happen on two axes, namely, the x - axis and the y - axis.Both axes'
//movements are saved separately in the X and Y variable of the mouse state.We then have
//the possibility to get the relative or absolute values.Because we are only interested in
//mouse movement and not the position of the mouse, we are using the relative values.
//Hooman Salamat


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

Ogre::Vector3 translate(0, 0, 0);
float rotX = 0.0f;
float rotY = 0.0f;
const int platformNumber = 5;

class HUDFrameListener : public Ogre::FrameListener
{
private:
	OgreBites::Label* _Tpu,* _Lives,* _Score;
	Ogre::Real lastTpu=0;
public:
	HUDFrameListener(OgreBites::Label* mTpu, OgreBites::Label* mLives, OgreBites::Label* mScore)
	{
		_Tpu = mTpu;
		_Lives = mLives;
		_Score = mScore;
	}
	bool frameStarted(const Ogre::FrameEvent& evt)
	{
		if(Ogre::Math::Abs(lastTpu*1000-evt.timeSinceLastFrame*1000)>10)
		_Tpu->setCaption(Ogre::StringConverter::toString(evt.timeSinceLastFrame * 1000));
		lastTpu = evt.timeSinceLastFrame;
		
		return true;
	}
};
class PlayerFrameListener : public Ogre::FrameListener
{
private:
	Ogre::SceneNode* _PlayerNode,*_LeftBoundNode,*_RightBoundNode,*_BottomBoundNode;
	Ogre::SceneNode* _camNode;
	float _movementspeed;
	float _mousespeed;
	Doodle* _PlayerDoodle;
	Ogre::SceneNode* _PlatformsArray[5];
	int index = 5,count=0;
	Ogre::Entity* _platformEntity[1000];
	SceneManager* _scnMgr;
	stack<SceneNode*> _PlatformsStack;

	
public:

	PlayerFrameListener(Ogre::SceneNode* PlayerNode, Ogre::SceneNode* left, Ogre::SceneNode* right, Ogre::SceneNode* bottom, Doodle* playerDoodle,Ogre::SceneNode* cam, stack<SceneNode*> sns,Ogre::Entity* pe, SceneManager* scnMgr)
	{
		for (int i = 0; i < 4; i++)
		{
			_PlatformsStack.push(sns.top());
			sns.pop();
		}
		
		_camNode = cam;
		_PlayerNode = PlayerNode;
		_PlayerDoodle = playerDoodle;
		_LeftBoundNode = left;
		_RightBoundNode = right;
		_BottomBoundNode = bottom;
		//_platformEntity = scnMgr->createEntity("platform");;
		_scnMgr = scnMgr;
		_movementspeed = 200.0f;
		_mousespeed = 0.002f;

	}

	bool frameStarted(const Ogre::FrameEvent& evt)
	{
		
		
		
	
		if (!translate.isZeroLength())
		_PlayerDoodle->isFalling = false;
		else
		_PlayerDoodle->isFalling = true;
	
		_PlayerDoodle->onPlatform(_PlayerNode,_PlatformsStack);
		_PlayerDoodle->checkBound(_PlayerNode, _LeftBoundNode, _RightBoundNode, _BottomBoundNode);
		_PlayerDoodle->Move(_PlayerNode,evt.timeSinceLastFrame,translate,_camNode);
		if (_PlayerDoodle->hasCameraMoved())
		{
			//for (int i = 0; i < 2; i++)
			//{
				addPlatforms();
			//}
			
			_PlayerDoodle->setCameraHasMoved(false);
		}
	
			translate = Vector3(0, 0, 0);
		
		return true;
	}
	void addPlatforms()
	{
		
		Ogre::Entity* e = _scnMgr->createEntity("platform");
		string name = "PlatfromNode" + Ogre::StringConverter::toString(index);
		Ogre::SceneNode* node = _scnMgr->getRootSceneNode()->createChildSceneNode(name);
		node->attachObject(e);
		float x = Ogre::Math::RangeRandom(-10, 10);
		float y = Ogre::Math::RangeRandom(_PlayerNode->getPosition().y+10, _PlayerNode->getPosition().y + 20);
		float z = 20;
		node->setPosition(Vector3(x,y,z));
		node->setScale(8, 1, 4);
		_PlatformsStack.push(node);
		
		index++ ;
	 
		
	}
};

class OgreTutorial
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
	Bounds* left, *right, *bottom;
	SceneNode* LeftNode, *RightNode, *BottomNode;
	SceneNode* SceneNodesArray[1000];
	stack<SceneNode*> SceneNodesStack;
	Ogre::Entity* platformEntity;
	
public:
	OgreTutorial();
	virtual ~OgreTutorial() {}

	void setup();
	bool keyPressed(const KeyboardEvent& evt);
	bool mouseMoved(const MouseMotionEvent& evt);
	void createScene();
	void generatePlatforms();
	void CreateBounds();
	void createCamera();
	void createFrameListener();
};


OgreTutorial::OgreTutorial()
	: ApplicationContext("3D-DoodleJump-NegarSaeidi")
{
}


void OgreTutorial::setup()
{
	
	// do not forget to call the base first
	ApplicationContext::setup();
	getRenderWindow()->resize(500, 1000);
	
	addInputListener(this);

	// get a pointer to the already created root
	root = getRoot();
	scnMgr = root->createSceneManager();


	// register our scene with the RTSS
	RTShader::ShaderGenerator* shadergen = RTShader::ShaderGenerator::getSingletonPtr();
	shadergen->addSceneManager(scnMgr);

	createScene();
	createCamera();
	createFrameListener();
	

}

bool OgreTutorial::mouseMoved(const MouseMotionEvent& evt)
{
	rotX = evt.xrel;
	rotY = evt.yrel;
	return true;
}

bool OgreTutorial::keyPressed(const KeyboardEvent& evt)
{
	switch (evt.keysym.sym)
	{
	case SDLK_ESCAPE:
		getRoot()->queueEndRendering();
		break;
	case 'w':
		translate = Ogre::Vector3(0, 0, -40);
	
		break;
	case 's':
	
		translate = Ogre::Vector3(0, 0, 40);
		break;
	case 'a':
	
		translate = Ogre::Vector3(-10, 0, 0);
		break;
	case 'd':
		
		translate = Ogre::Vector3(10, 0, 0);
		break;
	
		
	default:
		
		break;
	}
	return true;
}

void OgreTutorial::createScene()
{
	// -- tutorial section start --
	
	Ogre::SceneNode* node = scnMgr->createSceneNode("Node1");
	scnMgr->getRootSceneNode()->addChild(node);

	scnMgr->setShadowTechnique(ShadowTechnique::SHADOWTYPE_STENCIL_ADDITIVE);

	//! [turnlights]
	scnMgr->setAmbientLight(ColourValue(0.5, 0.5, 0.5));
	//! [turnlights]

 //! [newlight]
 //

	Ogre::Light* light = scnMgr->createLight("Light1");
	light->setType(Ogre::Light::LT_DIRECTIONAL);
	light->setDirection(Ogre::Vector3(1, -1, 0));

	// Set Light Color
	light->setDiffuseColour(1.0f, 1.0f, 1.0f);
	// Set Light Reflective Color
	light->setSpecularColour(1.0f, 1.0f, 0.0f);
	// Set Light (Range, Brightness, Fade Speed, Rapid Fade Speed)
	//light1->setAttenuation(10, 0.5, 0.045, 0.0);

	//
	Entity* lightEnt = scnMgr->createEntity("LightEntity", "sphere.mesh");
	SceneNode* lightNode = node->createChildSceneNode("LightNode");
	lightNode->attachObject(lightEnt);
	lightNode->attachObject(light);
	lightNode->setScale(0.01f, 0.01f, 0.01f);

	OgreBites::TrayManager* mTrayMgr = new OgreBites::TrayManager("InterfaceName", getRenderWindow());
	//you must add this in order to add a tray
	scnMgr->addRenderQueueListener(mOverlaySystem);
	addInputListener(mTrayMgr);

	
	mTrayMgr->showFrameStats(TL_BOTTOMLEFT);
	mTrayMgr->toggleAdvancedFrameStats();

	mScoreLabel = mTrayMgr->createLabel(TL_TOPLEFT, "Score", "Score:", 150);
	mScore = mTrayMgr->createLabel(TL_TOPLEFT, "score", "0", 150);

	mTpuLabel = mTrayMgr->createLabel(TL_TOPRIGHT, "Time/Update", "Time/Update:", 150);
	mTpu = mTrayMgr->createLabel(TL_TOPRIGHT, "tpu", "0", 150);

	mLivesLabel = mTrayMgr->createLabel(TL_TOPLEFT, "Lives", "Lives:", 150);
	mLives = mTrayMgr->createLabel(TL_TOPLEFT, "lives", "5", 150);

	CreateBounds();
	
	generatePlatforms();
	
	player = new Doodle();
	Entity* ent = scnMgr->createEntity("Sinbad.mesh");
	ent->setCastShadows(false);
	SinbadNode = scnMgr->createSceneNode("Character");
	SinbadNode->attachObject(ent);
	scnMgr->getRootSceneNode()->addChild(SinbadNode);
	SinbadNode->setPosition(Ogre::Vector3(6.01f, 4.51f, 22.8f));
	SinbadNode->setScale(0.8f, 0.8f, 0.8f);

	
	platformEntity = scnMgr->createEntity("platform");
	scnMgr->setSkyBox(true, "DoodleBackground", 500, false);
	cout << "............" + Ogre::StringConverter::toString(SoundManager::Instance()->playSound("l;")) << endl;
}

void OgreTutorial::generatePlatforms()
{

	   DoodlePlatform1 = new Platform();
	   Ogre::ManualObject* ManualObj = new ManualObject("Cube");
	   DoodlePlatform1->CreateShape(ManualObj, "MyMaterial1");
	   Ogre::Entity* p1 = scnMgr->createEntity("platform");
	   PlatformNode1 = scnMgr->getRootSceneNode()->createChildSceneNode("PlatformNode1");
	   PlatformNode1->attachObject(p1);
	   DoodlePlatform1->setPosition(Vector3(5, 10, 20));
	   PlatformNode1->setPosition(DoodlePlatform1->getPosition());
	   PlatformNode1->setScale(8, 1, 4);
	   //SceneNodesArray[0] = PlatformNode1;
	   SceneNodesStack.push(PlatformNode1);
	  


		DoodlePlatform2 = new Platform();
		Ogre::Entity* p2 = scnMgr->createEntity("platform");
		PlatformNode2 = scnMgr->getRootSceneNode()->createChildSceneNode("PlatformNode2");
		PlatformNode2->attachObject(p2);
		DoodlePlatform2->setPosition(Vector3(10, 20, 20));
		PlatformNode2->setPosition(DoodlePlatform2->getPosition());
		PlatformNode2->setScale(8, 1, 4);
		//SceneNodesArray[1] = PlatformNode2;
		SceneNodesStack.push(PlatformNode2);

		DoodlePlatform3 = new Platform();
		Ogre::Entity* p3 = scnMgr->createEntity("platform");
		PlatformNode3 = scnMgr->getRootSceneNode()->createChildSceneNode("PlatformNode3");
		PlatformNode3->attachObject(p3);
		DoodlePlatform3->setPosition(Vector3(-5, 30, 20));
		PlatformNode3->setPosition(DoodlePlatform3->getPosition());
		PlatformNode3->setScale(8, 1, 4);
		//SceneNodesArray[2] = PlatformNode3;
		SceneNodesStack.push(PlatformNode3);

		DoodlePlatform4 = new Platform();
		Ogre::Entity* p4 = scnMgr->createEntity("platform");
		PlatformNode4 = scnMgr->getRootSceneNode()->createChildSceneNode("PlatformNode4");
		PlatformNode4->attachObject(p4);
		DoodlePlatform4->setPosition(Vector3(-10, 15, 20));
		PlatformNode4->setPosition(DoodlePlatform4->getPosition());
		PlatformNode4->setScale(8, 1, 4);
		//SceneNodesArray[3] = PlatformNode4;
		SceneNodesStack.push(PlatformNode4);

	

	
	
}

void OgreTutorial::CreateBounds()
{
	//LeftBound
	left = new Bounds();
	Ogre::ManualObject* ManualObj1 = new ManualObject("edge1");
	left->CreateShape(ManualObj1);
	Ogre::Entity* el = scnMgr->createEntity("bounds");
	LeftNode = scnMgr->getRootSceneNode()->createChildSceneNode("LeftNode");
	LeftNode->attachObject(el);
	left->setPosition(Vector3(-20, 0, 0));
	LeftNode->setPosition(left->getPosition());
	LeftNode->setScale(1, 500, 200);
	//RightBound
	right = new Bounds();
	Ogre::ManualObject* ManualObj2 = new ManualObject("edge2");;
	Ogre::Entity* er = scnMgr->createEntity("bounds");
	RightNode = scnMgr->getRootSceneNode()->createChildSceneNode("RIghtNode");
	RightNode->attachObject(er);
	right->setPosition(Vector3(20, 0, 0));
	RightNode->setPosition(right->getPosition());
	RightNode->setScale(1, 500, 200);
	//BottomBound
	bottom= new Bounds();
	Ogre::ManualObject* ManualObj3 = new ManualObject("edge3");
	Ogre::Entity* eb = scnMgr->createEntity("bounds");
	BottomNode = scnMgr->getRootSceneNode()->createChildSceneNode("BottomNode");
	BottomNode->attachObject(eb);
	bottom->setPosition(Vector3(-20, 0, 0));
	BottomNode->setPosition(bottom->getPosition());
	BottomNode->setScale(500, 1, 200);
}

void OgreTutorial::createCamera()
{
	//! [camera]
	camNode = scnMgr->getRootSceneNode()->createChildSceneNode();

	// create the camera
	cam = scnMgr->createCamera("myCam");
	cam->setNearClipDistance(5); // specific to this sample
	cam->setAutoAspectRatio(true);

	camNode->attachObject(cam);
	camNode->setPosition(0,30, 100);
	camNode->lookAt(Ogre::Vector3(0, -10, -40), Node::TS_WORLD);

	// and tell it to render into the main window
	getRenderWindow()->addViewport(cam);

	//! [camera]


}

void OgreTutorial::createFrameListener()
{

	Ogre::FrameListener* FrameListener1 = new PlayerFrameListener(SinbadNode, LeftNode, RightNode, BottomNode, player, camNode, SceneNodesStack, platformEntity, scnMgr);
	mRoot->addFrameListener(FrameListener1);

	Ogre::FrameListener* FrameListener2 = new HUDFrameListener(mTpu,mLives,mScore);
	mRoot->addFrameListener(FrameListener2);
}

int main(int argc, char** argv)
{
	try
	{
		OgreTutorial app;
		app.initApp();
		app.getRoot()->startRendering();
		app.closeApp();
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error occurred during execution: " << e.what() << '\n';
		return 1;
	}

	return 0;
}