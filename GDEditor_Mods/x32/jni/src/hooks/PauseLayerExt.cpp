#include <dlfcn.h>
#include "blaze.h"
#include "cocos2d.h"
#include "PauseLayerExt.h"
#include "GDPSManager.h"
#include "patch.h"
#include "gd.h"

class SliderThumb {
public:
    float getValue();
};


bool PauseLayerExt::init_hk() {

    auto ret = init_trp(this);

    this->firstPage = CCArray::create();


	
    for(int k = 0; k < this->getChildrenCount(); k++){
        this->firstPage->addObject(this->getChildren()->objectAtIndex(k));
    }

    this->showPage(0);


    return ret;
}



CCMenu * getPageControl(CCLayer * layer){

}



void PauseLayerExt::onNextPage(CCObject *sender) {
    showPage(1);

}

void PauseLayerExt::onPrevPage(CCObject *sender) {
    showPage(0);
}

void PauseLayerExt::showPage(int page) {
    this->removeAllChildren();
    this->addPageControl();

    auto winSize = CCDirector::sharedDirector()->getWinSize();

    this->addChild(reinterpret_cast<CCMenu*>(firstPage->objectAtIndex(0)));


    if(page == 0){
        for(int k = 1; k < firstPage->count(); k++){
            this->addChild(reinterpret_cast<CCMenu*>(firstPage->objectAtIndex(k)));
        }
    }

    if(page == 1){
		/*
        auto manager = GDPSManager::sharedState();


        auto title = CCLabelBMFont::create("Other settings", "bigFont.fnt");
        title->setPosition(ccp(winSize.width/2,winSize.height - 30));
        this->addChild(title);


        auto txt = CCLabelBMFont::create("Platform opacity", "bigFont.fnt");
        txt->setScale(0.5);
        auto sl = Slider::create(this,menu_selector(PauseLayerExt::onPlatformOpacity),1);

        CCLog("%d", GDPSManager::sharedState()->opacity );
        float value = (float)manager->opacity / (float)255;
        sl->setValue(value);
        txt->setPosition(ccp(winSize.width/2 - 100,winSize.height/2 + 100));
        sl->setPosition(ccp(winSize.width/2 - 100,winSize.height/2 + 80));
        this->addChild(txt);
        this->addChild(sl);*/
    }
}

void PauseLayerExt::onPlatformOpacity(CCObject *sender) {
    auto value = reinterpret_cast<SliderThumb*>(sender)->getValue();
    GDPSManager::sharedState()->opacity = 255 * value;
    CCLog("%d", GDPSManager::sharedState()->opacity );
}

void PauseLayerExt::addPageControl() {
    auto winSize = CCDirector::sharedDirector()->getWinSize();

    auto misc = CCMenu::create();

    auto sp = CCSprite::createWithSpriteFrameName("GJ_arrow_01_001.png");
    auto backBtn = CCMenuItemSpriteExtra::create(
            sp,
            sp,
            this,
            menu_selector(PauseLayerExt::onPrevPage));

    auto sp2 = CCSprite::createWithSpriteFrameName("GJ_arrow_01_001.png");
    sp2->setFlipX(1);
    auto nextbtn = CCMenuItemSpriteExtra::create(
            sp2,
            sp2,
            this,
            menu_selector(PauseLayerExt::onNextPage));

		auto manager = GDPSManager::sharedState();

		auto dir = CCDirector::sharedDirector();
        //auto title = CCLabelBMFont::create("Other settings", "bigFont.fnt");
        //title->setPosition(ccp(winSize.width/2,winSize.height - 30));
        //this->addChild(title);


        auto txt = CCLabelBMFont::create("Platformer opacity", "bigFont.fnt");
        txt->setScale(0.4);
        auto sl = Slider::create(this,menu_selector(PauseLayerExt::onPlatformOpacity),1);

        CCLog("%d", GDPSManager::sharedState()->opacity );
        float value = (float)manager->opacity / (float)255;
        sl->setValue(value);
        txt->setPosition({winSize.width / 2 - 200, winSize.height / 2 + 60});
		sl->setScale(.6);
        sl->setPosition({winSize.width / 2 - 320, winSize.height / 2 - 18});
        this->addChild(txt);
        this->addChild(sl);


    nextbtn->setPosition((+ winSize.width / 2) - 50, 0);
    backBtn->setPosition((- winSize.width / 2) + 50, 0);

    misc->addChild(backBtn);
    misc->addChild(nextbtn);
	

    //this->addChild(misc);
}


