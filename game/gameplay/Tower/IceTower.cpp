#include "IceTower.h"

IceTower::IceTower(float x, float y) : Tower(TowerType::Ice, x, y) {
    damage = 5.f; range = 100.f; fireRate = 0.7f; slowFactor = 0.5f;
}
void IceTower::attack() {
    // TODO: 发射冰弹，命中后给敌人上减速 buff
    resetCooldown();
}
