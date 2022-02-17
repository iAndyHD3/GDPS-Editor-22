#ifndef __OPTIONSLAYER_H__
#define __OPTIONSLAYER_H__

#include "cocos2d.h"



class GD_DLL OptionsLayer : public CCLayer, public FLAlertLayerProtocol {
public:
	~OptionsLayer();
	
	static OptionsLayer *create();

	
	CCMenu *menu_;
	void onSupport();
	void onRate();
	void onSoundtracks();
	void onHelp();
	void onMusic();
	void onFX();
	void onGC();
	
	bool goToSupport_;
	bool goToSongs_;
	void exitLayer();

	virtual void customSetup();
	virtual void layerHidden();
	virtual void FLAlert_Clicked(FLAlertLayer *layer, bool accept);


	void onGDPSSettings(CCObject *sender);
	void onVideo(CCObject* sender);


};

#endif //__OPTIONSLAYER_H__
