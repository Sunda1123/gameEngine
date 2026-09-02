#include "ArrowTower.h"
#include "TowerFactory.h"   // 报名要用它（.cpp 里 include，不污染头文件）

ArrowTower::ArrowTower(float x, float y) : Tower(TowerType::Arrow, x, y) {
    damage = 10.f; range = 120.f; fireRate = 0.8f; cost = 80;
}
void ArrowTower::attack() {
    // TODO: 生成箭 projectile，加入世界的子弹列表
    resetCooldown();
}

// 报名段：程序启动时自动执行，替 ArrowTower 报名
static bool arrowRegistered = [] {
    TowerFactory::registerTower(TowerType::Arrow,
        [](float x, float y) { return std::make_unique<ArrowTower>(x, y); });
    return true;
}();
