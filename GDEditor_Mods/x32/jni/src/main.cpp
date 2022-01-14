#include "cocos2d.h"
#include <jni.h>
#include <dlfcn.h>
#include "blaze.h"
#include "Logger.h"
#include "patch.h"
#include "hooks/MenuLayerExt.h"
#include "hooks/MoreSearchLayerExt.h"
#include "hooks/EditLevelLayerExt.h"
#include "hooks/LevelEditorLayerExt.h"
#include "hooks/MultiplayerLayerExt.h"
#include "hooks/EditorUIExt.h"
#include "hooks/PauseLayerExt.h"
#include "hooks/PlayLayerExt.h"
#include "hooks/MoreOptionsLayerExt.h"
#include "hooks/GJGarageLayerExt.h"
#include "hooks/AccountRegisterLayerExt.h"
#include "hooks/onRobtopExt.h"
#include "hooks/onFacebookExt.h"
#include "GDPSManager.h"
#include "layers/GDPSSettings.h"
#include <gd.h>
#include <hooking.h>
#include <CCFileUtils.h>
#include "../Encryption/Encryption.h"
#include "../ZLIB/zlib.h"
#include <string>
#include <iostream>


using namespace std;


#define null NULL
#define targetLibName ("libcocos2dcpp.so")

patch *playTest = new patch();
patch *pauseBtn = new patch();

template < class T>
	void *getPointer(T value)
	{
		auto val = reinterpret_cast< void *&> (value);
		return val;
	}

void *getPointerFromSymbol(void *handle, const char *symbol)
{
	return reinterpret_cast<void*> (dlsym(handle, symbol));
}

extern bool inEditor;

void(*v_trp)(int a1, int a2, int a3, int a4);
void v_hk(int a1, int a2, int a3, int a4)
{
	LOGD("Enter!");
	if (inEditor)
	{
		clippingRect(a1, a2, 1000, 1000);
	}
	else
	{
		clippingRect(a1, a2, a3, a4);
	}
}


#include <cstdlib>

inline long mid_num(const std::string& s) {
    return std::strtol(&s[s.find('_') + 1], nullptr, 10);
}

GameObject* creata_hk( int key )
{
    auto tb = ObjectToolbox::sharedState( )->intKeyToFrame( key );
    
    // LOGD("GAMEOBJECT: %s", tb);
    if( strstr(tb, "pixelart") != NULL && strstr(tb, "b_001") == NULL )
    {
        auto pixelKey = mid_num( tb );
        // LOGD("ART: %i", pixelKey);

        return old4( pixelKey > 38 ? 1 : key );
    }

    if( !strcmp( tb, "pixelb_03_01_001.png" ) )
        return old4( 1 );

    if ( !strcmp( tb, "pixelb_03_02_001.png" ) )
        return old4( 1 );


    if( strstr( tb, "gdh" ) != NULL 
    || strstr( tb, "secretCoin" ) != NULL 
    || strstr( tb, "fireball" ) != NULL 
    || strstr( tb, "fire_b" ) != NULL 
    || strstr( tb, "gj22_anim" ) != NULL 
    || strstr( tb, "pixel" ) != NULL 
    || strstr( tb, "gjHand2" ) != NULL )
        return old4( 1 );

    auto o = old4( key );
    
    return o;
}

int prevRelease = -1;
void(*release_trp)(PlayerObject *self, int button);
void release_hk(PlayerObject *self, int button)
{
	if (prevRelease == 5)
	{
		prevRelease = button;
		return;
	}

	prevRelease = button;
	release_trp(self, button);
}

char const * (*loading_trp)(LoadingLayer*);
char const* loading_hook(LoadingLayer *layer)
{
	auto gdpsmanager = GDPSManager::sharedState();
	auto gm = GameManager::sharedState();
	
	
			gm->setGameVariable("11000", true);


	gdpsmanager->playTest = GameManager::sharedState()->getGameVariable("100001");
	gdpsmanager->pauseBtn = GameManager::sharedState()->getGameVariable("100005");

	if (!gdpsmanager->playTest)
	{
		playTest->Modify();
	}
	
		if (gdpsmanager->pauseBtn)
	{
		pauseBtn->Modify();
	}
	
	
	
/* 	 	auto crashfix = gm->getGameVariable("100004");
	
	if(!crashfix) {
				patch *tmp = new patch();
			tmp->addPatch("libcocos2dcpp.so", 0x44D2AE, "00 bf 00 bf"); // editor fix, breaks levels

			tmp->Modify();
	}else{
						patch *tmp = new patch();

					tmp->addPatch("libcocos2dcpp.so", 0x7A617F, "47 4a 5f 63 72 65 61 74 65 42 74 6e 5f 30 30 32"); // editor fix, breaks levels
			tmp->Modify();
			

			
			
		}
 */
	return loading_trp(layer);
}

