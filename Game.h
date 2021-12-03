#pragma once
#include "Ball.h"
#include "Ogre.h"
#include "OgreApplicationContext.h"
#include "OgreInput.h"
#include "OgreMaterial.h"
#include "OgreRTShaderSystem.h"
#include "OgreTrays.h"
#include "Ball.h"
#include "Bat.h"



using namespace Ogre;
using namespace OgreBites;

class Game
    : public ApplicationContext
    , public InputListener
{
private:
    Ogre::SceneNode* BallNode, * batNode;
    Doodle* ball;
    Platform* bat;
    float windowWidth, windowHeight;
    OgreBites::Label* mScoreLabel;
    OgreBites::Label* mScore;

    OgreBites::Label* mLivesLabel;
    OgreBites::Label* mLives;

    OgreBites::Label* mFpsLabel;
    OgreBites::Label* mFps;
    OgreBites::Label* mTpuLabel;
    OgreBites::Label* mTpu;

    
public:
    Game();
    virtual ~Game() {}
    void setup();
    bool keyPressed(const KeyboardEvent& evt);
    void createFrameListener();

};