#pragma once
#include "cocos2d.h"
#include "CCSprite.h"
#include "WorldSelectLayer.h"
#include "GameManager.h"
#include <gd.h>
#include "GDAPI_Macros.h"
#include "GJListLayer.h"
#include "patch.h"
#include "GDPSManager.h"

class CreatorLayer : public cocos2d::CCLayer 
{
public:
    CLASS_MEMBER(cocos2d::CCSprite*, questBtnSpr, 0x134);

public:
    CreatorLayer();
    virtual ~CreatorLayer();
	static CCScene* scene();
	
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

class WorldSelectLayerExt : public WorldSelectLayer
{
public:
    void onGo(cocos2d::CCObject*) {
        auto dir = CCDirector::sharedDirector();
        dir->pushScene(cocos2d::CCTransitionFade::create(0.5, CreatorLayer::scene()));
    }
};



class CreatorLayerExt : public CCLayer
{
public:

	    virtual void keyBackClicked() { this->onBack(nullptr); }
		
		void onBack(cocos2d::CCObject*) {
        auto dir = CCDirector::sharedDirector();
        dir->pushScene(cocos2d::CCTransitionFade::create(0.5, CreatorLayer::scene()));
    }


    void onWorld(cocos2d::CCObject*) {
		
		GDPS->setWorldIsland(1);

        auto dir = CCDirector::sharedDirector();
        dir->pushScene(cocos2d::CCTransitionFade::create(0.5, WorldSelectLayer::scene(0)));
    }
	
	    void onEvent(cocos2d::CCObject*) {
		
		GDPS->setWorldIsland(2);

        auto dir = CCDirector::sharedDirector();
        dir->pushScene(cocos2d::CCTransitionFade::create(0.5, WorldSelectLayer::scene(0)));
    }
	
		void onLists(cocos2d::CCObject*) {
		
		GDPS->setWorldIsland(3);

        auto dir = CCDirector::sharedDirector();
        dir->pushScene(cocos2d::CCTransitionFade::create(0.5, WorldSelectLayer::scene(0)));
    }
	
	 void onSafe(CCObject*)
    {
		    GM->setIntGameVariable("131313", 1);
			
        auto scene = CCScene::create();
        scene->addChild(CreatorLayerExt::create(), 100);

        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f, scene));
    }
	
	bool init() {
		
		  auto director = CCDirector::sharedDirector();
    auto winSize = director->getWinSize();

    auto bg = CCSprite::create("GJ_gradientBG.png");

    bg->setPosition(CCPoint(0, winSize.height / 2));
    bg->setScaleX(winSize.width);
    bg->setScaleY(winSize.height / bg->getContentSize().height);


    bg->setColor(ccc3(0, 0x66, 0xFF));

    this->addChild(bg, -2);

    auto misc = CCMenu::create();
    this->addChild(misc);

    auto m_pButtonMenu = CCMenu::create();
    this->addChild(m_pButtonMenu);

    auto backBtn = CCMenuItemSpriteExtra::create(
            CCSprite::createWithSpriteFrameName("GJ_arrow_01_001.png"),
            CCSprite::createWithSpriteFrameName("GJ_arrow_01_001.png"),
            this,
            menu_selector(WorldSelectLayerExt::onGo)
    );
    backBtn->setPosition((-winSize.width / 2) + 25.0f, (winSize.height / 2) - 25.0f);
    misc->addChild(backBtn);


    auto list = GJListLayer::create(NULL,"The safe",ccc4(255,0,0,0),356,220);

    list->setPosition(ccp(
                              winSize.width/2 - list->getContentSize().width/2,
                              winSize.height/2 - list->getContentSize().height/2
            ));


    auto txt = CCLabelBMFont::create("Nothing to see here...", "bigFont.fnt");
    txt->setPosition(ccp(winSize.width/2, winSize.height/2));
    txt->setScale(0.5);
   // this->addChild(txt);
	
	auto tfisthesafe = CCSprite::create("tfisthesafe.png");
    tfisthesafe->setPosition(ccp(winSize.width/2, winSize.height/2));
	tfisthesafe->setScale(1.5);
	this->addChild(tfisthesafe);


    this->addChild(list);


    this->setTouchEnabled(true);
    this->setKeypadEnabled(true);


return true;
}
CREATE_FUNC(CreatorLayerExt)

};