#include "patch.h"
#include <fstream>
#include <gd.h>
#include <CCFileUtils.h>
#include "GDPSManager.h"
#include <sstream>





GDPSManager* s_sharedGDPSManager = nullptr;


GDPSManager* GDPSManager::sharedState() {
    if (!s_sharedGDPSManager) {
        s_sharedGDPSManager = new GDPSManager();
        s_sharedGDPSManager->init();
    }
    return s_sharedGDPSManager;
}

void GDPSManager::encodeDataTo(CCDictionary* data) {
    auto tpDict = CCDictionary::create();
    tpDict->setIntForKey(this->opacity,"opacity");
    data->setDictionaryForKey(tpDict,"platform");

    auto globalDict = CCDictionary::create();
    globalDict->setIntForKey(this->oldTextures,"oldTextures");
    data->setDictionaryForKey(globalDict,"global");
}

void GDPSManager::dataLoaded(CCDictionary* data) {
    auto tpSettings = data->getDictionaryForKey("platform");
    this->opacity = tpSettings->getIntForKey("opacity");

    auto globalSettings = data->getDictionaryForKey("global");
    this->oldTextures = globalSettings->getIntForKey("oldTextures");
}


void GDPSManager::firstLoad() {
    opacity = 255;
}


bool GDPSManager::init() {
    this->m_sFileName = "CCModMenuManager.dat";
    this->setup();
    return true;
}

void GDPSManager::save() {
    CCLog("init save!");
    auto save_path = CCFileUtils::sharedFileUtils()->getWritablePath() + this->m_sFileName;
    auto dict = CCDictionary::create();
    this->encodeDataTo(dict);
    dict->writeToFile(save_path.c_str());
}


void GDPSManager::setup() {
    auto path = CCFileUtils::sharedFileUtils()->getWritablePath() + this->m_sFileName;
    std::ifstream infile(path.c_str());
    if(infile.good()){
        this->load();
    }else{
        this->dictionary = CCDictionary::create();
        this->firstLoad();
    }
}

void GDPSManager::load() {
    auto path = CCFileUtils::sharedFileUtils()->getWritablePath() + this->m_sFileName;
    auto dict = CCDictionary::createWithContentsOfFile(path.c_str());
    dataLoaded(dict);
}

// what the fuck
/*
void GDPSManager::setWorldIsland(int id) {
	
	auto v = CCString::createWithFormat("%02d",id)->getCString();
    patch *tmp = new patch();
    std::stringstream stream;
    stream << std::hex << int(v[0]) << " " << std::hex << int(v[1]);
    std::string result( stream.str() );
	
	tmp->addPatch("libcocos2dcpp.so", 0x7BFD68, result);

    tmp->Modify();
	}
*/

void GDPSManager::setPlayerSwing(int id) {
	
	auto v = CCString::createWithFormat("%02d",id)->getCString();
    patch *tmp = new patch();
    std::stringstream stream;
    stream << std::hex << int(v[0]) << " " << std::hex << int(v[1]);
    std::string result( stream.str() );
	
	  if(id == 1 || id == 0){         //swing_01_001 -> swn01_01_001
        patch *tmp = new patch();
                tmp->addPatch("libcocos2dcpp.so", 0x7A54CA, "73 77 6e 30 31");
                tmp->addPatch("libcocos2dcpp.so", 0x7A54DD, "73 77 6e 30 31"); 
				tmp->addPatch("libcocos2dcpp.so", 0x7A54F2, "73 77 6e 30 31"); 
                tmp->addPatch("libcocos2dcpp.so", 0x7A550A, "73 77 6e 30 31");
        tmp->Modify();
		
			
    }else{                          //swn01_01_2_001 --  swn01_01_2_001 --  swn01_01_glow_001
                tmp->addPatch("libcocos2dcpp.so", 0x7A54CA, "73 77 6e "+result);
                tmp->addPatch("libcocos2dcpp.so", 0x7A54DD, "73 77 6e "+result);
                tmp->addPatch("libcocos2dcpp.so", 0x7A54F2, "73 77 6e "+result);
				tmp->addPatch("libcocos2dcpp.so", 0x7A550A, "73 77 6e "+result);
       tmp->Modify();
	}
	
}