void (*dict)( CCDictionary*, CCObject*, int);
void dict_hk( cocos2d::CCDictionary* d, CCObject* obj, int key )
{
	
	//LOGD("%s", obj, key);
	
    switch(key)
    {
    case 0x7DF: // add if statement for string check
        return dict( d, CCString::create( "edit_eRotateBtn_001.png" ), key );
        break;

    case 0x778:
        return dict( d, CCString::create( "edit_eAdvRandomBtn_001.png" ), key );
        break;

    case 0x7E0:
        return dict( d, CCString::create( "edit_eGuideBtn_001.png" ), key );
        break;

    case 0xA8D:
        return dict( d, CCString::create( "edit_ePauseMoverBtn_001.png" ), key );
        break;
		
	case 0xA8E:
        return dict( d, CCString::create( "edit_eResumeComBtn_001.png" ), key );
        break;

    case 0x80E:
        return dict( d, CCString::create( "edit_eEdgeBtn_001.png" ), key );
        break;

    default:

        dict( d, obj, key );
        break;
    }

}

bool isGauntlet = false;

CCSpriteFrame* (*old5)(CCSpriteFrameCache*, const char*) = nullptr;
CCSpriteFrame* sprite_hk( CCSpriteFrameCache* ptr, const char* s )
{
    // LOGD("SPRITE: %s", s);


    if( !strcmp( s, "GJ_fullBtn_001.png" )  )
        return old5( ptr, "GJ_creatorBtn_001.png" );
    
    if( !strcmp( s, "GJ_freeStuffBtn_001.png" )  )
        return old5( ptr, "GJ_dailyRewardBtn_001.png" );

    if( !strcmp( s, "GJ_freeLevelsBtn_001.png" )  )
        return old5( ptr, "GJ_moreGamesBtn_001.png" );

    if ( !strcmp( s, "GJ_gauntletsBtn_001.png" ) )
    {
        if( !isGauntlet )
        {
            isGauntlet = true;
            return old5( ptr, "GJ_versusBtn_001.png" );
        }
        {
            isGauntlet = false;
            return old5( ptr, "GJ_gauntletsBtn_001.png" );
        }
    }

    return old5( ptr, s );
}

void(*save_trp)(void*);
void save_hook(void *self)
{
	GDPSManager::sharedState()->save();
	return save_trp(self);
}

void OptionsLayer::onGDPSSettings(CCObject *sender)
{
	GDPSManager::sharedState()->isGDPSSettings = true;
	MoreOptionsLayer::create()->show();
}

void(*ol_customSetup_trp)(OptionsLayer *layer);
void OptionsLayer_customSetup_hk(OptionsLayer *layer)
{
	ol_customSetup_trp(layer);
	CCMenu *m = *((CCMenu **) layer + 116);
	CCMenuItemSpriteExtra *btn = dynamic_cast<CCMenuItemSpriteExtra*> (m->getChildren()->objectAtIndex(2));
	btn->setPositionX(-80);

	auto gdpsSetting = ButtonSprite::create("GDPS Settings", 125, 10, 10, 1);
	auto myButton = CCMenuItemSpriteExtra::create(
		gdpsSetting,
		gdpsSetting,
		layer,
		menu_selector(OptionsLayer::onGDPSSettings)
		);
			auto button = CCSprite::createWithSpriteFrameName("GJ_optionsBtn02_001.png");
	auto myButton1 = CCMenuItemSpriteExtra::create(
		button,
		button,
		layer,
		menu_selector(VideoOptionsLayer::onAdvanced)
	);
	myButton1->setPosition(-140, -55);

	myButton->setPositionX(80);
	m->addChild(myButton);
	m->addChild(myButton1);

}

