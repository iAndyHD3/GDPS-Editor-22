#include <cocos2d.h>
#include "gd.h"

class PauseLayerExt : public PauseLayer {	
public:

CCLayer* firstLayer;
CCLayer* secondLayer;

public:


    void onNextPage(CCObject * sender);
    void onPrevPage(CCObject * sender);

    void onPlatformOpacity(CCObject * sender);

	void addLayer(int layer);


    static inline bool (*init_trp)(PauseLayer*);
    bool init_hk();






};