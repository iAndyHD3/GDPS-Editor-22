#pragma once

#include "cocos2d.h"
#include "gd.h"


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
	
void onYT(CCObject*){
cocos2d::CCApplication::sharedApplication()->openURL("https://www.youtube.com/channel/UC9vRBa6Wffb0R7N7ezbwh9A");
}
void onUsername(CCObject*){
cocos2d::CCApplication::sharedApplication()->openURL("http://game.gdpseditor.com/server/tools/account/changeUsername.php");
}
void onPassword(CCObject*){
cocos2d::CCApplication::sharedApplication()->openURL("http://game.gdpseditor.com/server/tools/account/changePassword.php");
}
void onMusic(CCObject*){
cocos2d::CCApplication::sharedApplication()->openURL("http://game.gdpseditor.com/server/tools/music.php");
}
void onGDBrowser(CCObject*){
cocos2d::CCApplication::sharedApplication()->openURL("https://gdpseditor.gdbrowser.com/");
}
void onUnlisted(CCObject*){
cocos2d::CCApplication::sharedApplication()->openURL("http://game.gdpseditor.com/server/tools/stats/unlisted.php");
}
		

    CREATE_FUNC(ToolsLayer)
};