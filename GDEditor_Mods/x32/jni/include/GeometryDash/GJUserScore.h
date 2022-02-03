#ifndef __GJUSERSCORE_H__
#define __GJUSERSCORE_H__

#include <gd.h>

class GJUserScore : public cocos2d::CCNode
{
public:
    std::string userName_;
    std::string userUDID_;
    int scoreType_; // legacy field, used in 1.9 to determine shown info
    int userID_;
    int accountID_;

    int stars_;
    int diamonds_;
    int demons_;
    int playerRank_;
    int creatorPoints_; // note - internally this is named levels
    int secretCoins_;
    int userCoins_;

    int iconID_; // for leaderboards, icon id to show
    int color1_;
    int color2_;
    int special_;

    int messageState_;
    int friendStatus_;
    int commentHistoryStatus_;

    std::string youtubeURL_;
    std::string twitterURL_;
    std::string twitchURL_;

    int playerCube_;
    int playerShip_;
    int playerBall_;
    int playerUfo_;
    int playerWave_;
    int playerRobot_;
    int playerSpider_;
    int playerStreak_;
    bool glowEnabled_ : 4;

    int playerExplosion_;

    int modBadge_;
    int globalRank_;

    int friendReqStatus_;
    int newMsgCount_;
    int friendReqCount_;
    bool isBlocked : 4;

    std::string lastScoreAge;

// fixed members
public:
    CLASS_MEMBER(int, modBadge, 0x17C);
};

class GJUserScoreExt : public GJUserScore {
public:
    int playerSwing_;
};

#endif