int(*onToggleTrampoline)(void *pthis, const char *val);
void hook_onToggle(void *pthis, const char *val)
{
	int v = atoi(val);

	onToggleTrampoline(pthis, val);

	if (v > 100000)
	{
		if (v == 100001)
		{
			GDPS->playTest = !GDPS->playTest;
			if (!GDPS->playTest)
			{
				playTest->Modify();
			}
			else
			{
				playTest->Restore();
			}
		}

		if (v == 100002)
		{
			GDPSManager::sharedState()->oldTextures = !GDPSManager::sharedState()->oldTextures;
			GM->reloadAll(false, false, true);
			GM->setGameVariable("100002", GDPSManager::sharedState()->oldTextures);
		}
		
/* 		if (v == 100003)
		{
			//GM->reloadAll(true, true, true);
			GM->setGameVariable("100003", GDPSManager::sharedState()->cleanMenu);
		}
 */
		if (v == 100004)
		{
			GM->reloadAll(false, false, true);
		}		
		
		if (v == 100005)
		{
			GDPS->pauseBtn = !GDPS->pauseBtn;
			if (GDPS->pauseBtn)
			{
				pauseBtn->Modify();
			}
			else
			{
				pauseBtn->Restore();
			}
		}
	
	}
}

void(*CCFileUtils_addSearchPath_trp)(CCFileUtils *self, const char *searchpath);
void CCFileUtils_addSearchPath_hk(CCFileUtils *self, const char *searchpath)
{
	CCLog("HELLO!!!");
	CCFileUtils_addSearchPath_trp(self, searchpath);
	if (GDPSManager::sharedState()->oldTextures)
	{
		auto fileUtils = CCFileUtils::sharedFileUtils();
		fileUtils->removeAllPaths();
		CCFileUtils_addSearchPath_trp(self, "assets/oldtp/");
		CCFileUtils_addSearchPath_trp(self, "assets/");
		CCFileUtils_addSearchPath_trp(self, searchpath);
	}
}

void(*dataLoaded_trp)(GameManager *self, DS_Dictionary *a1);
void GameManager_dataLoaded_hk(GameManager *self, DS_Dictionary *a1)
{
	dataLoaded_trp(self, a1);

	self->setGameVariable("100002", GDPSManager::sharedState()->oldTextures);
	if (GDPSManager::sharedState()->oldTextures)
	{
		CCFileUtils *fileUtils = CCFileUtils::sharedFileUtils();
		auto vect = fileUtils->getSearchPaths();
		fileUtils->removeAllPaths();
		fileUtils->addSearchPath("assets/");
		dataLoaded_trp(self, a1);
		fileUtils->removeAllPaths();
		fileUtils->addSearchPath("assets/oldtp/");
		fileUtils->addSearchPath("assets/");
	}
}

void *(*t_trp)(void *a1, const char *func);
void *t(void *a1, const char *func)
{
	LOGD("%s", func);
	return t_trp(a1, func);
}

cocos2d::_ccColor3B(*PlayerObject_updateGlowColortrp)(int value);
cocos2d::_ccColor3B PlayerObject_updateGlowColorhook(int value)
{
	return ccc3(255, 0, 0);

}

