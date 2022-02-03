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
#define version2 2209
#include "../Encryption/Encryption.h"
#include "../ZLIB/zlib.h"
#include "../GDPSManager.h"
#include "../obfuscate.h"
#include "../layers/advancedOptionsLayer.h"
#include "../layers/CreditsLayer.h"
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
		
		gm->setIntGameVariable("11001", particles);
		
		

        if(ver > version2){
        FLAlertLayer::create(nullptr, "New update!", "New update!\n<cg>Download</c> the new update in the discord server\n Join using the <co>join discord!</c> button",  "OK", nullptr, 400, false, 300)->show();

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
	
 


		

    void MenuLayerExt::onDownload(CCObject* sender){

        auto app = cocos2d::CCApplication::sharedApplication();
        auto url = ("https://ps.fhgdps.com/GDPSEditor22/game/latest.php");

        app->openURL(url);
    }



    void MenuLayerExt::onProgressChanged(CCObject *sender){
        auto value = reinterpret_cast<SliderThumb*>(sender)->getValue();
        CCLog("%f",value);
    }



    void MenuLayerExt::onBlaze(CCObject* sender){

        auto app = cocos2d::CCApplication::sharedApplication();
        auto url = ("https://www.youtube.com/channel/UCcfPtuop90e_JzxPkiZ6Q5Q");

        app->openURL(url);	
    }
	
	
	void onPopupTest(CCObject* sender){
	//crash :v
	advancedOptionsLayer::create()->show();
    }
	
	

		
		
		


    static inline bool (*init_trp)(MenuLayer * self);
    bool MenuLayerExt::init_hk(){

        auto ret =  init_trp(this);
		

		auto director = CCDirector::sharedDirector();
		auto dir = CCDirector::sharedDirector();
        auto winSize = director->getWinSize();
		auto gm = GameManager::sharedState();
		
		auto levelFix = GM->getGameVariable("100004");
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

/*
	std::string levelSubstring = "H4sIAAAAAAAAC6VY27HdIAxsyDcjAeIx-UoNtwAXkBZSfAwCDBbCJ5Of46NdsYDAsuD3t40Hng5Oc6Kh056G6ETkh-EHg-78wtOfCABnOPFEyj_xhDOe-AfPIgHmMwn8f4m0lMg-3OAjEXPm9tpYWAbeRGgrAp-NxKsi_zgltxA5fv9Ce0B-ED88P9xx_fL_wEh9xPz4tqlYpvyyQCF-ufLLLAI_8ICfeFxNzGEiHfbwlxmzRdlCyqy_bIvZdtS82b4YPPL4O-yecBazgcUG-JqaORxk_CIvCzN4YXR3XMzI_Q5NqcPdy2MVGjrIcBkNgsCDxEPHA02mW3vhc0g8Bgm7jbeYF3srsJhfKPG7Fq7Zttgk_HzBjcBTGVt6dsd43hAP3Cu43fqToq_hYpzRlHF6gZOCR4nTrZOo2bSef22v4HKerLPAzRYX8686Eo9b3Cg6Ejfr-CZcxzE5iYcbTzTZs-6Ak4KLuNRxiLgzLudTcRGXikfRb-hZ4zadmPWdBRBvAG3JUzlfJsgwQsKKXyny6rk0z7nWpAMjHDnJ_gAKJvsVM4-oJD-T26Opb7U_vhLU3tGU4HxdvxR6VkQTRvSRX1sb7G1KMm6NjGtwGJ290JpoK2gaadjSQWHDXjtoI5toreugdF0CaEEJILN2y_otmxSWF6F2XBdB0n5P2z2dFJqGrrVwV22V9ns6fUQra9nENdruafiEVjZh1dZYv2XTB6y2QducNdruadDoK52MeyXZKXM4s8sclcV1Lmis7YllgpXwNxp6qxGWsSua3vYCc7DxmcIrLkqh5g8lbVs7Yr4n7gG9viazJJdRIyDqKPR-6KQASVaSdHsG6nYSwx5wUfA1YUVXw8W3DINZl8AY6DGVEDXP2D5_a0KUDY1ICiELhUr0yrvaovRuymL6wazDy7PUcBn2GhVFf-FvhH-ZaJSHAcblaYDxxQkp42lRKTMBe0LUeJVYLEol5DJWQi58JeRWqYTE5cvMuNzNw7Q1ndWsFyeNMIQj9hcx2SegHGpa7OOzMwPrRa-4eAcrLlJW0xFhbIQIfCPEUjVCLG4lZGAaIWpkA_1Q1cpShuMEP74jjZ4GEAe5ifAeMoW9fGfJ4RbAYDt6tP4Rt_3jcCSJg_8ckeBs4crblu8q_GECLDxM2Tb5kqN4jEw_66pt_T0txSMtlrFydrWSjVuc6zq3OCPOXL6FoblwqLzrC-HWfHjhF-e8WTv3ndsq_YcPfNx-DmT3Y6RVwpy4N-39-Mg3n-eOofS227yZdtvKg952nY9vuy70U7TwgJvnV86FCZlezXBfBQ62TG9hfWllQlh-k6u_o26vj-cmwlo3ritDE72Cr0uyqi--9VV_gcvSi259Of6kfA7S4vORoCxd4uUHO2KxYs3_WlpeJHawgG8O7s0hfOSATnVAeHOwbw5ecajX0u3KMOd9lxG-bB4RB6l8Tm1-ffl4UKSdf3p6l_pXBAvQr37mxbL1WlcSodVGD0DzlMVMI4Y0_xdEvc3Y8xkAAA==";

			std::string decodeBase64 = Encryption::Base64::Decode(levelSubstring, true);
			std::string decodeZLib = Encryption::ZLib::Inflate(decodeBase64, Encryption::ZLib::Format::GZIP);


const char * level = decodeZLib.c_str();

		auto labellevel = CCLabelBMFont::create(level, "chatFont.fnt");
		labellevel->setPosition(dir->getScreenRight() / 2, dir->getScreenTop() - 80);
		labellevel->setScale(1);
		this->addChild(labellevel, 10);
*/

		 //auto label22 = CCLabelBMFont::create("Version 2.2.0.8 Beta 3 V1", "chatFont.fnt");
		auto label22 = CCLabelBMFont::create("Version 2.2.0.9", "chatFont.fnt");
		if(GM->getGameVariable("100004")) {
			
	label22->setPosition(CCPoint(dir->getScreenRight() - 80, dir->getScreenTop() - 10));
	//label22->setPosition(CCPoint(dir->getScreenRight() - 200, dir->getScreenTop() - 10));
		} else {
			
		 label22->setPosition(CCPoint(dir->getScreenRight() - 55, dir->getScreenTop() - 10));
		 //label22->setPosition(CCPoint(dir->getScreenRight() - 200, dir->getScreenTop() - 10));
		}
    label22->setAnchorPoint({ 0, 0 });
    label22->setScale(.5);
	
	auto label33 = CCLabelBMFont::create("Beta 4", "chatFont.fnt");
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
        );
		btn2->setScale(.7);
        auto bottomMenu2 =  CCMenu::create();
		bottomMenu2->addChild(myButton2);
        reinterpret_cast<CCSprite*>(bottomMenu2)->setPosition({winSize.width / 2 + 240, winSize.height - 280 });
		
		
		auto btn4 = CCSprite::createWithSpriteFrameName("communityCreditsBtn_001.png");
		//auto btn4 = CCSprite::createWithSpriteFrameName("GJ_infoBtn_001.png");
		//btn4->setColor(ccc3(255,0,0));
		auto myButton4 = CCMenuItemSpriteExtra::create(
                btn4,
                btn4,
                this,
                menu_selector(CreditsLayer::create)
        );
        auto bottomMenu4 =  CCMenu::create();
        reinterpret_cast<CCSprite*>(bottomMenu4)->setPosition({winSize.width / 2 + 110, winSize.height - 275});
		btn4->setScale(1.4);
        bottomMenu4->addChild(myButton4);
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

		        this->addChild(bottomMenu, 100);
		        this->addChild(bottomMenu2, 100);
		        this->addChild(bottomMenu3, 100);
				this->addChild(bottomMenu4);
				this->addChild(label22);
				//this->addChild(label33);

	}
        {
            auto gm = GameManager::sharedState();

          
			auto m_nPlayerJetpack = gm->getIntGameVariable("7001");
			
			GDPS->setPlayerSwing(gm->m_nPlayerSwing);
			GDPS->setPlayerJetpack(m_nPlayerJetpack);
			


			auto numReq = gm->getGameVariable("11000");
			
			
			if(numReq) {
				
				

     cocos2d::extension::CCHttpRequest* request = new (std::nothrow) cocos2d::extension::CCHttpRequest();
        request->setUrl(AY_OBFUSCATE("http://game.gdpseditor.com/server/game/version.php"));
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


/*
const char* server = AY_OBFUSCATE("http://gmdpseditor.7m.pl/database");
const char* server_b64 = AY_OBFUSCATE("aHR0cDovL2dtZHBzZWRpdG9yLjdtLnBsL2RhdGFiYXNlCg==");
*/
const char* server = AY_OBFUSCATE("http://game.gdpseditor.com/server");
const char* server_b64 = AY_OBFUSCATE("aHR0cDovL2dhbWUuZ2Rwc2VkaXRvci5jb20vc2VydmVy");

		GDPS->changeServers(server, server_b64);


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