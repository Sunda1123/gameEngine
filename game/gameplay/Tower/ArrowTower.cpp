#include "ArrowTower.h"

ArrowTower::ArrowTower(float x, float y) : Tower(TowerType::Arrow, x, y) {
    damage = 10.f; range = 120.f; fireRate = 0.8f;
}
void ArrowTower::attack() {
    // TODO: 生成箭 projectile，加入世界的子弹列表
    resetCooldown();
}
