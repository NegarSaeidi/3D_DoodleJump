
/**
* <summary>
* Ball class - have checkCollision, checkBounds, move functions
* Creates the shape of the ball
*</summary>
*/

#include "Doodle.h"
#include "CollisionManager.h"
#include <iostream>

/**
 * Constructor
 * Initializes the class variables
 * @return no return
 */

Doodle::Doodle() : position(100, 100, 0), scale(0.1f, 0.1f, 0.1f),speed(20.0f),gravity(-5),isFalling(false),jumpSpeed(350),doubleJump(450)
{
    bottomColliding = false;
    leftColliding = false;
    rightColliding = false;
    jumpOnPlatform = false;
    isOnPlatform = false;
    cameraMoved = false;
    tempSpeed = 0;
   
}
Doodle::~Doodle()
{
}




Vector3 Doodle::getScale()
{
    return scale;
}

void Doodle::Move(Ogre::SceneNode* sn, Ogre::Real evt,Vector3 dir, Ogre::SceneNode* cam)
{
  
    Vector3 tempPos = sn->getPosition();
    if ((bottomColliding || isOnPlatform) & !jumpOnPlatform)
    {
        tempPos += (Vector3(0, 1, 0)) * evt * jumpSpeed;
        //sn->translate((Vector3(0, 1, 0)) * evt * jumpSpeed);
    }
    if (isFalling & !jumpOnPlatform)
    {
       // sn->translate((Vector3(0, 1, 0)) * evt * gravity);
       tempPos += (Vector3(0, 1, 0)) * evt * gravity;
    }
    else
    {
       
        if (leftColliding)
        {
            if (dir.x > 0)
            {
                tempPos += dir * evt * speed;
               // sn->translate(dir * evt * speed);
            }
        }
        else if (rightColliding)
        {
            if (dir.x < 0)
            {//sn->translate(dir * evt * speed);
                tempPos += dir * evt * speed;
            }
        }
        else if (jumpOnPlatform)
        {
            
            //sn->translate(Vector3(0,1,0) * evt * doubleJump);
            tempPos += Vector3(0, 1, 0) * evt * speed;
            cam->translate(Vector3(0, 1, 0) * evt * speed*2);
            if (tempSpeed >= doubleJump)
            {
                jumpOnPlatform = false;
                tempSpeed = speed;
                cameraMoved = true;
            }
            else
                tempSpeed += 100;
       
        }
        else
        {
            tempPos += dir * evt * speed;
                //sn->translate(dir * evt * speed);

        }
       
    }
    sn->setPosition(tempPos);
  

  
}

void Doodle::checkBound(Ogre::SceneNode* sn, Ogre::SceneNode* left, Ogre::SceneNode* right, Ogre::SceneNode* bottom)
{
   
    if (CollisionManager::Instance()->checkCollision(sn,bottom))
    {
        bottomColliding = true;
    }
    else
        bottomColliding = false;
    if (CollisionManager::Instance()->checkCollision(sn, left))
    {
        leftColliding = true;

    }
    else
        leftColliding = false;
    if (CollisionManager::Instance()->checkCollision(sn, right))
    {
        rightColliding = true;
    }
    else
        rightColliding = false;

}

void Doodle::onPlatform(Ogre::SceneNode* playerNode, stack<Ogre::SceneNode*> platforms)
{
   
   
   
    stack<SceneNode*> mainStack, tempStack;
    bool flag = false;
    
   /* while(!platforms.empty())
    {
       
        platformsBoxes.push( platforms.top()->_getWorldAABB());
        tempStack.push(platforms.top());
        platforms.pop();
            
    }*/
   
   
   while(!platforms.empty())
      
   {
      
        if ((CollisionManager::Instance()->checkCollision(playerNode, platforms.top())))
        {
           
           
            if (playerNode->getPosition().y < platforms.top()->getPosition().y)
            {
               
                jumpOnPlatform = true;
              
              
            }

   
            else
            {
                if(!jumpOnPlatform)
                flag = true;

            }


        }
       
        platforms.pop();
      
    }
    if (flag)
        isOnPlatform = true;
    else
        isOnPlatform = false;

 

}

void Doodle::MoveCamera(Ogre::SceneNode* sn, Ogre::Real evt)
{
   
  
        sn->translate(Vector3(0, 1, 0) * evt * speed);
       
    
}



bool Doodle::hasCameraMoved()
{
    return cameraMoved;
}

void Doodle::setCameraHasMoved(bool b)
{
    cameraMoved = b;
}



