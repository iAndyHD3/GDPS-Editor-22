#pragma once

#include "LevelEditorLayer.h"
#include "TextInputDelegate.h"
#include "UploadActionDelegate.h"
#include "UploadPopupDelegate.h"
#include "SetIDPopupDelegate.h"
#include "UploadActionPopup.h"
#include "GameManager.h"
#include "GameSoundManager.h"

#include "GDAPI_Macros.h"

// size 0x15C
class EditLevelLayer : public cocos2d::CCLayer, TextInputDelegate, FLAlertLayerProtocol, UploadActionDelegate, UploadPopupDelegate, SetIDPopupDelegate
{
public:
    cocos2d::CCMenu* btnMenu_; // 0x13C
    GJGameLevel* gameLevel_;
    cocos2d::CCArray* placeholderInput_;
    cocos2d::CCLabelBMFont* folderLabel_;
    bool isPlaying_;
    bool lowDetailMode_;
    int levelType_;
	bool inEditorLayer;
    std::string levelName_;
    UploadActionPopup* uploadPopup_;
	    unsigned char _pad1[ 0x24 ];
    GJGameLevel* level; // 0x140
    cocos2d::CCArray* a1; // 0x144
    cocos2d::CCArray* a2; // 0x148

public:
    CLASS_MEMBER(cocos2d::CCMenu*, btnMenu, 0x13C);

public:
    EditLevelLayer();
    virtual ~EditLevelLayer();

    static EditLevelLayer* create( GJGameLevel* level );

    void closeTextInputs( );
    void verifyLevelName( );

    virtual void keyBackClicked( void );

public:
    void onEditCustom(cocos2d::CCObject*) {
        if(!this->isPlaying_) {
            closeTextInputs();

            this->isPlaying_ = true;

           GM->_lastScene() = LastGameScene::Info;

            verifyLevelName();

            GSM->playBackgroundMusic( this->gameLevel_->getAudioFileName(), false, true, false );
            auto dir = cocos2d::CCDirector::sharedDirector( );
            auto scene = cocos2d::CCTransitionFade::create( 
                0.5, 
                LevelEditorLayer::scene( this->gameLevel_ ) );

            dir->pushScene( scene );
        }
    }
};