cocos2d::_ccColor3B(*GameManager_colorForIdx_trp)(GameManager *pthis, int value);
cocos2d::_ccColor3B GameManager_colorForIdx_hook(GameManager *pthis, int value)
{
	switch (value)
	{
		case 0:
			return ccc3(125, 255, 0);
		case 1:
			return ccc3(0, 255, 0);
		case 2:
			return ccc3(0, 255, 125);
		case 3:
			return ccc3(0, 255, 255);
		case 4:
			return ccc3(0, 125, 255);
		case 5:
			return ccc3(0, 0, 255);
		case 6:
			return ccc3(125, 0, 255);
		case 7:
			return ccc3(255, 0, 255);
		case 8:
			return ccc3(255, 0, 125);
		case 9:
			return ccc3(255, 0, 0);
		case 10:
			return ccc3(255, 125, 0);
		case 11:
			return ccc3(255, 255, 0);
		case 12:
			return ccc3(255, 255, 255);
		case 13:
			return ccc3(185, 0, 255);
		case 14:
			return ccc3(255, 185, 0);
		case 15:
			return ccc3(0, 0, 0);
		case 16:
			return ccc3(0, 200, 255);
		case 17:
			return ccc3(175, 175, 175);
		case 18:
			return ccc3(90, 90, 90);
		case 19:
			return ccc3(255, 125, 125);
		case 20:
			return ccc3(0, 175, 75);
		case 21:
			return ccc3(0, 125, 125);
		case 22:
			return ccc3(0, 75, 175);
		case 23:
			return ccc3(75, 0, 175);
		case 24:
			return ccc3(125, 0, 125);
		case 25:
			return ccc3(175, 0, 75);
		case 26:
			return ccc3(175, 75, 0);
		case 27:
			return ccc3(125, 125, 0);
		case 28:
			return ccc3(75, 175, 0);
		case 29:
			return ccc3(255, 75, 0);
		case 30:
			return ccc3(150, 50, 0);

		case 31:
			return ccc3(150, 100, 0);
		case 32:
			return ccc3(100, 150, 0);
		case 33:
			return ccc3(0, 150, 100);
		case 34:
			return ccc3(0, 100, 150);
		case 35:
			return ccc3(100, 0, 150);
		case 36:
			return ccc3(150, 0, 100);
		case 37:
			return ccc3(150, 0, 0);
		case 38:
			return ccc3(0, 150, 0);
		case 39:
			return ccc3(0, 0, 150);
		case 40:
			return ccc3(125, 255, 175);
		case 41:
			return ccc3(125, 125, 255);

		case 42:
			return ccc3(255, 215, 215);
		case 43:
			return ccc3(115, 0, 0);
		case 44:
			return ccc3(95, 0, 0);
		case 45:
			return ccc3(60, 0, 0);
		case 46:
			return ccc3(130, 80, 80);
		case 47:
			return ccc3(130, 50, 50);
		case 48:
			return ccc3(85, 40, 40);
		case 49:
			return ccc3(190, 255, 225);
		case 50:
			return ccc3(140, 255, 225);
		case 51:
			return ccc3(0, 255, 200);
		case 52:
			return ccc3(55, 160, 125);
		case 53:
			return ccc3(50, 110, 95);
		case 54:
			return ccc3(40, 85, 70);
		case 55:
			return ccc3(0, 100, 100);
		case 56:
			return ccc3(0, 70, 70);

		case 57:
			return ccc3(255, 185, 110);
		case 58:
			return ccc3(255, 160, 60);
		case 59:
			return ccc3(160, 100, 60);
		case 60:
			return ccc3(115, 70, 50);

		case 61:
			return ccc3(125, 75, 55);
		case 62:
			return ccc3(80, 50, 30);
		case 63:
			return ccc3(100, 50, 30);
		case 64:
			return ccc3(75, 30, 0);
		case 65:
			return ccc3(150, 255, 255);
		case 103:
			return ccc3(0, 0, 115);
		case 104:
			return ccc3(0, 10, 85);
		case 66:
			return ccc3(0, 70, 110);
		case 67:
			return ccc3(0, 55, 80);
		case 68:
			return ccc3(0, 40, 60);
		case 69:
			return ccc3(115, 190, 255);
		case 70:
			return ccc3(115, 190, 255);
		case 71:
			return ccc3(75, 126, 180);
		case 72:
			return ccc3(50, 80, 115);
		case 73:
			return ccc3(255, 255, 74);
		case 74:
			return ccc3(255, 255, 130);
		case 75:
			return ccc3(255, 255, 130);
		case 76:
			return ccc3(255, 225, 155);
		case 77:
			return ccc3(80, 50, 10);
		case 78:
			return ccc3(200, 165, 110);
		case 79:
			return ccc3(170, 125, 80);
		case 80:
			return ccc3(110, 80, 55);

		case 81:
			return ccc3(190, 180, 255);
		case 82:
			return ccc3(190, 125, 255);
		case 83:
			return ccc3(60, 0, 150);
		case 84:
			return ccc3(60, 0, 100);
		case 85:
			return ccc3(80, 80, 155);
		case 86:
			return ccc3(110, 70, 180);
		case 87:
			return ccc3(90, 50, 125);
		case 88:
			return ccc3(70, 40, 100);
		case 89:
			return ccc3(200, 255, 170);
		case 90:
			return ccc3(210, 255, 100);
		case 91:
			return ccc3(210, 255, 50);
		case 92:
			return ccc3(0, 100, 0);
		case 93:
			return ccc3(0, 60, 0);
		case 94:
			return ccc3(255, 175, 255);
		case 95:
			return ccc3(75, 0, 50);
		case 96:
			return ccc3(255, 125, 255);
		case 97:
			return ccc3(175, 85, 180);
		case 98:
			return ccc3(135, 60, 135);
		case 99:
			return ccc3(100, 50, 100);
		case 105:
			return ccc3(110, 0, 60);
		case 100:
			return ccc3(225, 225, 225);
		case 101:
			return ccc3(125, 125, 125);
		case 102:
			return ccc3(65, 65, 65);

		default:
			return ccc3(255, 255, 255);
	}
}

