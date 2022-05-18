#pragma once

#include <cocos2dx/CCLayer.h>
#include "FLAlertLayer.h"
#include "GJUserscore.h"
#include "CCTextInputNode.h"
#include "TextArea.h"
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
   CLASS_MEMBER(CCTextInputNode*, comment, 0x43B40000); //descartados: 178, 24, 1F0
   CLASS_MEMBER(CCTextInputNode*, comment2, 0x1D8);
   CLASS_MEMBER(CCTextInputNode*, comment3, 0xE0);
   
    //CLASS_MEMBER(std::string, allowedChars, 0x1FC);
	
public:

	void updateDescText(const char*);
	void onClose(CCObject*);
	void onShare(CCObject*);
	void onPerecnt(CCObject*);
	void updatePercentLabel();
	void updateCharCountLabel();
	void textInputClosed(CCTextInputNode*);
	void textChanged(CCTextInputNode*);
	
	void custom() {
		//auto comment = reinterpret_cast<CCTextInputNode*>(this->m_pLayer->getChildren()->objectAtIndex(4));

	this->updateDescText("€€€€€");
	}
	
		void custom2() {
		this->_comment2()->setString("Hello");
	}
	
		void custom3() {
		this->_comment3()->setString("Hello");
	}
	
 
};