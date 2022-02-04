#pragma once
#include "cocos2d.h"
#include "CCSprite.h"
#include "WorldSelectLayer.h"
#include "GameManager.h"

class CreatorLayer : public cocos2d::CCLayer 
{
public:

public:
    CreatorLayer();
    virtual ~CreatorLayer();
	
	void onMyLevels(CCObject*);

};

class CreatorLayerExt : public CreatorLayer 
{
public:
    void onWorld( cocos2d::CCObject* ref )
    {
        auto dir = CCDirector::sharedDirector();
        dir->pushScene( cocos2d::CCTransitionFade::create(0.5, WorldSelectLayer::scene( 0 ) ) );
    }
};