// hook ProfilePage 

void* (*profilePage_trp)(CCLayer*, GJUserScore*);
void* profilePage_hook(CCLayer* self, GJUserScore* userData) {
	
	auto ret = profilePage_trp(self, userData);
	int modBadgeLevel = userData->modBadge_;
	
	if (modBadgeLevel > 2) {
		auto layer = (CCLayer*)self->getChildren()->objectAtIndex(0);
		
		for(int c = 0 ; c < layer->getChildrenCount(); c++) {
		auto modBadgeSpr = (CCSprite*)layer->getChildren()->objectAtIndex(c);
		
		
		if(modBadgeSpr->getChildrenCount() == 0) {
			if(modBadgeSpr->getPositionX() > 180 && modBadgeSpr-> getPositionY() == 284) {
				
				#include <sstream>  
				
				stringstream ss;
				
				ss<<modBadgeLevel;
				
				std::string SmodBadge;
				ss>>SmodBadge;
				
				auto spriteCache = CCSpriteFrameCache::sharedSpriteFrameCache();

				spriteCache->addSpriteFramesWithFile("GJ_GameSheet03-hd.plist");
				spriteCache->addSpriteFramesWithFile("GJ_GameSheet03.plist");
				
				std::string modpng = "modBadge_02_001.png";
				
				std::string modFrame = modpng.replace(11,1,SmodBadge);
				
				const char* finalSprite = modFrame.c_str();

	auto finalSprite2 = spriteCache->spriteFrameByName(finalSprite);
 
				modBadgeSpr->setDisplayFrame(finalSprite2);
			}
		}
	}
}
return ret;
}

void *(*CreatorLayer_init_trp)(LevelSettingsLayer *pthis, LevelSettingsObject *a2, LevelEditorLayer *a3);
void *CreatorLayer_init_hook(LevelSettingsLayer *pthis, LevelSettingsObject *a2, LevelEditorLayer *a3)
{
	auto ret = CreatorLayer_init_trp(pthis, a2, a3);
	

	return ret;
}


void *(*SetupRotatePopupLayer_trp)(CCLayerColor* self, CCObject* object1, CCObject* object2);
void *SetupRotatePopupLayer_hook(CCLayerColor* self, CCObject* object1, CCObject* object2)
{
	auto ret = SetupRotatePopupLayer_trp(self, object1, object2);
	

	return ret;
}

	
bool(*GaragLayer_init_trp)(CCLayer *pthis);
bool GaragLayer_init_hook(CCLayer *pthis)
{
	auto res = GaragLayer_init_trp(pthis);


	auto winsize = CCDirector::sharedDirector()->getWinSize();
	{
		auto icons_node = reinterpret_cast<CCNode*> (pthis->getChildren()->objectAtIndex(6));
		icons_node->setPositionX(winsize.width / 2);
		icons_node->setPositionY(icons_node->getPositionY() + 10);
	}

	{
		auto icons_node = reinterpret_cast<CCNode*> (pthis->getChildren()->objectAtIndex(5));
		icons_node->setPositionX(winsize.width / 2);
		icons_node->setPositionY(icons_node->getPositionY() - 15);
	}

	{
		auto icons_node = reinterpret_cast<CCNode*> (pthis->getChildren()->objectAtIndex(7));
		icons_node->setPositionY(icons_node->getPositionY() - 20);
	}

	{
		auto icons_node = reinterpret_cast<CCNode*> (pthis->getChildren()->objectAtIndex(4));
		icons_node->setPositionY(icons_node->getPositionY() - 20);
	}

	{
		auto artBottomL = cocos2d::CCSprite::createWithSpriteFrameName("GJ_sideArt_001.png");
		artBottomL->setPosition(ccp(artBottomL->getScaledContentSize().width / 2, artBottomL->getScaledContentSize().height / 2));
		pthis->addChild(artBottomL);
	}

	{
		
		auto artBottomL = cocos2d::CCSprite::createWithSpriteFrameName("GJ_sideArt_001.png");
		artBottomL->setPosition(ccp(-artBottomL->getScaledContentSize().width / 2 + winsize.width, artBottomL->getScaledContentSize().height / 2));
		artBottomL->setFlipX(true);
		pthis->addChild(artBottomL);
	}

	{
		auto palette_menu = CCMenu::create();
		auto paletteSprite = cocos2d::CCSprite::create("GJ_paletteBtn_001.png");
		auto btn = CCMenuItemSpriteExtra::create(
			paletteSprite,
			paletteSprite,
			pthis,
			nullptr	//static_cast<cocos2d::SEL_MenuHandler>(&ColoursPalette::onColorClick)
	);
		palette_menu->addChild(btn);
		btn->setPositionX(-winsize.width / 2 + 30);
		pthis->addChild(palette_menu);
	}

	//GJ_sideArt_001.png

	return res;
}

