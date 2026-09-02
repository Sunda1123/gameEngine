#include "CannonTower.h"
#include "TowerFactory.h"   // 报名要用它（.cpp 里 include，不污染头文件）

CannonTower::CannonTower(float x, float y) : Tower(TowerType::Cannon, x, y) {
    damage = 10.f; range = 120.f; fireRate = 0.8f; cost = 80;
}
void CannonTower::attack() {
    // TODO: 生成箭 projectile，加入世界的子弹列表
    resetCooldown();
}

// 报名段：程序启动时自动执行，替 CannonTower 报名
static bool CannonRegistered = [] {
    TowerFactory::registerTower(TowerType::Cannon,
        [](float x, float y) { return std::make_unique<CannonTower>(x, y); });
    return true;
}();
