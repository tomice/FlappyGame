#include "HelloWorldScene.h"
#include "Constants.h"
#include "CFlappy.h"
#include "CCloud.h"
#include "CPipe.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// Touch functionality
void HelloWorld::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *event)
{
    CCSetIterator i;
    CCTouch *touch;
    CCPoint tap;
    
    for(i = pTouches->begin(); i != pTouches->end(); i++)
    {
        touch = (CCTouch *)(*i);
        if(touch)
        {
            tap = touch->getLocation();
            CCLOG("Touched at %.2f,%.2f",tap.x,tap.y);
            if(_flappy->boundingBox().containsPoint(tap))
            {
                if(_flappy->GetState() == kFlappyStateStopped)
                {
                    StartGame();
                }
                else
                {
                    _flappy->SetStartSpeed();
                }
            }
        }
    }

}

void HelloWorld::ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *event)
{
    
}

void HelloWorld::ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *event)
{

}

void HelloWorld::SetSpawnTime()
{
    _lastSpawnTime = 0;
    _nextSpawnTime = (float)(rand() % kPipeSpawnMaxVariance) / 10 + kPipeSpawnMinTime;
}

void HelloWorld::SpawnNewPipes()
{
    int ourChance = rand() % 4 + 1;
    
    if(ourChance == 1)
    {
        SpawnUpperOrLower(true);
    }
    else if(ourChance == 2)
    {
        SpawnUpperOrLower(false);
    }
    else
    {
        SpawnPairOfPipes();
    }
}

void HelloWorld::SpawnUpperOrLower(bool isUpper)
{
    int Ymax = isUpper == true ? kSingleGapTop : _middleY;
    int Ymin = isUpper == true ? _middleY : kSingleGapBottom;
    
    int YRange = abs(Ymax - Ymin);
    
    int Ypos = Ymax - rand() % YRange;
    
    SpawnPipe(isUpper, Ypos);
}

void HelloWorld::SpawnPairOfPipes()
{
    int Gap = kDoubleGapMin + (rand() % (kDoubleGapMax - kDoubleGapMin));
    int YRange = kDoubleGapTop - Gap - kDoubleGapBottom;
    int TopY = kDoubleGapTop - (rand() % YRange);
    int BottomY = TopY - Gap;
    
    SpawnPipe(true, TopY);
    SpawnPipe(false, BottomY);
}

void HelloWorld::SpawnPipe(bool isUpper, float yPosition)
{
    CPipe *pipe = GetNextPipe();
    
    if(isUpper == true)
    {
        pipe->setAnchorPoint(ccp(0.5,0));
        pipe->setFlipY(false);
    }
    else
    {
        pipe->setAnchorPoint(ccp(0.5,1));
        pipe->setFlipY(true);
    }
    
    pipe->setPositionY(yPosition);
    pipe->Start();
}

CPipe *HelloWorld::GetNextPipe()
{
    CCObject *it;
    
    CCARRAY_FOREACH(_pipes, it)
    {
        CPipe *pipe = static_cast<CPipe*>(it);
        if(pipe->GetState() == kPipeStateInactive)
        {
            return pipe;
        }
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CPipe *newPipe = CPipe::createPipeWithFilename("Pipe-HD.png");
    
    // note the cloud speed. should be treespeed...
    newPipe->Initialize(2.0, visibleSize.width, kPipeOffsetX, kPipeInactiveX);
    this->addChild(newPipe, kZindexPipe);
    _pipes->addObject(newPipe);
    return newPipe;
}


void HelloWorld::GameUpdate(float deltaTime)
{
    if(_gameStarted == true)
    {
        _lastSpawnTime += deltaTime;
        if(_lastSpawnTime > _nextSpawnTime)
        {
            SetSpawnTime();
            SpawnNewPipes();
        }
        bool gameOver = false;
        if(_flappy->getPositionY() < 0)
        {
            gameOver = true;
        }
        else
        {
            CCObject *it;
            
            CCARRAY_FOREACH(_pipes, it)
            {
                CPipe *pipe = static_cast<CPipe*>(it);
                if(pipe->GetState() == kPipeStateActive)
                {
                    if(_flappy->PipeCollisionBox().intersectsRect(pipe->boundingBox()))
                    {
                        gameOver = true;
                    }
                }
            }
        }
        
        if(gameOver == true)
        {
            GameOver();
        }
        else
        {
            _flappy->UpdateFlappy(deltaTime);
        }
    }


}

void HelloWorld::CreateClouds()
{
    _clouds = new CCArray();
    AddCloud(kCloudSpeedSlow, ccp(700,610), kCloudScaleSlow, kZindexCloudSlow);
    AddCloud(kCloudSpeedSlow, ccp(150,570), kCloudScaleSlow, kZindexCloudSlow);
    
    AddCloud(kCloudSpeedFast, ccp(150,300), kCloudScaleFast, kZindexCloudFast);
    AddCloud(kCloudSpeedFast, ccp(400,500), kCloudScaleFast, kZindexCloudFast);
    AddCloud(kCloudSpeedFast, ccp(880,400), kCloudScaleFast, kZindexCloudFast);
}

void HelloWorld::AddCloud(const float speed, const cocos2d::CCPoint position, const float scale, const int zIndex)
{
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCloud *cloud = CCloud::createCloudWithFilename("Cloud-HD.png");
    cloud->SetSpeedAndWidth(speed, visibleSize.width);
    cloud->setPosition(position);
    cloud->setScale(scale);
    this->addChild(cloud, zIndex);
    _clouds->addObject(cloud);
}

void HelloWorld::StopClouds()
{
    CCObject *it;
    CCARRAY_FOREACH(_clouds, it)
    {
        CCloud *cloud = static_cast<CCloud*>(it);
        cloud->Stop();
    }
    
    CCARRAY_FOREACH(_pipes, it)
    {
        CPipe *pipe = static_cast<CPipe*>(it);
        pipe->stopAllActions();
    }
}

void HelloWorld::StartClouds()
{
    CCObject *it;
    CCARRAY_FOREACH(_clouds, it)
    {
        CCloud *cloud = static_cast<CCloud*>(it);
        cloud->Start();
    }
    
    CCARRAY_FOREACH(_pipes, it)
    {
        CPipe *pipe = static_cast<CPipe*>(it);
        pipe->Stop();
    }
}

void HelloWorld::StopGame()
{
    StopClouds();
    _gameStarted = false;
    _nextSpawnTime = 0.2;
    CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    
}

void HelloWorld::StartGame()
{
    _flappy->setPositionY(_middleY);
    _flappy->SetState(kFlappyStateMoving);
    StartClouds();
    _gameStarted = true;
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Background.mp3", true);
}

void HelloWorld::GameOver()
{
    _flappy->Reset();
    StopGame();
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Headshot.wav");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    srand(time(NULL));
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    _middleY = visibleSize.height / 2;
    
    CCSprite *bgSprite = CCSprite::create("Background-HD.png");
    bgSprite->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(bgSprite, kZindexBackground);
    
    _flappy = CFlappy::createFlappyWithFilename("Flappy-HD.png");
    _flappy->setPosition(ccp(kFlappyStartX, visibleSize.height / 2));
    this->addChild(_flappy, kZindexFlappy);
    
    CreateClouds();
    _pipes = new CCArray();
    StopGame();
    
    this->setTouchEnabled(true);
    
    this->schedule(schedule_selector(HelloWorld::GameUpdate));
    
    return true;
}