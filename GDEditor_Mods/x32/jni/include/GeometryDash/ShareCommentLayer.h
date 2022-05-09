#pragma once

#include <cocos2dx/CCLayer.h>
#include "FLAlertLayer.h"
#include "GJUserscore.h"
#include "CCTextInputNode.h"

#include "GDAPI_Macros.h"

enum CommentType
{
	Fire,
	Ice,
	Poison,
	Shadow,
	Lava,
	Bonus,
	Chaos,
	Demon,
	Time,
};


class ShareCommentLayer : public FLAlertLayer {
public:
   CLASS_MEMBER(CCTextInputNode*, comment, 0x178);
   
    //CLASS_MEMBER(std::string, allowedChars, 0x1FC);
	
public:

	void updateDescText(const char*);
 
};