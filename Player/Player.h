#include <vector>
#include "../Map/Map.h"
#include "../Tower/Tower.h"
#include "../Monster/Monster.h"


class Player{
private:
    void initStats();     //初始化玩家初始条件和状态 
    int initialGold;   //初始金币，后边定价再定这个
    int gold;       //现有金币
    int maxBaseHealth;      //基地血量，也是玩家血量，到时候得画个血条
    int baseHealth;
public:
    Player();
    ~Player();
    std::vector<Tower*> towers;
    std::vector<Monster*> monster;

    bool placeTower(float x, float y);        // 花钱放塔
    bool spawnMonster(float x , float y );             // 花钱放怪
    int getInitialGold() const { return initialGold; }
    int getGold() const { return gold; }
    int getMaxBaseHealth() const { return maxBaseHealth; }
    int getBaseHealth() const { return baseHealth; }
};


