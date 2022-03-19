#pragma once

#include "cocos2d.h"
#include "gd.h"
#include "obfuscate.h"


class ToolsLayer : public CCLayer {
	
public:
    bool init();
	
	    virtual void keyBackClicked() { this->onBack(nullptr); }

	    void onBack(CCObject*)
    {
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f, MenuLayer::scene(false)));
    }
	
	    void create(CCObject*)
		{
                auto scene = CCScene::create();
        scene->addChild(ToolsLayer::create(), 100);

        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f, scene));
    }
	
	void onTest(CCObject*) {
		/*
		for(int i = 0; i < 1000; i++) {
			
			auto array = CCArray::create();
			
		for(int k = 0; k < 100; k++)
			
		 {
		 auto label22 = CCLabelBMFont::create("Version 2.2.1.2", "chatFont.fnt");
			array->addObject(label22);
		}
			array->removeAllObjects();

	}
	*/


	}

	
void onLevelRequest(CCObject*){
cocos2d::CCApplication::sharedApplication()->openURL("https://gdpseditor.com/levelRequest");
}
void onUsername(CCObject*){
cocos2d::CCApplication::sharedApplication()->openURL("https://gdpseditor.com/username");
}
void onPassword(CCObject*){
cocos2d::CCApplication::sharedApplication()->openURL("https://gdpseditor.com/password");
}
void onMusic(CCObject*){
cocos2d::CCApplication::sharedApplication()->openURL("https://gdpseditor.com/music");
}
void onGDBrowser(CCObject*){
cocos2d::CCApplication::sharedApplication()->openURL("https://gdpseditor.com/gdbrowser");
}
void onUnlisted(CCObject*){
cocos2d::CCApplication::sharedApplication()->openURL("https://gdpseditor.com/unlisted");
}
		

    CREATE_FUNC(ToolsLayer)
};