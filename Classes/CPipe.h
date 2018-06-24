//
//  CPipe.h
//  FlappyGame
//
//  Created by rMBP on 2014/03/28.
//
//

#ifndef __FlappyGame__CPipe__
#define __FlappyGame__CPipe__

#include "cocos2d.h"

class CPipe : public cocos2d::CCSprite
{
    
public:
    
    static CPipe* createPipeWithFilename(const char *filename);
    void Start();
    void Stop();
    void Initialize(const float speed, const float width, const float XOffset, const float InactiveX);
    
    int GetState();
    
private:
    
    void ReachedDestination();
    int _state;
    float _speed;
    float _screenWidth;
    float _pixelsPerSecond;
    float _xOffset;
    float _InactiveX;
    
};

#endif /* defined(__FlappyGame__CPipe__) */
