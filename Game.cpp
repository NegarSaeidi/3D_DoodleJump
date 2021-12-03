

#include "Ogre.h"
#include "OgreApplicationContext.h"
#include "OgreInput.h"
#include "OgreRTShaderSystem.h"
#include "Doodle.h"
#include "Platform.h"
#include <iostream>

using namespace Ogre;
using namespace OgreBites;
float rotX = 0.0f;
float rotY = 0.0f;
Ogre::Real m_Angle = 0.0;
Ogre::Vector3 translate(0, 0, 0);

class ExampleFrameListener : public Ogre::FrameListener
{
private:
    Ogre::SceneNode* _sceneNode;
    Ogre::SceneNode* _camNode;
    float _movementspeed;
    float _mousespeed;
public:

    ExampleFrameListener( Ogre::SceneNode* camNode)
    {
     
        _camNode = camNode;
        _movementspeed = 200.0f;
        _mousespeed = 0.002f;
    }

    bool frameStarted(const Ogre::FrameEvent& evt)
    {
        _camNode->yaw(Ogre::Radian(rotX * _mousespeed));
        _camNode->pitch(Ogre::Radian(rotY * _mousespeed));
        //_camNode->translate(translate * evt.timeSinceLastFrame * _movementspeed);
        _sceneNode->translate(translate * evt.timeSinceLastFrame * _movementspeed);
        translate = Ogre::Vector3(0, 0, 0);
        rotX = 0.0f;
        rotY = 0.0f;
        return true;
    }
};

class Game
    : public ApplicationContext
    , public InputListener
{
private:
    SceneManager* scnMgr;
    Root* root;
    Doodle* player;
    Platform* doodlePlatform;
public:
    Game();
    virtual ~Game(){}

    void setup();
    void createScene();
    void createCamera();
    bool keyPressed(const KeyboardEvent& evt);
    bool mouseMoved(const MouseMotionEvent& evt);
    void createFrameListener();
    Ogre::SceneNode* PlayerNode,*PlatformNode;
    SceneNode* camNode;
};


Game::Game(): ApplicationContext("week13-1-MeshDemo")
{
}


void Game::setup()
{
    // do not forget to call the base first
    ApplicationContext::setup();
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

void Game::createScene()
{

    // -- tutorial section start --
    //! [turnlights]
    scnMgr->setAmbientLight(ColourValue(0.5, 0.5, 0.5));
    //! [turnlights]

    //! [newlight]
    //
    Light* light1 = scnMgr->createLight("Light1");
    light1->setType(Ogre::Light::LT_DIRECTIONAL);
    // Set Light Color
    light1->setDiffuseColour(1.0f, 1.0f, 1.0f);
    // Set Light Reflective Color
    light1->setSpecularColour(1.0f, 0.0f, 0.0f);
    // Set Light (Range, Brightness, Fade Speed, Rapid Fade Speed)
    light1->setAttenuation(10, 0.5, 0.045, 0.0);

    //
    Entity* lightEnt = scnMgr->createEntity("LightEntity", "sphere.mesh");
    SceneNode* lightNode = scnMgr->createSceneNode("LightNode");
    //lightNode->attachObject(lightEnt);
    lightNode->attachObject(light1);
    lightNode->setScale(0.01f, 0.01f, 0.01f);


    scnMgr->getRootSceneNode()->addChild(lightNode);
    //! [newlight]



    //! [lightpos]
    lightNode->setPosition(0, 4, 10);
    //! [lightpos]
    Plane plane(Vector3::UNIT_Y, -10);

 /*   MeshManager::getSingleton().createPlane(
        "ground", RGN_DEFAULT,
        plane,
        1500, 1500, 20, 20,
        true,
        1, 5, 5,
        Vector3::UNIT_Z);
    Entity* groundEntity = scnMgr->createEntity("ground");
    scnMgr->getRootSceneNode()->createChildSceneNode()->attachObject(groundEntity);
    groundEntity->setCastShadows(false);
    groundEntity->setMaterialName("DoodleBackground");*/
    //Create Player
    player = new Doodle();
    Ogre::ManualObject* doodle_manual = scnMgr->createManualObject("Doodle");
    player->getShape(doodle_manual);
    Ogre::Entity* doodle_entity = scnMgr->createEntity("Doodle");
    PlayerNode = scnMgr->getRootSceneNode()->createChildSceneNode("PlayerNode");
    PlayerNode->scale(player->getScale());
    PlayerNode->attachObject(doodle_entity);

    //Platform
   // doodlePlatform = new Platform();
   

    //Ogre::ManualObject* ManualObj = new ManualObject("Cube");  
    //doodlePlatform->CreateShape(ManualObj);
    //PlatformNode = scnMgr->getRootSceneNode()->createChildSceneNode("CubeNode");
    //PlatformNode->attachObject(ManualObj);

    //PlatformNode->setScale(2.0, 2.0, 2.0);
    //PlatformNode->setPosition(doodlePlatform->getPosition());
    //Background

   // scnMgr->setSkyBox(true, "DoodleBackground", 300, false);

}
bool Game::mouseMoved(const MouseMotionEvent& evt)
{
    rotX = evt.xrel;
    rotY = evt.yrel;
    return true;
}
void Game::createCamera()
{

    //! [camera]
     camNode = scnMgr->getRootSceneNode()->createChildSceneNode();

    // create the camera
    Camera* cam = scnMgr->createCamera("myCam");
    cam->setNearClipDistance(5); // specific to this sample
    cam->setAutoAspectRatio(true);
    camNode->attachObject(cam);
    camNode->setPosition(0, 2, 100);
;
    
    camNode->lookAt(Ogre::Vector3(0, 0, 0), Node::TS_WORLD);

    // and tell it to render into the main window
    getRenderWindow()->addViewport(cam);

    //! [camera]
}

bool Game::keyPressed(const KeyboardEvent& evt)
{
    switch (evt.keysym.sym)
    {
    case SDLK_ESCAPE:
        getRoot()->queueEndRendering();
        break;
    case 'w':
        translate = Ogre::Vector3(0, 10, 0);
        break;
    case 's':
        translate = Ogre::Vector3(0, -10, 0);
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

void Game::createFrameListener()
{
    Ogre::FrameListener* FrameListener = new ExampleFrameListener(camNode);
    mRoot->addFrameListener(FrameListener);
}


int main(int argc, char** argv)
{
    try
    {
        Game app;
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

//! [fullsource]