void GDPSManager::setPlayerJetpack(int id) {
	
	auto v = CCString::createWithFormat("%02d",id)->getCString();
    patch *tmp = new patch();
    std::stringstream stream;
    stream << std::hex << int(v[0]) << " " << std::hex << int(v[1]);
    std::string result( stream.str() );
	
	  if(id == 1 || id == 0){        
        tmp->addPatch("libcocos2dcpp.so", 0x7A55CD, "70 61 63 6B");
        tmp->addPatch("libcocos2dcpp.so", 0x7A55DF, "70 61 63 6B");
        tmp->addPatch("libcocos2dcpp.so", 0x7A55F3, "70 61 63 6B");
		tmp->addPatch("libcocos2dcpp.so", 0x7A560A, "70 61 63 6B");
        tmp->Modify();
			
    }else{            
        tmp->addPatch("libcocos2dcpp.so", 0x7A55CD, "6a 70"+result);
        tmp->addPatch("libcocos2dcpp.so", 0x7A55DF, "6a 70"+result);
        tmp->addPatch("libcocos2dcpp.so", 0x7A55F3, "6a 70"+result);
		tmp->addPatch("libcocos2dcpp.so", 0x7A560A, "6a 70"+result);
       tmp->Modify();
	}
	
}
	
	
void GDPSManager::changeServers(const char* server, const char* server_b64) {
	
	          unsigned char* server1;
          server1 = (unsigned char*) server;
		  
		            unsigned char* server1_b64;
          server1_b64 = (unsigned char*) server_b64;

			string server_hex;
			string serverB64_hex;
			 KittyUtils::toHex(server1, 33, server_hex);
			KittyUtils::toHex(server1_b64, 44, serverB64_hex);
			
	     patch *tmp = new patch();		
		 /*
         tmp->addPatch("libcocos2dcpp.so", 0x7A8513, server_hex);
         tmp->addPatch("libcocos2dcpp.so", 0x7A8941, server_hex);
         tmp->addPatch("libcocos2dcpp.so", 0x7A8C21, server_hex);
         tmp->addPatch("libcocos2dcpp.so", 0x7A8CB0, server_hex);
         tmp->addPatch("libcocos2dcpp.so", 0x7A8D5C, server_hex);
         tmp->addPatch("libcocos2dcpp.so", 0x7A8DE7, server_hex);
         tmp->addPatch("libcocos2dcpp.so", 0x7A8EAA, server_hex);
         tmp->addPatch("libcocos2dcpp.so", 0x7A8EE5, server_hex);
         tmp->addPatch("libcocos2dcpp.so", 0x7A8F53, server_hex);
         tmp->addPatch("libcocos2dcpp.so", 0x7A8FCC, server_hex);
         tmp->addPatch("libcocos2dcpp.so", 0x7A9054, server_hex);
         tmp->addPatch("libcocos2dcpp.so", 0x7A90BB, server_hex);
         tmp->addPatch("libcocos2dcpp.so", 0x7A9107, server_hex);
         tmp->addPatch("libcocos2dcpp.so", 0x7A914B, server_hex);
         tmp->addPatch("libcocos2dcpp.so", 0x7A918A, server_hex);
         tmp->addPatch("libcocos2dcpp.so", 0x7A91D3, server_hex);
         tmp->addPatch("libcocos2dcpp.so", 0x7A922C, server_hex);
         tmp->addPatch("libcocos2dcpp.so", 0x7A92A4, server_hex);
         tmp->addPatch("libcocos2dcpp.so", 0x7A9353, server_hex);
         tmp->addPatch("libcocos2dcpp.so", 0x7A93A3, server_hex);
         tmp->addPatch("libcocos2dcpp.so", 0x7A93FA, server_hex);
         tmp->addPatch("libcocos2dcpp.so", 0x7A94A0, server_hex);
         tmp->addPatch("libcocos2dcpp.so", 0x7B7A1D, server_hex);
         tmp->addPatch("libcocos2dcpp.so", 0x7B8191, server_hex);
         tmp->addPatch("libcocos2dcpp.so", 0x7B8202, server_hex);
         tmp->addPatch("libcocos2dcpp.so", 0x7B8278, server_hex);
         tmp->addPatch("libcocos2dcpp.so", 0x7B8446, server_hex);
         tmp->addPatch("libcocos2dcpp.so", 0x7B8A5D, server_hex);
         tmp->addPatch("libcocos2dcpp.so", 0x7B8A99, server_hex);
		 tmp->addPatch("libcocos2dcpp.so", 0x7A99A4, server_hex);
		 */
		 
tmp->addPatch("libcocos2dcpp.so", 0x7A9DD2, server_hex);
tmp->addPatch("libcocos2dcpp.so", 0x7AA0B2, server_hex);
tmp->addPatch("libcocos2dcpp.so", 0x7AA141, server_hex);
tmp->addPatch("libcocos2dcpp.so", 0x7AA1ED, server_hex);
tmp->addPatch("libcocos2dcpp.so", 0x7AA278, server_hex);
tmp->addPatch("libcocos2dcpp.so", 0x7AA2B0, server_hex);
tmp->addPatch("libcocos2dcpp.so", 0x7AA303, server_hex);
tmp->addPatch("libcocos2dcpp.so", 0x7AA33B, server_hex);
tmp->addPatch("libcocos2dcpp.so", 0x7AA376, server_hex);
tmp->addPatch("libcocos2dcpp.so", 0x7AA3E4, server_hex);
tmp->addPatch("libcocos2dcpp.so", 0x7AA45D, server_hex);
tmp->addPatch("libcocos2dcpp.so", 0x7AA4E5, server_hex);
tmp->addPatch("libcocos2dcpp.so", 0x7AA54C, server_hex);
tmp->addPatch("libcocos2dcpp.so", 0x7AA598, server_hex);
tmp->addPatch("libcocos2dcpp.so", 0x7AA5DC, server_hex);
tmp->addPatch("libcocos2dcpp.so", 0x7AA61B, server_hex);
tmp->addPatch("libcocos2dcpp.so", 0x7AA664, server_hex);
tmp->addPatch("libcocos2dcpp.so", 0x7AA6BD, server_hex);
tmp->addPatch("libcocos2dcpp.so", 0x7AA735, server_hex);
tmp->addPatch("libcocos2dcpp.so", 0x7AA7E4, server_hex);
tmp->addPatch("libcocos2dcpp.so", 0x7AA834, server_hex);
tmp->addPatch("libcocos2dcpp.so", 0x7AA88B, server_hex);
tmp->addPatch("libcocos2dcpp.so", 0x7AA931, server_hex);
tmp->addPatch("libcocos2dcpp.so", 0x7B919F, server_hex);
tmp->addPatch("libcocos2dcpp.so", 0x7B98FA, server_hex);
tmp->addPatch("libcocos2dcpp.so", 0x7B996B, server_hex);
tmp->addPatch("libcocos2dcpp.so", 0x7B99E1, server_hex);
tmp->addPatch("libcocos2dcpp.so", 0x7B9BAF, server_hex);
tmp->addPatch("libcocos2dcpp.so", 0x7B9F1C, server_hex);
tmp->addPatch("libcocos2dcpp.so", 0x7BA1C6, server_hex);
tmp->addPatch("libcocos2dcpp.so", 0x7BA202, server_hex);
		 
		 
		 
		 
		 
		 
		 
		 
		 
		 //bs64
		 /*
		          tmp->addPatch("libcocos2dcpp.so", 0x7A822E, serverB64_hex);
		          tmp->addPatch("libcocos2dcpp.so", 0x7A8280, serverB64_hex);
		          tmp->addPatch("libcocos2dcpp.so", 0x7A82D8, serverB64_hex);
		          tmp->addPatch("libcocos2dcpp.so", 0x7A8344, serverB64_hex);
		          tmp->addPatch("libcocos2dcpp.so", 0x7A8398, serverB64_hex);
		          tmp->addPatch("libcocos2dcpp.so", 0x7A841E, serverB64_hex);
		          tmp->addPatch("libcocos2dcpp.so", 0x7A84C1, serverB64_hex);
		          tmp->addPatch("libcocos2dcpp.so", 0x7A854D, serverB64_hex);
		          tmp->addPatch("libcocos2dcpp.so", 0x7A85F4, serverB64_hex);
		          tmp->addPatch("libcocos2dcpp.so", 0x7A8666, serverB64_hex);
		          tmp->addPatch("libcocos2dcpp.so", 0x7A87C9, serverB64_hex);
		          tmp->addPatch("libcocos2dcpp.so", 0x7A8875, serverB64_hex);
		          tmp->addPatch("libcocos2dcpp.so", 0x7A8997, serverB64_hex);
		          tmp->addPatch("libcocos2dcpp.so", 0x7A8A03, serverB64_hex);
		          tmp->addPatch("libcocos2dcpp.so", 0x7A8A66, serverB64_hex);
		          tmp->addPatch("libcocos2dcpp.so", 0x7A8ACB, serverB64_hex);
		          tmp->addPatch("libcocos2dcpp.so", 0x7A8B37, serverB64_hex);
		          tmp->addPatch("libcocos2dcpp.so", 0x7A8BBD, serverB64_hex);
		          tmp->addPatch("libcocos2dcpp.so", 0x7A8CEA, serverB64_hex);
		          tmp->addPatch("libcocos2dcpp.so", 0x7A92D8, serverB64_hex);
		          tmp->addPatch("libcocos2dcpp.so", 0x7A9442, serverB64_hex);
		          tmp->addPatch("libcocos2dcpp.so", 0x7A9602, serverB64_hex);
				  */
tmp->addPatch("libcocos2dcpp.so", 0x7A96BF, serverB64_hex);
tmp->addPatch("libcocos2dcpp.so", 0x7A9711, serverB64_hex);
tmp->addPatch("libcocos2dcpp.so", 0x7A9769, serverB64_hex);
tmp->addPatch("libcocos2dcpp.so", 0x7A97D5, serverB64_hex);
tmp->addPatch("libcocos2dcpp.so", 0x7A9829, serverB64_hex);
tmp->addPatch("libcocos2dcpp.so", 0x7A98AF, serverB64_hex);
tmp->addPatch("libcocos2dcpp.so", 0x7A9952, serverB64_hex);
tmp->addPatch("libcocos2dcpp.so", 0x7A99DE, serverB64_hex);
tmp->addPatch("libcocos2dcpp.so", 0x7A9A85, serverB64_hex);
tmp->addPatch("libcocos2dcpp.so", 0x7A9AF7, serverB64_hex);
tmp->addPatch("libcocos2dcpp.so", 0x7A9C5A, serverB64_hex);
tmp->addPatch("libcocos2dcpp.so", 0x7A9D06, serverB64_hex);
tmp->addPatch("libcocos2dcpp.so", 0x7A9E28, serverB64_hex);
tmp->addPatch("libcocos2dcpp.so", 0x7A9E94, serverB64_hex);
tmp->addPatch("libcocos2dcpp.so", 0x7A9EF7, serverB64_hex);
tmp->addPatch("libcocos2dcpp.so", 0x7A9F5C, serverB64_hex);
tmp->addPatch("libcocos2dcpp.so", 0x7A9FC8, serverB64_hex);
tmp->addPatch("libcocos2dcpp.so", 0x7AA04E, serverB64_hex);
tmp->addPatch("libcocos2dcpp.so", 0x7AA17B, serverB64_hex);
tmp->addPatch("libcocos2dcpp.so", 0x7AA769, serverB64_hex);
tmp->addPatch("libcocos2dcpp.so", 0x7AA8D3, serverB64_hex);
tmp->addPatch("libcocos2dcpp.so", 0x7AAA93, serverB64_hex);


		 tmp->Modify();

 }