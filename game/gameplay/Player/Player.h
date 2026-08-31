#include <vector>
#include <memory>   // unique_ptr（塔归它管，RAII）
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
    TowerType towerType = TowerType::Arrow;   // 当前选中的塔类型（默认箭塔，GameUI 可改）
public:
    Player();
    ~Player();
    std::vector<std::unique_ptr<Tower>> towers;   // 塔归 unique_ptr 管（RAII，自动释放）
    std::vector<Monster*> monsters;

    bool placeTower(float x, float y);        // 花钱放塔
    bool spawnMonster(float x , float y );             // 花钱放怪
    int getInitialGold() const { return initialGold; }
    int getGold() const { return gold; }
    int getMaxBaseHealth() const { return maxBaseHealth; }
    int getBaseHealth() const { return baseHealth; }
    void takeBaseDamage(int dmg);   // 基地挨打：血归 Player 管，只有它能改
    void addGold(int amount);       // 加钱：经济塔产钱 / 以后杀怪给钱都走这个
    void setTowerType(TowerType t) { towerType = t; }   // 选塔（GameUI 点按钮切换）
};


