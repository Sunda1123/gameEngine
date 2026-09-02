#include "IceTower.h"
#include "TowerFactory.h"   // 报名要用它（.cpp 里 include，不污染头文件）

IceTower::IceTower(float x, float y) : Tower(TowerType::Ice, x, y) {
    damage = 5.f; range = 100.f; fireRate = 0.7f; slowFactor = 0.5f; cost = 140;
}
void IceTower::attack() {
    // TODO: 生成箭 projectile，加入世界的子弹列表
    resetCooldown();
}

// 报名段：程序启动时自动执行，替 IceTower 报名
static bool IceRegistered = [] {
    TowerFactory::registerTower(TowerType::Ice,
        [](float x, float y) { return std::make_unique<IceTower>(x, y); });
    return true;
}();
