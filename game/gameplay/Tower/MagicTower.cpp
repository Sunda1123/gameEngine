#include "MagicTower.h"

MagicTower::MagicTower(float x, float y) : Tower(TowerType::Magic, x, y) {
    damage = 15.f; range = 160.f; fireRate = 1.2f; cost = 160;
}
void MagicTower::attack() {
    // TODO: 发射穿透魔法弹
    resetCooldown();
}
