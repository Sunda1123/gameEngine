#include "Player.h"
#include "Monster.h"
#include "Map.h"
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
    for (Monster* m : monster) delete m;
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
    monster.push_back(new Monster(MonsterType::ORDINARY, x, y));
    return true;
}