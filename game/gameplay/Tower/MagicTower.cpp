#include "MagicTower.h"
#include "TowerFactory.h"   // 报名要用它（.cpp 里 include，不污染头文件）

MagicTower::MagicTower(float x, float y) : Tower(TowerType::Magic, x, y) {
    damage = 15.f; range = 160.f; fireRate = 1.2f; cost = 160;
}
void MagicTower::attack() {
    // TODO: 生成箭 projectile，加入世界的子弹列表
    resetCooldown();
}

// 报名段：程序启动时自动执行，替 MagicTower 报名
static bool MagicRegistered = [] {
    TowerFactory::registerTower(TowerType::Magic,
        [](float x, float y) { return std::make_unique<MagicTower>(x, y); });
    return true;
}();
