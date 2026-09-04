#include "Player.h"
#include "../Tower/TowerFactory.h"   // 造塔走名册工厂，Player 不用再认识具体塔
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


// 放塔：钱归这里管（B 方案）。成功返回扣了多少钱（命令撤销要退它），失败返回 0
int Player::placeTower(float x, float y) {
    // 造塔走名册：让 Factory 按当前选中类型造（switch 六连已送进各塔的报名段）
    auto t = TowerFactory::create(towerType, x, y);
    if (!t) return 0;   // 名册没这座塔（没报名/类型无效）→ 失败

    int cost = t->getCost();   // 价格跟着塔走（单一数据源）
    if (gold < cost) return 0; // 钱不够
    gold -= cost;

    towers.push_back(std::move(t));
    return cost;   // ★ 告诉调用方花了多少（Command 靠它 undo 退钱）
}

void Player::addGold(int amount) {
    gold += amount;
}

// 加钱：钱是 Player 的私有财产，加钱走 public 入口

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
