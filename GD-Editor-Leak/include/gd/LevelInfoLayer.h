#pragma once

#include "CCLayer.h"
#include "LevelFeatureLayer.h"
#include "GJAccountManager.h"

class LevelInfoLayer : public cocos2d::CCLayer 
{
public:

GJAccountManager* accmanager;

public:
    LevelInfoLayer();
    virtual ~LevelInfoLayer();

    void onRate( cocos2d::CCObject* ref );
    void onRateStarsMod( cocos2d::CCObject* ref );

    void onPlay( cocos2d::CCObject* ref );
    void onPlayReplay( cocos2d::CCObject* ref );
	void onRequest(CCObject* ref);
	void onCompleted(cocos2d::extension::CCHttpClient *sender, cocos2d::extension::CCHttpResponse *response);
};