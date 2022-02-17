#include <gd.h>
#include "cocos2d.h"
#include "onPlaytestExt.h"
#include "patch.h"
//#include "../../include/hooks/MenuLayerExt.h"


void onPlaytestExt::playtest_hk(int a2, int a3, int a4) {
	
	if(GM->getGameVariable("100001")) {
	return playtest(this, a2, a3, a4);
	} else {
		
        FLAlertLayer::create(nullptr, "Playtest disabled", "Playtest <cr>often crashes</c> so it's disabled by default\nYou can enable playtest (at your own risk) in GDPS Settings\n<cg>Options -> GDPS Settings -> Playtest</c>", "OK", nullptr, 470, false, 200)->show();
	}
	
}

