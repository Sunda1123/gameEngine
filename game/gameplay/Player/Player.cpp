#include "Player.h"
#include "../Tower/AllTowers.h"   // 所有塔的总入口（一行搞定，不用逐个 include）
#include "../Monster/OrdinaryMonster.h"
#include "../Monster/Monster.h"
#include "../Map/Map.h"
#include <vector>
#include <SDL3/SDL.h>

Player::Player() { initStats(); }


void Player::initStats() {
    initialGold = 1000;     // 记录初始金币（以后算得分/回放用）
    gold = 1000;            // ★ 当前金币 = 初始资金，就在这设
    maxBaseHealth = 100;
    baseHealth = 100;
}


                                    //🐬这点得把那点塔和怪的数据写表带过来
Player::~Player() {
    // 塔不用管了：towers 是 unique_ptr，自己会 delete（RAII）
    for (Monster* m : monsters) delete m;   // 怪还是裸指针，得手动清
}


bool Player::placeTower(float x, float y) {
    int cost = 100;  // 先写死100，后面再做成表
    if (gold < cost) return false;

    gold -= cost;
    switch (towerType) {
        case TowerType::Arrow:
            towers.push_back(std::make_unique<ArrowTower>(x, y));
            break;
        case TowerType::Cannon:
            towers.push_back(std::make_unique<CannonTower>(x, y));
            break;
        case TowerType::Magic:
            towers.push_back(std::make_unique<MagicTower>(x, y));
            break;
        case TowerType::Ice:
            towers.push_back(std::make_unique<IceTower>(x, y));
            break;
        case TowerType::Tar:
            towers.push_back(std::make_unique<TarTower>(x, y));
            break;
        case TowerType::Gold:
            towers.push_back(std::make_unique<GoldTower>(x, y));
            break;
    }
    return true;
}

bool Player::spawnMonster(float x, float y) {
    int cost = 50;   // 先写死50
    if (gold < cost) return false;

    gold -= cost;
    monsters.push_back(new OrdinaryMonster(x, y));
    return true;
}

// 基地挨打：血是 Player 的私有财产，只有这个 public 方法能改（封装！）
void Player::takeBaseDamage(int dmg) {
    baseHealth -= dmg;
    if (baseHealth < 0) baseHealth = 0;   // 血不下穿 0
}

// 加钱：钱是 Player 的私有财产，加钱走 public 入口
void Player::addGold(int amount) {
    gold += amount;
}