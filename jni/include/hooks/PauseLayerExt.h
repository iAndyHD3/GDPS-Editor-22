class PauseLayerExtProtocol{
public:
    CCArray * firstPage;
    CCArray * page2;

    CCMenu * pageControls;
    vector<CCArray*> m_pages;
    int m_currentPage;
};



class PauseLayerExt : public PauseLayer, public PauseLayerExtProtocol{
public:


    void showPage(int page);
    void onNextPage(CCObject * sender);
    void onPrevPage(CCObject * sender);

    void onPlatformOpacity(CCObject * sender);


    void addPageControl();



    static inline bool (*init_trp)(PauseLayer*);
    bool init_hk();






};