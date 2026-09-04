#include "GoldTower.h"
#include "TowerFactory.h"   // 报名要用它（.cpp 里 include，不污染头文件）
#include "../Player/Player.h"   // act 要用 player.addGold → 需要 Player 完整定义（防 incomplete type）

GoldTower::GoldTower(float x, float y) : Tower(TowerType::Gold, x, y) {
    fireRate = 2.0f; cost = 50;
}

// 经济塔的"每帧行为"：不索敌不打怪，冷却到了就产钱（cooldown 当产钱计时器）
void GoldTower::act(Player& player, float dt) {
    update(dt);                // 冷却倒数
    if (canFire()) {           // 冷却到 0 = 能产钱了
        player.addGold(10);    // 产钱（数值待平衡）
        resetCooldown();       // 重置计时器 = fireRate
    }
}
 

// 报名段：程序启动时自动执行，替 GoldTower 报名
static bool GoldRegistered = [] {
    TowerFactory::registerTower(TowerType::Gold,
        [](float x, float y) { return std::make_unique<GoldTower>(x, y); });
    return true;
}();

