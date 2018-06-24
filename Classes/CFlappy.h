//
//  CFlappy.h
//  FlappyGame
//
//  Created by rMBP on 2014/03/28.
//
//

#ifndef __FlappyGame__CFlappy__
#define __FlappyGame__CFlappy__

#include "cocos2d.h"

class CFlappy : public cocos2d::CCSprite
{
    
public:
    
    static CFlappy* createFlappyWithFilename(const char *filename);
    void UpdateFlappy(float deltaTime);
    void Reset();
    int GetState();
    void SetState(int state);
    void SetStartSpeed();
    cocos2d::CCRect PipeCollisionBox();
    
    bool InUD;
    
private:
    
    //const float StartSpeedY = 300;
    int _state;
    float _speedY;
    float lastUpdate;
};

#endif /* defined(__FlappyGame__CFlappy__) */
