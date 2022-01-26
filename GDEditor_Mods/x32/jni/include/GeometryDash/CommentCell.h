#pragma once

#include <cocos2dx/CCLayer.h>

#include "GDAPI_Macros.h"

class GJComment : public cocos2d::CCObject {
public:
    CLASS_MEMBER(int, modBadge, 0x124);
};

// not fucking sure if this is a CCLayer but im not even gonna bother it doesnt matter
class CommentCell : public cocos2d::CCLayer {
public:
    CLASS_MEMBER(cocos2d::CCMenu*, menu, 0x16C);
};