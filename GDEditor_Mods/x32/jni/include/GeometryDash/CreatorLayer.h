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