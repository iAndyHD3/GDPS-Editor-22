#pragma once

#include <cocos2dx/CCLayer.h>

class MenuLayer : public cocos2d::CCLayer 
{
public:
    MenuLayer();
    virtual ~MenuLayer();
	  static cocos2d::CCScene* scene(bool);

    bool init( );
};