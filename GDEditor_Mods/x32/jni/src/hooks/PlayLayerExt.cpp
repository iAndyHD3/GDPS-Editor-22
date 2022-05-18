#include <dlfcn.h>
#include "blaze.h"
#include "cocos2d.h"
#include "PlayLayerExt.h"
#include "GDPSManager.h"
#include "patch.h"


template<class T>
void* getPointer(T value){
    auto val = reinterpret_cast<void *&>(value);
    return val;
}



void PlayLayerExt::update_hk(float a1) {
    update_trp(this,a1);

    UILayer * layer = reinterpret_cast<UILayer *>(*((int *) this + 409));

    if(*(int *)((long)layer + 502)){ // is platformer


        auto manager = GDPSManager::sharedState();

        auto sp = reinterpret_cast<CCSprite*>(reinterpret_cast<CCMenu *>(layer->getChildren()->objectAtIndex(0)));


	
sp->setOpacity(manager->opacity);
/*
	auto children = reinterpret_cast<CCMenu *>(layer->getChildren());
		
		int count = children->getChildrenCount();
		for(int i = 0; i < count; i++) {
			
			auto label = CCLabelBMFont::create(GDPS->itos(i).c_str(), "bigFont.fnt");
			
		    auto node = reinterpret_cast<CCNode*>(children->getChildren()->objectAtIndex(i));
	
			label->setPosition(node->getPosition());
			layer->addChild(label, 1000);
			
		}
	*/
        

    }





}
