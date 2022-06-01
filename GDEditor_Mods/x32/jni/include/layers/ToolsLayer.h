#pragma once

#include "cocos2d.h"
#include "gd.h"
#include "obfuscate.h"
#include "MapSelectLayer.h"

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
	
		void onTheMap(CCObject*) {
		auto dir = CCDirector::sharedDirector();
		auto scene = CCScene::create();
		scene->addChild(MapSelectLayer::scene(100), 100);
		dir->replaceScene(CCTransitionFade::create(0.5f, scene));
	}
	
void onAlert(CCObject*) {
	FLAlertLayer::create(nullptr, "The map!", "This is not the real map, only the functionality of the layer was leaked so placeholder textures were added to open it.",  "OK", nullptr, 400, false, 300)->show();
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