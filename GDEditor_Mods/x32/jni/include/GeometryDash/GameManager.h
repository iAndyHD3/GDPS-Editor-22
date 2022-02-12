#pragma once

#include "CCNode.h"
#include "GManager.h"
#include "MenuLayer.h"
#include "GameRateDelegate.h"
#include "GJBaseGameLayer.h"
#include "LevelEditorLayer.h"
#include "PlayLayer.h"
#include "GDAPI_Macros.h"

#include <stdlib.h>

class LevelSelectLayer;
class GJShopLayer;
class DailyLevelPage;

enum IconType
{
    Player,
    Ship,
    Ball,
    Bird,
    Dart,
    Robot,
    Spider,
    Swing,
    Jetpack,
};

enum LastGameScene
{
    Menu,
    Creator,
    MyLevels,
    Info,
    LevelBrowser = 7,
    WorldSelect = 9,
    SecretLayer2 = 12,
};

class __attribute__( (packed, aligned( 4 )) ) GameManager : public GManager
{
public:
    bool m_bSwitchModes;
    bool m_bToFullscreen;
    bool m_bReloading;
    bool m_bUnknown;
    PAD(4);
    cocos2d::CCDictionary* m_pValueKeeper;
    cocos2d::CCDictionary* m_pUnlockValueKeeper;
    cocos2d::CCDictionary* m_pCustomObjectDict;
    PAD(4);
    double m_dUnknown;
    PAD(16);
    double m_dUnknown2;
    //PAD(8);   // tolto per funzionare con android!
    bool m_bLoaded; //?
    std::string m_sUnknown;
    PlayLayer* m_pPlayLayer;
    PAD(24);
    std::string m_sPlayerUDID;
    std::string m_sPlayerName;
    bool m_bCommentsEnabled;
    int m_nPlayerUserIDRand1;
    int m_nPlayerUserIDRand2;
    int m_nPlayerUserID;
    float m_fBackgroundMusicVolume;
    float m_fEffectsVolume;
    int m_nTimeOffset;
    PAD(28);
    PAD(36)
    int m_nPlayerFrameRand1;
    int m_nPlayerFrameRand2;
    int m_nPlayerFrame;
    int m_nPlayerShipRand1;
    int m_nPlayerShipRand2;
    int m_nPlayerShip;
    int m_nPlayerBallRand1;
    int m_nPlayerBallRand2;
    int m_nPlayerBall;
    int m_nPlayerBirdRand1;
    int m_nPlayerBirdRand2;
    int m_nPlayerBird;
    int m_nPlayerDartRand1;
    int m_nPlayerDartRand2;
    int m_nPlayerDart;
    int m_nPlayerRobotRand1;
    int m_nPlayerRobotRand2;
    int m_nPlayerRobot;
    int m_nPlayerSpiderRand1;
    int m_nPlayerSpiderRand2;
    int m_nPlayerSpider;
    int m_nPlayerSwingRand1;
    int m_nPlayerSwingRand2;
    int m_nPlayerSwing;
    int m_nPlayerColorRand1;
    int m_nPlayerColorRand2;
    int m_nPlayerColor;
    int m_nPlayerColor2Rand1;
    int m_nPlayerColor2Rand2;
    int m_nPlayerColor2;
    int m_nPlayerStreakRand1;
    int m_nPlayerStreakRand2;
    int m_nPlayerStreak;
    int m_nPlayerDeathEffectRand1;
    int m_nPlayerDeathEffectRand2;
    int m_nPlayerDeathEffect;
    PAD(8);
    int m_nSecretNumberRand1; //? may be named differently
    int m_nSecretNumberRand2;
    PAD(12) //need to check
    bool m_bPlayerGlow;
    int m_nPlayerIconType;
    bool m_bUnknown2;
    bool m_bShowSongMarkers;
    bool m_bShowBPMMarkers;
    bool m_bRecordGameplay;
    bool m_bShowProgressBar;
    bool m_bPerformanceMode;
    bool m_bClickedGarage;
    bool m_bClickedEditor;
    bool m_bClickedName;
    bool m_bClickedPractice;
    bool m_bShowedEditorGuide;
    bool m_bShowedRateDiffDialog;
    bool m_bShowedRateStarDialog;
    bool m_bShowedLowDetailDialog;
    PAD(48);
    int m_nBootups;
    bool m_bHasRatedGame;
    PAD(3);
    bool m_bGameCenterEnabled;
    bool m_bSmoothFix;
    PAD(16);
    int m_nResolution;
    cocos2d::TextureQuality m_eQuality; //more after that i havent re'd
	bool inEditor_; // 0x1AA
	    LevelEditorLayer* editorLayer; // 0x15C

    int playerFrame2; // 0x1B8
    int playerFrame1; // 0x1BC
    int playerFrame_; // 0x1C0
    int shipFrame2; // 0x1C4
    int shipFrame1; // 0x1C8
	
	    int primaryColorID_2; // 0x218
    int primaryColorID_1; // 0x21C
    int primaryColorID_;  // 0x220
    int secondaryColorID_2; // 0x224
    int secondaryColorID_1; // 0x228

public:
    CLASS_MEMBER(int, playerSwingSeed, 0x20C);
    CLASS_MEMBER(int, playerSwingRand, 0x210);
    CLASS_MEMBER(int, playerSwing, 0x214);

    CLASS_MEMBER(LastGameScene, lastScene, 0x1AC);

// missing funcs
public:
    void setPlayerSwing(int ID) {
        _playerSwing() = ID;
        
        // not sure how rand is calculated
    }

public:
    GameManager();
    virtual ~GameManager();

    static GameManager* sharedState( );

    bool getGameVariable( const char* g_var );
    void setGameVariable( const char* g_var, bool toggle );
	
	void setIntGameVariable(const char* variable, int valor);
int getIntGameVariable(const char* variable);


    bool hasRatingPower( );
    void setHasRatingPower( int ratingPower );

    void addGameAnimation( int animationID, int animationType, float duration, std::string animationName, std::string animationColorName );

    cocos2d::ccColor3B colorForIdx( int id );
    void reloadAll(bool ,bool,bool );
    void setPlayerColor(int);
    void setPlayerColor2(int);
	void setPlayerShip(int);
	void setPlayerJetpack(int);
	void setPlayerFrame(int);
	void resetAllIcons();
};

#define GM GameManager::sharedState()
#define PL GameManager::sharedState()->playLayer_