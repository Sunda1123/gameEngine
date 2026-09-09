#include "IceTower.h"
#include "TowerFactory.h"          // 报名要用它
#include "../Bullet/IceBullet.h"   // fireBullet 要发冰弹（用别人先打招呼）

IceTower::IceTower(float x, float y) : Tower(TowerType::Ice, x, y) {
    damage = 5.f; range = 100.f; fireRate = 0.7f; slowFactor = 0.5f; slowDuration = 2.f; cost = 140;
}
void IceTower::attack() {
    // 发射已由基类 act → fireBullet 管，attack 留着以后用
    resetCooldown();
}

// 冰塔发冰弹：把冰塔的减速数值塞进冰弹（override 基类的普通弹）
std::unique_ptr<Bullet> IceTower::fireBullet(SDL_FPoint dir) {
    return std::make_unique<IceBullet>(pos, dir, damage, slowFactor, slowDuration);
}

// 报名段：程序启动时自动执行，替 IceTower 报名（注意要 return true！）
static bool IceRegistered = [] {
    TowerFactory::registerTower(TowerType::Ice,
        [](float x, float y) { return std::make_unique<IceTower>(x, y); });
    return true;
}();
