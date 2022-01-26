#pragma once

#include <cocos2dx/CCLayer.h>

#include "GDAPI_Macros.h"

class ProfilePage : public cocos2d::CCLayer {
public:
    CLASS_MEMBER(cocos2d::CCMenu*, modBadgeMenuThing, 0x1B8);
    CLASS_MEMBER(cocos2d::CCArray*, someArray, 0x220);
};