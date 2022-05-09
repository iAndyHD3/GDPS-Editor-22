#pragma once

#include "FLAlertLayer.h"
#include "LevelEditorLayer.h"
#include "LevelSettingsObject.h"

class LevelSettingsLayer : public FLAlertLayer 
{
public:
    CLASS_MEMBER(CCSprite*, swingOff, 0x2C);
    CLASS_MEMBER(CCSprite*, swingOn, 0x30);


public:
    LevelSettingsLayer();
    virtual ~LevelSettingsLayer();

    static LevelSettingsLayer* create( LevelSettingsObject* a1, LevelEditorLayer* a2 );
	virtual bool init(void);
};