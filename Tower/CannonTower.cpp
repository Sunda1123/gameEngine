#include "CannonTower.h"

CannonTower::CannonTower(float x, float y) : Tower(TowerType::Cannon, x, y) {
    damage = 30.f; range = 80.f; fireRate = 2.0f;
}
void CannonTower::attack() {
    // TODO: 生成炮弹，带 AOE
    resetCooldown();
}
