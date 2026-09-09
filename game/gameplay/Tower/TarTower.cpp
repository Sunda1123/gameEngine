#include "TarTower.h"
#include "TowerFactory.h"   // 报名要用它（.cpp 里 include，不污染头文件）
#include "../Bullet/TarBullet.h"   // 发焦油弹（用别人先打招呼）

TarTower::TarTower(float x, float y) : Tower(TowerType::Tar, x, y) {
    damage = 0.f; range = 80.f; fireRate = 2.0f; slowFactor = 0.2f; damageOverTime = 5.0f; burDuration = 3.f; cost = 220;
}

// 焦油塔发"焦油弹"：命中不靠撞伤（damage=0），靠 onHit 挂 DOT 每秒烧血
std::unique_ptr<Bullet> TarTower::fireBullet(SDL_FPoint dir) {
    return std::make_unique<TarBullet>(pos, dir, getDamage(), damageOverTime, burDuration);
}
// （attack() 是旧设计死代码——基类 act 统一走 fireBullet 发射，attack 没被调用，删了）

// 报名段：程序启动时自动执行，替 TarTower 报名
static bool TarRegistered = [] {
    TowerFactory::registerTower(TowerType::Tar,
        [](float x, float y) { return std::make_unique<TarTower>(x, y); });
    return true;
}();
