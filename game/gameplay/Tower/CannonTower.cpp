#include "CannonTower.h"
#include "TowerFactory.h"   // 报名要用它（.cpp 里 include，不污染头文件）

CannonTower::CannonTower(float x, float y) : Tower(TowerType::Cannon, x, y) {
    damage = 10.f; range = 120.f; fireRate = 0.8f; cost = 80;
}
void CannonTower::attack() {
    // 发射已统一在基类 Tower::act（索敌→算方向→塞子弹）；各塔特殊子弹以后再分　
    
    resetCooldown();
}

// 报名段：程序启动时自动执行，替 CannonTower 报名
static bool CannonRegistered = [] {
    TowerFactory::registerTower(TowerType::Cannon,
        [](float x, float y) { return std::make_unique<CannonTower>(x, y); });
    return true;
}();
