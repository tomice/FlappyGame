//
//  CFlappy.cpp
//  FlappyGame
//
//  Created by rMBP on 2014/03/28.
//
//

#include "CFlappy.h"
#include "Constants.h"
USING_NS_CC;

CFlappy* CFlappy::createFlappyWithFilename(const char *filename)
{
    CFlappy *sprite = new CFlappy();
    if(sprite && sprite->initWithFile(filename))
    {
        sprite->Reset();
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return NULL;
}

void CFlappy::UpdateFlappy(float deltaTime)
{
    if(this->_state == kFlappyStateMoving)
    {
        float distance = 0;
        float newSpeed = 0;
        float OldSpeed = _speedY;
        distance = _speedY * deltaTime + 0.5 * GRAVITY * deltaTime * deltaTime;
        newSpeed = _speedY + GRAVITY * deltaTime;
        
        this->setPositionY(this->getPositionY() + distance);
        _speedY = newSpeed;
    }
}
void CFlappy::Reset()
{
    _state = kFlappyStateStopped;
    SetStartSpeed();
}
int CFlappy::GetState()
{
    return _state;
}
void CFlappy::SetState(int st)
{
    _state = st;
}
void CFlappy::SetStartSpeed()
{
    _speedY = kFlappyStartSpeedY;
}

CCRect CFlappy::PipeCollisionBox()
{
    return CCRect (
    this->boundingBox().origin.x + 20,
    this->boundingBox().origin.y + 5,
    this->boundingBox().size.width - 35,
    this->boundingBox().size.height - 25
    );
}