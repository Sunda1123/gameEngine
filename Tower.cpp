#include "Tower.h"


Tower::Tower(TowerType type, float x, float y)
    : type(type), pos{x, y}, cooldown(0.f), level(1), slowFactor(0.f)
{
    initStats();
}

Tower::~Tower() = default; //析构调用



void Tower::update(float dt) {         //
    if (cooldown > 0.f) cooldown -= dt;
}

void Tower::upgrade() {
    level++;
    damage *= 1.2f;
    range *= 1.05f;
    damageOverTime *= 1.2f;
    burDuration *= 1.1f;
}

bool Tower::canFire() const {
    return cooldown <= 0.f;
}

void Tower::resetCooldown() {
    cooldown = fireRate;
}

float Tower::getCooldown() const {
    return cooldown;
}







void Tower::initStats() {
    switch (type) {
        case TowerType::Arrow:
            damage = 10.f; range = 120.f; fireRate = 0.8f;
            break;
        case TowerType::Cannon:
            damage = 30.f; range = 80.f; fireRate = 2.0f;
            break;
        case TowerType::Magic:
            damage = 15.f; range = 160.f; fireRate = 1.2f;
            break;
        case TowerType::Ice:
            damage = 5.f; range = 100.f; fireRate = 0.7f; slowFactor = 0.5f;
            break;
        case TowerType::Tar:
            damage = 0.f; range = 80.f; fireRate = 2.0f; slowFactor = 0.2f ; damageOverTime = 5.0f; burDuration = 3.f;
    }
}









ArrowTower::ArrowTower(float x, float y) : Tower(TowerType::Arrow, x, y) {}
void ArrowTower::attack() {
    // TODO: 生成箭 projectile，加入世界的子弹列表
    resetCooldown();
}


CannonTower::CannonTower(float x, float y) : Tower(TowerType::Cannon, x, y) {}
void CannonTower::attack() {
    // TODO: 生成炮弹，带 AOE
    resetCooldown();
}


MagicTower::MagicTower(float x, float y) : Tower(TowerType::Magic, x, y) {}
void MagicTower::attack() {
    // TODO: 发射穿透魔法弹
    resetCooldown();
}


IceTower::IceTower(float x, float y) : Tower(TowerType::Ice, x, y) {}
void IceTower::attack() {
    // TODO: 发射冰弹，命中后给敌人上减速 buff
    resetCooldown();
}

TarTower::TarTower(float x,float y) : Tower (TowerType::Tar,x,y){}
void TarTower::attack(){
    //TODO: 生成焦油蛋，AOE减速，只有持续伤害，没有瞬间爆发伤害，同时给敌人上弱减速 buff 
}