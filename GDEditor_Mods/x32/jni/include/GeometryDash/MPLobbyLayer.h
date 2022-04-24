#pragma once
#include <cocos2d.h>

class MPLobbyLayer : public cocos2d::CCLayer {
public:
	static cocos2d::CCScene* scene();
	
	static cocos2d::CCLayer* create();
	void tryExitLobby();
	void uploadActionFinished(int, int);
	bool init();
};