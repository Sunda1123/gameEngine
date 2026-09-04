#pragma once
#include <vector>
#include <memory>   // unique_ptr（塔归它管，RAII）
#include "../Map/Map.h"
#include "../Tower/Tower.h"
#include "../Tower/TowerFactory.h"   // getTowerCost 要问 Factory 要价格
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

    int placeTower(float x, float y);        // 放塔（自己管钱）：返回扣的钱；失败返 0（撤销要退钱，所以要知道扣多少）
    bool spawnMonster(float x , float y );             // 花钱放怪
    int getInitialGold() const { return initialGold; }
    int getGold() const { return gold; }
    int getMaxBaseHealth() const { return maxBaseHealth; }
    int getBaseHealth() const { return baseHealth; }
    void takeBaseDamage(int dmg);   // 基地挨打：血归 Player 管，只有它能改
    void addGold(int amount);       // 加钱：经济塔产钱 / 以后杀怪给钱都走这个
    void setTowerType(TowerType t) { towerType = t; }   // 选塔（GameUI 点按钮切换）
    int getTowerCount() const { return (int)towers.size(); }   // 塔数量
    void removeTower(int index) {   // 按索引删塔（带边界保护，别越界崩）
        if (index >= 0 && index < (int)towers.size())
            towers.erase(towers.begin() + index);
    }
    int getTowerCost() const {   // 造这座塔要花多少钱（问 Factory 造个临时塔看价）
        auto t = TowerFactory::create(towerType, 0, 0);
        return t ? t->getCost() : 0;   // 空指针保护：名册没有就白送 0
    }

};




