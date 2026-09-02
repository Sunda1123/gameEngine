#include "TarTower.h"
#include "TowerFactory.h"   // 报名要用它（.cpp 里 include，不污染头文件）

TarTower::TarTower(float x, float y) : Tower(TowerType::Tar, x, y) {
    damage = 0.f; range = 80.f; fireRate = 2.0f; slowFactor = 0.2f; damageOverTime = 5.0f; burDuration = 3.f; cost = 220;
}
void TarTower::attack() {
    // TODO: 生成箭 projectile，加入世界的子弹列表
    resetCooldown();
}

// 报名段：程序启动时自动执行，替 TarTower 报名
static bool TarRegistered = [] {
    TowerFactory::registerTower(TowerType::Tar,
        [](float x, float y) { return std::make_unique<TarTower>(x, y); });
    return true;
}();
