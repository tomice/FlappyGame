//
//  CPipe.cpp
//  FlappyGame
//
//  Created by rMBP on 2014/03/28.
//
//

#include "CPipe.h"
#include "Constants.h"

USING_NS_CC;

CPipe* CPipe::createPipeWithFilename(const char *filename)
{
    CPipe *sprite = new CPipe();
    if(sprite && sprite->initWithFile(filename))
    {
        sprite->setVisible(false);
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return NULL;
}

void CPipe::Start()
{
    this->stopAllActions();
    
    float distance = _xOffset + _screenWidth + _xOffset;
    float time = distance / _pixelsPerSecond;
    CCPoint destination = ccp(kCloudDestinationX, this->getPositionY());
    this->setPosition(ccp(_xOffset + _screenWidth, getPositionY()));
    
    CCMoveTo *actionMove = CCMoveTo::create(time, destination);
    CCCallFuncN *actionMoveDone = CCCallFuncN::create(this, callfuncN_selector(CPipe::ReachedDestination));
    _state = kPipeStateActive;
    this->setVisible(true);
    this->runAction(CCSequence::create(actionMove, actionMoveDone, NULL));
}

void CPipe::Stop()
{
    this->stopAllActions();
    this->setVisible(false);
    _state = kPipeStateInactive;
    this->setPosition(ccp(_InactiveX, this->getPositionY()));
}

void CPipe::Initialize(const float speed, const float width, const float XOffset, const float InactiveX)
{
    _speed = speed;
    _screenWidth = width;
    _pixelsPerSecond = _screenWidth / _speed;
    _InactiveX = InactiveX;
    this->setPosition(ccp(_InactiveX, 0));
    _state = kPipeStateInactive;
}

void CPipe::ReachedDestination()
{
    Stop();
}

int CPipe::GetState()
{
    return _state;
}