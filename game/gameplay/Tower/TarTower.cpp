#include "TarTower.h"

TarTower::TarTower(float x, float y) : Tower(TowerType::Tar, x, y) {
    damage = 0.f; range = 80.f; fireRate = 2.0f; slowFactor = 0.2f; damageOverTime = 5.0f; burDuration = 3.f;
}
void TarTower::attack() {
    // TODO: 生成焦油蛋，AOE减速，只有持续伤害，没有瞬间爆发伤害，同时给敌人上弱减速 buff
}
