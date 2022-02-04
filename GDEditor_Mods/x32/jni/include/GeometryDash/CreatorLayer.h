#pragma once
#include "cocos2d.h"
#include "CCSprite.h"
#include "WorldSelectLayer.h"
#include "GameManager.h"

#include "GDAPI_Macros.h"

class CreatorLayer : public cocos2d::CCLayer 
{
public:
    CLASS_MEMBER(cocos2d::CCSprite*, questBtnSpr, 0x134);

public:
    CreatorLayer();
    virtual ~CreatorLayer();
	
	void onMyLevels(CCObject*);
    void onSavedLevels(CCObject*);
    void onLeaderboards(CCObject*);
    void onChallenge(CCObject*);
    void onMultiplayer(CCObject*);
    void onDailyLevel(CCObject*);
    void onWeeklyLevel(CCObject*);
    void onGauntlets(CCObject*);
    void onFeaturedLevels(CCObject*);
    void onMapPacks(CCObject*);
    void onOnlineLevels(CCObject*);

    void checkQuestsStatus();
};

class CreatorLayerExt : public CreatorLayer 
{
public:
    void onWorld(cocos2d::CCObject*) {
        auto dir = CCDirector::sharedDirector();
        dir->pushScene(cocos2d::CCTransitionFade::create(0.5, WorldSelectLayer::scene(0)));
    }
};