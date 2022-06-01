#include <gd.h>
#include <ColoursPalette.h>
#include "cocos2d.h"
#include "GJGarageLayerExt.h"
#include "AdvancedIconSelect.h"


bool GJGarageLayerExt::init_hk() {
    auto ret = GJGarageLayerExt::init_trp(this);

    auto winsize = CCDirector::sharedDirector()->getWinSize();
	auto dir = CCDirector::sharedDirector();
    {
        auto icons_node = reinterpret_cast<CCNode*>(this->getChildren()->objectAtIndex(6));
        icons_node->setPositionX(winsize.width/2);
        icons_node->setPositionY(icons_node->getPositionY() + 10);
    }
    {
        auto icons_node = reinterpret_cast<CCNode*>(this->getChildren()->objectAtIndex(5));
        icons_node->setPositionX(winsize.width/2);
        icons_node->setPositionY(icons_node->getPositionY() - 15);
    }
    {
        auto icons_node = reinterpret_cast<CCNode*>(this->getChildren()->objectAtIndex(7));
        icons_node->setPositionY(icons_node->getPositionY() - 20);
    }
    {
        auto icons_node = reinterpret_cast<CCNode*>(this->getChildren()->objectAtIndex(8));
        icons_node->setPositionY(icons_node->getPositionY() - 20);
    }
    {
        auto icons_node = reinterpret_cast<CCNode*>(this->getChildren()->objectAtIndex(9));
        icons_node->setPositionY(icons_node->getPositionY() - 20);
    }
    {
        auto icons_node = reinterpret_cast<CCNode*>(this->getChildren()->objectAtIndex(10));
        icons_node->setPositionY(icons_node->getPositionY() - 20);
    }
    {
        auto icons_node = reinterpret_cast<CCNode*>(this->getChildren()->objectAtIndex(11));
        icons_node->setPositionY(icons_node->getPositionY() - 20);
    }
    {
        auto icons_node = reinterpret_cast<CCNode*>(this->getChildren()->objectAtIndex(12));
        icons_node->setPositionY(icons_node->getPositionY() - 20);
    }
    {
        auto icons_node = reinterpret_cast<CCNode*>(this->getChildren()->objectAtIndex(13));
        icons_node->setPositionY(icons_node->getPositionY() - 20);
    }
    {
        auto icons_node = reinterpret_cast<CCNode*>(this->getChildren()->objectAtIndex(14));
        icons_node->setPositionY(icons_node->getPositionY() - 20);
    }
    {
        auto icons_node = reinterpret_cast<CCNode*>(this->getChildren()->objectAtIndex(15));
        icons_node->setPositionY(icons_node->getPositionY() - 20);
    }
    {
        auto icons_node = reinterpret_cast<CCNode*>(this->getChildren()->objectAtIndex(4));
        icons_node->setPositionY(icons_node->getPositionY() - 20);
    }

    {
        auto artBottomL = cocos2d::CCSprite::createWithSpriteFrameName("GJ_sideArt_001.png");
        artBottomL->setPosition(ccp(artBottomL->getScaledContentSize().width/2,artBottomL->getScaledContentSize().height/2));
        this->addChild(artBottomL);
    }
    {
        auto artBottomL = cocos2d::CCSprite::createWithSpriteFrameName("GJ_sideArt_001.png");
        artBottomL->setPosition(ccp(-artBottomL->getScaledContentSize().width/2 + winsize.width,artBottomL->getScaledContentSize().height/2));
        artBottomL->setFlipX(true);
        this->addChild(artBottomL);
    }
    {
        auto palette_menu = CCMenu::create();
        auto paletteSprite = cocos2d::CCSprite::create("GJ_paletteBtn_001.png");
        auto btn = CCMenuItemSpriteExtra::create(
                paletteSprite,
                paletteSprite,
                this,
                static_cast<cocos2d::SEL_MenuHandler>(&GJGarageLayerExt::onPalette)
        );
        palette_menu->addChild(btn);
        btn->setPositionX(-winsize.width/2 + 30);
        this->addChild(palette_menu);
    }
	
	    {
        auto swing_menu = CCMenu::create();
        auto swingSprite = cocos2d::CCSprite::create("swing_off.png");
        auto swing_btn = CCMenuItemSpriteExtra::create(
                swingSprite,
                swingSprite,
                this,
                static_cast<cocos2d::SEL_MenuHandler>(&AdvancedIconSelect::onSwing)
        );
        swing_menu->addChild(swing_btn);
        swing_btn->setPositionX(dir->getScreenLeft() + 173);
		swing_btn->setPositionY(dir->getScreenBottom() + 41);
        this->addChild(swing_menu);
    }
	
		    {
        auto jetpack_menu = CCMenu::create();
        auto jetpackSprite = cocos2d::CCSprite::create("jetpack_off.png");
        auto jetpack_btn = CCMenuItemSpriteExtra::create(
                jetpackSprite,
                jetpackSprite,
                this,
                static_cast<cocos2d::SEL_MenuHandler>(&AdvancedIconSelect::onJetpack)
        );
        jetpack_menu->addChild(jetpack_btn);
        jetpack_btn->setPositionX(dir->getScreenLeft() + 208);
		jetpack_btn->setPositionY(dir->getScreenBottom() + 41);
        this->addChild(jetpack_menu);
    }
	
			    {
        auto old_menu = CCMenu::create();
        auto oldSprite = cocos2d::CCSprite::createWithSpriteFrameName("GJ_infoIcon_001.png");
        auto old_btn = CCMenuItemSpriteExtra::create(
                oldSprite,
                oldSprite,
                this,
                static_cast<cocos2d::SEL_MenuHandler>(&AdvancedIconSelect::onOldIcons)
        );
        old_menu->addChild(old_btn);
        old_btn->setPositionX(dir->getScreenLeft() + 60);
		old_btn->setPositionY(dir->getScreenBottom() + 130);
        this->addChild(old_menu);
    }


    /*
    auto page = GaragePage::create((IconType)7, this, nullptr);
	//page->setScale(3);
    this->addChild(page);
	
    auto array = *((cocos2d::CCArray **)this + 89);
    array->addObject(page);
    this->selectPage((IconType)7);
	*/

    
    //->addObject(page);
    /*
     v63 = (cocos2d::CCObject *)GaragePage::create(6, (int)this, (int)GJGarageLayer::onSpiderIcon, 0);
  (*(void (__fastcall **)(GJGarageLayer *, cocos2d::CCObject *, int))(*(_DWORD *)this + 224))(this, v63, 100);
  cocos2d::CCArray::addObject(*((cocos2d::CCArray **)this + 89), v63);
    */

    return ret;
}

void GJGarageLayerExt::onPalette(CCObject *sender) {
    ColoursPalette::create(this)->show();
}
