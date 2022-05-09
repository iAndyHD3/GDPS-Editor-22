#pragma once

#include "cocos2d.h"

#include "GDAPI_Macros.h"

class CCTextInputNode : public cocos2d::CCLayer {
public:
    CLASS_MEMBER(cocos2d::CCLabelBMFont*, placeholderLabel, 0x174);
	
public:
	void setString(std::string);
	void setAllowedChars(std::string);
	void setLabelNormalColor(cocos2d::_ccColor3B);
};