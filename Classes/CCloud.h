//
//  CCloud.h
//  FlappyGame
//
//  Created by rMBP on 2014/03/28.
//
//

#ifndef __FlappyGame__CCloud__
#define __FlappyGame__CCloud__

#include "cocos2d.h"

class CCloud : public cocos2d::CCSprite
{
    
public:
    
    static CCloud* createCloudWithFilename(const char *filename);
    void Start();
    void Stop();
    void SetSpeedAndWidth(const float speed, const float width);
    
    
private:
    
    void ReachedDestination();
    
    float _speed;
    float _screenWidth;
    float _pixelsPerSecond;

};

#endif /* defined(__FlappyGame__CCloud__) */
