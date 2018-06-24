//
//  CCloud.cpp
//  FlappyGame
//
//  Created by rMBP on 2014/03/28.
//
//

#include "CCloud.h"
#include "Constants.h"

USING_NS_CC;

CCloud* CCloud::createCloudWithFilename(const char *filename)
{
    CCloud *sprite = new CCloud();
    if(sprite && sprite->initWithFile(filename))
    {
        
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return NULL;
}
void CCloud::Start()
{
    this->stopAllActions();
    float currentX = this->getPositionX();
    float distance = currentX - kCloudDestinationX;
    float time = distance / _pixelsPerSecond;
    CCPoint destination = ccp(kCloudDestinationX, this->getPositionY());
    
    CCMoveTo *actionMove = CCMoveTo::create(time, destination);
    CCCallFuncN *actionMoveDone = CCCallFuncN::create(this, callfuncN_selector(CCloud::ReachedDestination));
    
    this->runAction(CCSequence::create(actionMove, actionMoveDone, NULL));
}

void CCloud::Stop()
{
    this->stopAllActions();
}

void CCloud::SetSpeedAndWidth(const float speed, const float width)
{
    _speed = speed;
    _screenWidth = width;
    _pixelsPerSecond = _screenWidth / _speed;
}

void CCloud::ReachedDestination()
{
    this->setPositionX(kCloudRestartX + _screenWidth);
    this->Start();
}