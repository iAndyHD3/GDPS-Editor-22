#include <dlfcn.h>
#include "blaze.h"
#include "cocos2d.h"
#include "PlayLayerExt.h"
#include "GDPSManager.h"
#include "patch.h"
#include "gd.h"
#include <sstream>


template<class T>
void* getPointer(T value){
    auto val = reinterpret_cast<void *&>(value);
    return val;
}

std::string PlayLayerExt::convertSecondsToMMSS (int value, string ms) {
  std::string result;
  // compute h, m, s
  std::string m = GDPS->itos((value % 3600) / 60);
  std::string s = GDPS->itos(value % 60);
  // add leading zero if needed
  std::string mm = std::string(2 - m.length(), '0') + m;
  std::string ss = std::string(2 - s.length(), '0') + s;
  // return mm:ss if hh is 00


    result = mm + ":" + ss + "." + ms ;
  return result;
}

void PlayLayerExt::onUpdateTimer(float dt) {
		//add all this extern shit to a class or something
		extern float timer;
		timer = timer + dt;
		string result;

		string strSeconds = CCString::createWithFormat("%.0f", timer - 0.5)->getCString();
		
		string strDecimals = CCString::createWithFormat("%.3f", timer)->getCString();
		
		string realSeconds = strDecimals;
		realSeconds.erase(strSeconds.length(), 4);
		
		strDecimals.erase(0, strSeconds.length() + 1);
		
		
		
		result = convertSecondsToMMSS(atoi(realSeconds.c_str()), strDecimals);
		
	extern CCLabelBMFont* timerLabel;
		timerLabel->setString(result.c_str());
	};
	
void PlayLayerExt::resetLevel_hk() {
	resetLevel_trp(this);
	extern float timer;
	timer = 0;

	    UILayer * layer = reinterpret_cast<UILayer *>(*((int *) this + 409));
	layer->schedule(schedule_selector(PlayLayerExt::onUpdateTimer), 0.01);

}

void PlayLayerExt::destroyPlayer_hk(PlayerObject* self, int a2)
{
		destroyPlayer_trp(self, a2);
			PlayLayer* pl = GameManager::sharedState()->_playLayer();

	    UILayer * layer = reinterpret_cast<UILayer *>(*((int *) pl + 409));

		layer->unschedule(schedule_selector(PlayLayerExt::onUpdateTimer));

}


void PlayLayerExt::update_hk(float a1) {
    update_trp(this,a1);

    UILayer * layer = reinterpret_cast<UILayer *>(*((int *) this + 409));



    if(*(int *)((long)layer + 502)){ // is platformer


        auto manager = GDPSManager::sharedState();

        auto sp = reinterpret_cast<CCSprite*>(reinterpret_cast<CCMenu *>(layer->getChildren()->objectAtIndex(0)));


        sp->setOpacity(manager->opacity);
		
		
		

    }


}
