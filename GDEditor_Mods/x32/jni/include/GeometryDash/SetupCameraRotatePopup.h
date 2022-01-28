#pragma once
#include "GDAPI_Macros.h"
#include "Slider.h"
#include <cocos2dx/CCLayer.h>
#include <cocos2dx/CCNode.h>


class SetupCameraRotatePopup : public cocos2d::CCLayerColor
{
public:

    CLASS_MEMBER(CCNode*, moveTimeInput, 0x1E8);
	CLASS_MEMBER(CCNode*, slider, 0x1EC);
	CLASS_MEMBER(Slider*, ccslider, 0x1B8);

public:
    SetupCameraRotatePopup();
    virtual ~SetupCameraRotatePopup();
	void onClose(CCObject*);
	void sliderDegreesChanged(CCObject*);
	void sliderChanged(CCObject*);

    bool init( );
};