#include <dlfcn.h>
#include "blaze.h"
#include "cocos2d.h"
#include "MoreOptionsLayerExt.h"
#include "GDPSManager.h"


void MoreOptionsLayerExt::addToggle_hk(const char * title, const char * code, const char * desc) {
    if(GDPSManager::sharedState()->isGDPSSettings){
        if(strcmp(title , "Smooth fix in editor")==0){
            addToggle_trp(this,"Play test","100001","Enable <cy>play test</c> in the editor.\nIt's really unstable so <cr>you shouldn't turn this option on</c>.\nWe are not responsible for any data loss.");
			addToggle_trp(this,"Level Info","0109","Show advanced level info (turn off for cleaner gameplay)");
            addToggle_trp(this,"Original Textures","100002","Use the original textures instead of the new one.");
			addToggle_trp(this,"Clean menu\n(Req. Restart)","100003","Disables menu addons, advanced options are still accessible in settings.\n<cy>Restart the game to apply changes</c>");
			addToggle_trp(this,"Adjust version position","100004","Moves the version indicator to the left for phones with rounded corners");			
			addToggle_trp(this,"Remove pause button","100005", "Meant for cleaner recordings, use the back button or the ESC key on emulator to go back");			

			
			
			
            GDPSManager::sharedState()->isGDPSSettings = false;
        }
    }else{
        addToggle_trp(this,title,code,desc);
    }

}

void MoreOptionsLayerExt::onToggle_hk(CCObject *sender) {

}
