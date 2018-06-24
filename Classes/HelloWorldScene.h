#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class CFlappy;
class CPipe;

class HelloWorld : public cocos2d::CCLayer
{
private:
    CFlappy *_flappy;
    float _middleY;
    cocos2d::CCArray* _clouds;
    cocos2d::CCArray* _pipes;
    
    float _nextSpawnTime;
    float _lastSpawnTime;
    bool _gameStarted;
    float _floorY;
    
    
    void GameUpdate(float deltaTime);
    void CreateClouds();
    void AddCloud(const float speed, const cocos2d::CCPoint position, const float scale, const int zIndex);
    void StopClouds();
    void StartClouds();
    void StopGame();
    void StartGame();
    void GameOver();
    
    void SetSpawnTime();
    void SpawnNewPipes();
    void SpawnUpperOrLower(bool isUpper);
    void SpawnPairOfPipes();
    void SpawnPipe(bool isUpper, float yPosition);
    CPipe *GetNextPipe();
    
    
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    //void menuCloseCallback(CCObject* pSender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);
    
    // Overriding this for touch functionality
    virtual void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *event);
    virtual void ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *event);
    virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *event);
};

#endif // __HELLOWORLD_SCENE_H__
