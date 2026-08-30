#include "Player.h"
#include "../Tower/ArrowTower.h"
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
    for (Tower* t : towers) delete t;
    for (Monster* m : monsters) delete m;
}


bool Player::placeTower(float x, float y) {
    int cost = 100;  // 先写死100，后面再做成表
    if (gold < cost) return false;

    gold -= cost;
    towers.push_back(new ArrowTower(x, y));  // 暂时默认放箭塔
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