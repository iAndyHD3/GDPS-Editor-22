#include <ColoursPalette.h>
#include <sstream>
#include "../cocos2dx/extensions/network/HttpClient.h"
#include "../cocos2dx/extensions/network/HttpRequest.h"
#include "../cocos2dx/extensions/network/HttpResponse.h"
#include "cocos2d.h"
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "patch.h"
#include "KittyMemory.h"
#include "../Encryption/Encryption.h"
#include "../ZLIB/zlib.h"
#include "../GDPSManager.h"
#include "../obfuscate.h"
#include "../layers/advancedOptionsLayer.h"
#include "../layers/CreditsLayer.h"
#include "../layers/ToolsLayer.h"
#include "../../include/hooks/MenuLayerExt.h"


template<class T>
extern void* getPointer(T value);
		
void MenuLayerExt::onRequestCompleted(cocos2d::extension::CCHttpClient *sender, cocos2d::extension::CCHttpResponse *response){
        CCLog("Completed!");

        if (!response)
        {
            CCLog("onHttpRequestCompleted - No Response");
            return;
        }

        CCLog("onHttpRequestCompleted - Response code: %lu", response->getResponseCode());

        if (!response->isSucceed())
        {
            CCLog("onHttpRequestCompleted - Response failed");
            CCLog("onHttpRequestCompleted - Error buffer: %s", response->getErrorBuffer());
            return;
        }
        CCLog("onHttpRequestCompleted - Response code: %s", response->getResponseHeader());

        std::vector<char> *buffer = response->getResponseData();
        GameToolbox * gameToolbox = new GameToolbox();
        auto resp = GameToolbox::getResponse(response);
		auto gm = GameManager::sharedState();

        CCLog("%s",resp.c_str());

        rapidjson::Document parsedFromString;

        parsedFromString.Parse<0>(resp.c_str());

        CCLog("%d",parsedFromString["version"].GetInt());

        int ver = parsedFromString["version"].GetInt();
        int particles = parsedFromString["particles"].GetInt();
		string weight = parsedFromString["weight"].GetString();
		string date = parsedFromString["date"].GetString();
		string changelog = parsedFromString["changelog"].GetString();
		
		gm->setIntGameVariable("11001", particles);
		
		

        if(ver > version2){
        //FLAlertLayer::create(nullptr, "New update!", "New update!\n<cg>Download</c> the new update in the discord server\n Join using the <co>join discord!</c> button",  "OK", nullptr, 400, false, 300)->show();
		MenuLayerExt::showUpdateAlert(GDPS->itos(ver), weight, date, changelog);
        }
		
			//I dont think I will use this but it can be funny to troll or something XDD
		
		 switch(particles) {
			 
			 
			
			case 1: 
			this->addChild(CCParticleFire::create());
			break;
			case 2:
			this->addChild(CCParticleFireworks::create());
			break;
			case 3:
			this->addChild(CCParticleSun::create());
			break;
			case 4:
			this->addChild(CCParticleGalaxy::create());
			break;
			case 5:
			this->addChild(CCParticleFlower::create());
			break;
			case 6:
			this->addChild(CCParticleMeteor::create());
			case 7:
			this->addChild(CCParticleSpiral::create());
			break;
			case 8:
			this->addChild(CCParticleExplosion::create());
			break;
			case 9:
			this->addChild(CCParticleSmoke::create());
			break;
			case 10:
			      CCLog("should have added snow?!");
			this->addChild(CCParticleSnow::create());
			break;
			case 11:
			this->addChild(CCParticleRain::create());
			case 12:
			this->addChild(CCParticleSnow::create());
			this->addChild(CCParticleSmoke::create());
		 }
		 
		 GM->setGameVariable("11000", false);
			

		} 
	

 	void MenuLayerExt::showUpdateAlert(string version, string weight, string date, string changelog) {
		
		string v = "";
		for(int i = 0; i < 4; i++) {
			v = v + version[i];
			if(i < 3) v = v + ".";
		}
		
		
	string description = "Version: " + v + "\nRelease Date: " + date + "\nSize: " + weight + " MB" + "\n\n\Changelog:\n" + changelog + "\n\nWould you like to download the new update?";
		
	alert = FLAlertLayer::create(nullptr, "New update!", description.c_str(),  "NO", nullptr, 400, true, 300);
			
		auto menu = alert->m_pButtonMenu;
		auto okBtn = reinterpret_cast<CCNode*>(menu->getChildren()->objectAtIndex(0));
	
		auto sprite = ButtonSprite::create("Yes",50,10,10,5);
		auto btn = CCMenuItemSpriteExtra::create(sprite, sprite, this, menu_selector(MenuLayerExt::onDownload));
		menu->addChild(btn);


		GameToolbox::alignItemsHorisontally(menu->getChildren(), 15, okBtn->getPosition(), false);
	
	alert->show();
	

	}

		

    void MenuLayerExt::onDownload(CCObject* sender){

        auto app = cocos2d::CCApplication::sharedApplication();
        auto url = ("http://game.gdpseditor.com/server/game/download.php");

        app->openURL(url);
    }
	
	    void MenuLayerExt::onJoinDiscord(CCObject* sender){

        auto app = cocos2d::CCApplication::sharedApplication();
        auto url = ("http://game.gdpseditor.com/server/game/discord.php");

        app->openURL(url);
    }




    void MenuLayerExt::onProgressChanged(CCObject *sender){
        auto value = reinterpret_cast<SliderThumb*>(sender)->getValue();
        CCLog("%f",value);
    }



    void MenuLayerExt::onBlaze(CCObject* sender){

		//MenuLayerExt::showUpdateAlert();
    }
	
	
	void onPopupTest(CCObject* sender){
	//crash :v
	advancedOptionsLayer::create()->show();
    }
	

	
	

		
		
		


    static inline bool (*init_trp)(MenuLayer * self);
    bool MenuLayerExt::init_hk(){

        auto ret =  init_trp(this);
		
	extern bool addBadges;
	addBadges = true;
	
		auto director = CCDirector::sharedDirector();
		auto dir = CCDirector::sharedDirector();
        auto winSize = director->getWinSize();
		auto gm = GameManager::sharedState();
		
		/*//auto gradient = CCLayerGradient::create(ccc4(255, 0, 0, 0), ccc4(255, 0, 0, 0));
		auto gradient = CCLayerGradient::create(ccc4(255, 255, 0, 255), ccc4(0, 0, 255, 255));
		gradient->setPosition(CCRIGHT / 2, CCTOP / 2);
		//gradient->initWithColor(ccc4(59, 255, 240, 1), ccc4(241, 0, 255, 1));
		this->addChild(gradient,10000000000);
		gradient->init();
		
		auto levelFix = GM->getGameVariable("100004");
		
		auto platformer = CCSprite::createWithSpriteFrameName("Attack_Btn.png");
		platformer->setPosition({CCMIDX, CCMIDY + 50 });
		this->addChild(platformer);
		
		auto platformer2 = CCSprite::createWithSpriteFrameName("Attack_Btn_Dwn.png");
		platformer2->setPosition({CCMIDX + 100, CCMIDY + 50 });
		this->addChild(platformer2);
		
				auto platformer3 = CCSprite::createWithSpriteFrameName("Jump_Btn.png");
		platformer3->setPosition({CCMIDX, CCMIDY - 20});
		this->addChild(platformer3);
		
		
				auto platformer4 = CCSprite::createWithSpriteFrameName("Jump_Btn_Dwn.png");
		platformer4->setPosition({CCMIDX + 100, CCMIDY - 20});
		this->addChild(platformer4);
	*/
		auto menuClear = GM->getGameVariable("100003");

        auto btn = ButtonSprite::create("Support Blaze!",80,10,10,1);
        auto myButton = CCMenuItemSpriteExtra::create(
                btn,
                btn,
                this,
                menu_selector(MenuLayerExt::onBlaze)
        );
        auto bottomMenu =  CCMenu::create();
        reinterpret_cast<CCSprite*>(bottomMenu)->setPositionY(90);


		 auto label22 = CCLabelBMFont::create("Version 2.2.1.3", "chatFont.fnt");
		//auto label22 = CCLabelBMFont::create("Version 2.2.1.2", "chatFont.fnt");
		if(GM->getGameVariable("100004")) {
			
	label22->setPosition(CCPoint(dir->getScreenRight() - 80, dir->getScreenTop() - 10));
	//label22->setPosition(CCPoint(dir->getScreenRight() - 200, dir->getScreenTop() - 10));
		} else {
			
		 label22->setPosition(CCPoint(dir->getScreenRight() - 55, dir->getScreenTop() - 10));
		 //label22->setPosition(CCPoint(dir->getScreenRight() - 200, dir->getScreenTop() - 10));
		}
    label22->setAnchorPoint({ 0, 0 });
    label22->setScale(.5);
	
	auto label33 = CCLabelBMFont::create("Beta 5", "chatFont.fnt");
		if(GM->getGameVariable("100004")) {
			
	label33->setPosition(CCPoint(dir->getScreenRight() - 80, dir->getScreenTop() - 20));
	//label33->setPosition(CCPoint(dir->getScreenRight() - 200, dir->getScreenTop() - 10));
		} else {
			
		 label33->setPosition(CCPoint(dir->getScreenRight() - 55, dir->getScreenTop() - 20));
		 //label33->setPosition(CCPoint(dir->getScreenRight() - 200, dir->getScreenTop() - 10));
		}
    label33->setAnchorPoint({ 0, 0 });
    label33->setScale(.5);

	auto menu = CCMenu::create();
	
	auto btn2 = CCSprite::createWithSpriteFrameName("GJ_createBtn_001.png");
        auto myButton2 = CCMenuItemSpriteExtra::create(
                btn2,
                btn2,
                this,
				menu_selector(CreatorLayer::onMyLevels)
              //menu_selector(OptionsLayer::onVideo)
        );
		btn2->setScale(.7);
        auto bottomMenu2 =  CCMenu::create();
		bottomMenu2->addChild(myButton2);
        reinterpret_cast<CCSprite*>(bottomMenu2)->setPosition({CCRIGHT - 50, CCBOTTOM + 45 });
		
		
		auto btn4 = CCSprite::createWithSpriteFrameName("communityCreditsBtn_001.png");
		auto myButton4 = CCMenuItemSpriteExtra::create(
                btn4,
                btn4,
                this,
                menu_selector(CreditsLayer::create)
        );
        auto bottomMenu4 =  CCMenu::create();
        reinterpret_cast<CCSprite*>(bottomMenu4)->setPosition({winSize.width / 2 + 113, CCBOTTOM + 45 });
		btn4->setScale(1.4);
        bottomMenu4->addChild(myButton4);
		
		

		
				auto btn5 = CCSprite::createWithSpriteFrameName("toolsBtn_001.png");
		btn5->setScale(1.2);
		auto myButton5 = CCMenuItemSpriteExtra::create(
                btn5,
                btn5,
                this,
                menu_selector(ToolsLayer::create)
        );
				        auto bottomMenu5 =  CCMenu::create();       
        reinterpret_cast<CCSprite*>(bottomMenu5)->setPosition({winSize.width / 2 - 113, CCBOTTOM + 45 });
        bottomMenu5->addChild(myButton5);
		
	//auto glview = cocos2d::CCEGLView::sharedOpenGLView();
	//glview->setDesignResolutionSize(winSize.width + 1000, winSize.height + 100, kResolutionNoBorder);
	//messing with this is funny
	
		auto btn3 = CCSprite::createWithSpriteFrameName("GJ_optionsBtn02_001.png");
        auto myButton3 = CCMenuItemSpriteExtra::create(
                btn3,
                btn3,
                this,
                menu_selector(VideoOptionsLayer::onAdvanced)
        );
        auto bottomMenu3 =  CCMenu::create();
        reinterpret_cast<CCSprite*>(bottomMenu3)->setPosition(CCPoint(winSize.width - 22, winSize.height - 35));
	if(!menuClear) {
				bottomMenu->addChild(myButton);
		        bottomMenu3->addChild(myButton3);

		       // this->addChild(bottomMenu, 100);
		        this->addChild(bottomMenu2, 100);
		        this->addChild(bottomMenu3, 100);
				this->addChild(bottomMenu4);
				this->addChild(bottomMenu5);
				this->addChild(label22);
				this->addChild(label33);

	}
	
        {
            auto gm = GameManager::sharedState();

          
			auto m_nPlayerJetpack = gm->getIntGameVariable("7001");
			gm->m_nPlayerSwing = gm->getIntGameVariable("6969");
			
			
			if(m_nPlayerJetpack == 0){
				gm->setIntGameVariable("7001", 1);
			}
		if(gm->m_nPlayerSwing == 0) {
			gm->m_nPlayerSwing = 1;
		}
			GDPS->setPlayerSwing(gm->m_nPlayerSwing);
			GDPS->setPlayerJetpack(m_nPlayerJetpack);
			
/*

			auto numReq = gm->getGameVariable("11000");
			
			
			if(numReq) {
				
		

     cocos2d::extension::CCHttpRequest* request = new (std::nothrow) cocos2d::extension::CCHttpRequest();
        request->setUrl(AY_OBFUSCATE("http://game.gdpseditor.com/server/game/version2.php"));
        request->setRequestType(cocos2d::extension::CCHttpRequest::kHttpGet);


        request->setResponseCallback(this,callfuncND_selector(MenuLayerExt::onRequestCompleted));
        request->setTag("Post test2");
        *((int *)request + 8) = 1;
        //*((int *)request + 16) = 0;
        cocos2d::extension::CCHttpClient::getInstance()->send(request);
        request->release();  
    
		gm->setGameVariable("11000", false);
		
		
	
			}else{
				
				auto particles = gm->getIntGameVariable("11001");
				
				switch(particles) {
			
			case 1: 
			this->addChild(CCParticleFire::create());
			break;
			case 2:
			this->addChild(CCParticleFireworks::create());
			break;
			case 3:
			this->addChild(CCParticleSun::create());
			break;
			case 4:
			this->addChild(CCParticleGalaxy::create());
			break;
			case 5:
			this->addChild(CCParticleFlower::create());
			break;
			case 6:
			this->addChild(CCParticleMeteor::create());
			case 7:
			this->addChild(CCParticleSpiral::create());
			break;
			case 8:
			this->addChild(CCParticleExplosion::create());
			break;
			case 9:
			this->addChild(CCParticleSmoke::create());
			break;
			case 10:
			this->addChild(CCParticleSnow::create());
			break;
			case 11:
			this->addChild(CCParticleRain::create());
			case 12:
			this->addChild(CCParticleSnow::create());
			this->addChild(CCParticleSmoke::create());
		 }
		 
			}
*/





        return ret;
    };
	
}
	
	
	











/*
server adresses

http://ps.fhgdps.com/GDPSEditor22

0x7A8513
0x7A8941	
0x7A8C21	
0x7A8CB0	
0x7A8D5C	
0x7A8DE7	
0x7A8DE7	
0x7A8DE7	
0x7A8EAA	
0x7A8EE5	
0x7A8F53	
0x7A8FCC	
0x7A9054	
0x7A90BB	
0x7A9107	
0x7A914B	
0x7A918A	
0x7A91D3	
0x7A922C	
0x7A92A4	
0x7A9353	
0x7A93A3	
0x7A93FA	
0x7A94A0	
0x7B7A1D	
0x7B8191
0x7B8202	
0x7B8278	
0x7B8446	
0x7B8A5D	
0x7B8A99	
*/