extern void lib_entry();

void loader()
{
	auto cocos2d = dlopen(targetLibName != "" ? targetLibName : NULL, RTLD_LAZY);
	//auto libShira = dlopen("libgdkit.so", RTLD_LAZY);

	//color doesnt update but well there it is
	//HookManager::do_hook(getPointerFromSymbol(cocos2d,"_ZN12PlayerObject15updateGlowColorEv"), (void*) PlayerObject_updateGlowColorhook,(void **)&PlayerObject_updateGlowColortrp);

	HookManager::do_hook(getPointerFromSymbol(cocos2d, "_ZN11GameManager11colorForIdxEi"), (void*) getPointer(&GameManager_colorForIdx_hook), (void **) &GameManager_colorForIdx_trp);

	//this hooks didnt really work well, here to test other things faster, having hooks ready
	//HookManager::do_hook(getPointerFromSymbol(cocos2d,"_ZN18LevelSettingsLayer4initEP19LevelSettingsObjectP16LevelEditorLayer"), (void*) getPointer(&onFacebookExt::init_hk), (void **) &onFacebookExt::init_trp);
	
	//HookManager::do_hook(getPointerFromSymbol(cocos2d, "_ZN14LevelInfoLayer4initEP11GJGameLevelb"), (void*) getPointer(&onRobtopExt::init_hk), (void **) &onRobtopExt::init_trp);
	
	HookManager::do_hook(getPointerFromSymbol(cocos2d, "_ZN13GJGarageLayer4initEv"), (void*) getPointer(&GJGarageLayerExt::init_hk), (void **) &GJGarageLayerExt::init_trp);
	//crash? ._.
	
	//HookManager::do_hook(getPointerFromSymbol(cocos2d, "_ZN22SetupCameraRotatePopup4initEP16EffectGameObjectPN7cocos2d7CCArrayE"), (void**) &SetupRotatePopupLayer_trp, (void *) &SetupRotatePopupLayer_trp);
	
	
	//HookManager::do_hook(getPointerFromSymbol(cocos2d, "_ZN11ProfilePage20loadPageFromUserInfoEP11GJUserScore"), (void**) &profilePage_trp, (void *) &profilePage_hook);

	HookManager::do_hook(getPointerFromSymbol(cocos2d, "_ZN20AccountRegisterLayer4initEv"), (void*) getPointer(&AccountRegisterLayerExt::init_hk), (void **) &AccountRegisterLayerExt::init_trp);

	HookManager::do_hook(getPointerFromSymbol(cocos2d, "_ZN7cocos2d11CCFileUtils13addSearchPathEPKc"), (void*) CCFileUtils_addSearchPath_hk, (void **) &CCFileUtils_addSearchPath_trp);
	HookManager::do_hook(getPointerFromSymbol(cocos2d, "_ZN11GameManager10dataLoadedEP13DS_Dictionary"), (void*) &GameManager_dataLoaded_hk, (void **) &dataLoaded_trp);

	//_ZN12LoadingLayer4initEb this is real loading layer, _ZN12LoadingLayer15loadingFinishedEv seems like its actually when you transition into menu layer
	HookManager::do_hook(getPointerFromSymbol(cocos2d, "_ZN12LoadingLayer15loadingFinishedEv"), (void*) loading_hook, (void **) &loading_trp);
	
	//HookManager::do_hook(getPointerFromSymbol(cocos2d, "_ZN7cocos2d12CCDictionary9setObjectEPNS_8CCObjectEi"), (void*) dict_hk, (void **) &dict);
	//HookManager::do_hook(getPointerFromSymbol(cocos2d, "_ZN7cocos2d18CCSpriteFrameCache17spriteFrameByNameEPKc"), (void*) sprite_hk, (void **) &old5);
	
	//HookManager::do_hook((void*) &clippingRect_hk, (void*) v_hk, (void **) &v_trp);
	//to here
	HookManager::do_hook((void*) &menu_hk, getPointer(&MenuLayerExt::init_hk), (void **) &MenuLayerExt::init_trp);
	
	HookManager::do_hook(getPointerFromSymbol(cocos2d, "_ZN16MultiplayerLayer4initEv"), (void*) getPointer(&MultiplayerLayerExt::init_hk), (void **) &MultiplayerLayerExt::init_trp);


	
	//HookManager::do_hook(getPointerFromSymbol(cocos2d, "_ZN8EditorUIC2Ev"), (void*) getPointer(&EditorUIExt::EditorUI_hk), (void **) &EditorUIExt::EditorUI_trp);
	//HookManager::do_hook(getPointerFromSymbol(cocos2d, "_ZN16LevelEditorLayer4initEP11GJGameLevel"), (void*) getPointer(&LevelEditorLayerExt::init_hk), (void **) &LevelEditorLayerExt::init_trp);
	
	
//HookManager::do_hook(getPointerFromSymbol(cocos2d, "_ZN10GameObject13createWithKeyEi"), (void*) getPointer(&creata_hk), (void **) &old4);

	
	//HookManager::do_hook(getPointerFromSymbol(cocos2d, "_ZN14EditLevelLayer6onBackEPN7cocos2d8CCObjectE"), (void*) getPointer(&EditLevelLayerExt::onBack_hk), (void **) &EditLevelLayerExt::onBack_trp);

	HookManager::do_hook((void*) &pause_hk, getPointer(&PauseLayerExt::init_hk), (void **) &PauseLayerExt::init_trp);

	
	HookManager::do_hook(getPointerFromSymbol(cocos2d, "_ZN9PlayLayer6updateEf"), getPointer(&PlayLayerExt::update_hk), (void **) &PlayLayerExt::update_trp);
	
	
	HookManager::do_hook(getPointerFromSymbol(cocos2d, "_ZN11AppDelegate11trySaveGameEb"), (void*) save_hook, (void **) &save_trp);

	HookManager::do_hook(getPointerFromSymbol(cocos2d, "_ZN12OptionsLayer11customSetupEv"), (void*) OptionsLayer_customSetup_hk, (void **) &ol_customSetup_trp);

	HookManager::do_hook(getPointerFromSymbol(cocos2d, "_ZN16MoreOptionsLayer9addToggleEPKcS1_S1_"), getPointer(&MoreOptionsLayerExt::addToggle_hk), (void **) &MoreOptionsLayerExt::addToggle_trp);
	HookManager::do_hook(getPointerFromSymbol(cocos2d, "_ZN11GameManager18toggleGameVariableEPKc"), (void*) hook_onToggle, (void **) &onToggleTrampoline);
	
	
	//HookManager::do_hook(
	//getPointerFromSymbol(cocos2d, "_ZN12PlayerObject13releaseButtonE12PlayerButton"), (void*) release_hk, (void **) &release_trp, true);

	//239A60

	patch *tmp = new patch();

 	//EC34
	//patch *shiraPTH = new patch();
	//shiraPTH->addPatch("libgdkit.so", 0xEC34, "F0 B5 03 AF 2D E9");



	//shiraPTH->Modify();
	//HookManager::do_hook(getPointer(&gdmk::get_proc_addr), (void*) t, (void **) &t_trp);
	//lib_entry();
	//LOGD("TTTTT!");
 
	//2E9914
	 tmp->addPatch("libcocos2dcpp.so", 0x2E9914, "6f f0 01 00 70 47");
	tmp->addPatch("libcocos2dcpp.so", 0x2ECC64, "00 bf");
	//tmp->addPatch("libcocos2dcpp.so", 0x2B1F52, "00 bf 00 bf 00 bf 00 bf");
	//tmp->addPatch("libcocos2dcpp.so", 0x2B1F92, "00 bf");
	
	
	//tmp->addPatch("libcocos2dcpp.so", 0x007A617F, "47 4a 5f 63 72 65 61 74 65 42 74 6e 5f 30 30 32"); //GJ_createBtn_001.png -> GJ_createBtn_002.png
	
	
	

/*
************************************
	this patch fixes all the editor crashes, however levels like expurgation with a lot of triggers crash
	tmp->addPatch("libcocos2dcpp.so", 0x44D2AE, "00 bf 00 bf");
	*/
		tmp->addPatch("libcocos2dcpp.so", 0x44D2AE, "00 bf 00 bf");
	/*
	
	
	//this patch restores the bytes to the original values, breaking the editor but fixing the levels crash
	tmp->addPatch("libcocos2dcpp.so", 0x44D2AE, "D7 F7 B5 FF"); // editor fix, breaks levels
			
************************************
*/


	//patch refresh

	tmp->addPatch("libcocos2dcpp.so", 0x2388EE, "00 20");
	 tmp->addPatch("libcocos2dcpp.so", 0x2388DC, "00 20");

	//playtest try
	
	tmp->addPatch("libcocos2dcpp.so", 0x288A3E, "00 bf"); 
	tmp->addPatch("libcocos2dcpp.so", 0x28EB70, "00 bf 00 bf");
	


	//fix level too short
	tmp->addPatch("libcocos2dcpp.so", 0x241ADA, "00 bf");
	tmp->addPatch("libcocos2dcpp.so", 0x241B04, "00 bf 00 bf");
	tmp->addPatch("libcocos2dcpp.so", 0x241B14, "00 bf 00 bf");

	//10 stars limit bypass
	tmp->addPatch("libcocos2dcpp.so", 0x2F8E5A, "04 e0");

	//tmp->addPatch("libgdkit.so", 0xDC02, "00 bf");
	//tmp->addPatch("libgdkit.so", 0xD284, "00 bf");
	
	
	//fps, levl info nop, applied patch to lib directly
	//tmp->addPatch("libgdkit.so", 0x00E2C8, "30 30 30 30");
	//tmp->addPatch("libgdkit.so", 0x00E2D0, "30 30 30 30");

	//  remove pause change speed	//
	//tmp->addPatch("libgdkit.so", 0xE5DA, "00 bf");
	//tmp->addPatch("libgdkit.so", 0xE618, "00 bf");
	//tmp->addPatch("libgdkit.so", 0xE65C, "00 bf");
	
	

	tmp->addPatch("libcocos2dcpp.so",0x2EA824,"00 bf");

	
	
	

	
	
	tmp->addPatch("libcocos2dcpp.so", 0x7A402E, "73 77 6e 31 31");
	tmp->addPatch("libcocos2dcpp.so", 0x7A4041, "73 77 6e 31 31");
	tmp->addPatch("libcocos2dcpp.so", 0x7A406E, "73 77 6e 31 31");
	tmp->addPatch("libcocos2dcpp.so", 0x7A4056, "73 77 6e 31 31");

	//package for save
	//tmp->addPatch("libcocos2dcpp.so", 0x785011, "67 65 6f 6d 65 74 72 79 6a 75 6d 70 74 65 73 74");

	tmp->Modify();

	playTest->addPatch("libcocos2dcpp.so", 0x2ABFF6, "00 bf");
	tmp->addPatch("libcocos2dcpp.so", 0x7896A9, "31");
	pauseBtn->addPatch("libcocos2dcpp.so", 0x7896A9, "32");


//pthread_exit(reinterpret_cast<void*> (0));

}

   JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *reserved)
{
	//init_handle();
	pthread_t t;
	pthread_create(&t, NULL,
		reinterpret_cast< void *(*)(void*) > (loader), NULL);
	return JNI_VERSION_1_6;
}   
 
 
//(?=.*playlayer)(?=.*init)