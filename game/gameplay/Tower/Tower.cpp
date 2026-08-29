#include "Tower.h"


Tower::Tower(TowerType type, float x, float y)   //侯捷P39可以回顾构造函数，赋初始值，建立类的不变量
    : type(type),
    pos{x, y},
    cooldown(0.f),
    level(1),
     slowFactor(0.f)
{
    // 具体数值由各派生塔构造函数设置（KingdomRush 风格）
}

Tower::~Tower() = default; //析构调用



Monster* Tower::findTarget(const std::vector<Monster*>& monsters) {
    float best = range * range;
    Monster* target = nullptr;

    SDL_FPoint tp = Tower::getPos();  // 塔自己的位置

    for (auto m : monsters) {
        //活着的怪才打
        if (m->getHp() <= 0) continue;

        //勾股定理算距离
        SDL_FPoint mp = m->getPos();
        float dx = mp.x - tp.x;
        float dy = mp.y - tp.y;
        float dist = dx * dx + dy * dy;

        if (dist < best) {
            best = dist;
            target = m;
        }
    }
    return target;
}



void Tower::update(float dt) {
    if (cooldown > 0.f) cooldown -= dt;
}



void Tower::upgrade() {
    level++;
    damage *= 1.2f;
    range *= 1.05f;
    damageOverTime *= 1.2f;
    burDuration *= 1.1f;
    slowFactor *=1.1f;
}



bool Tower::canFire() const {
    return cooldown <= 0.f;
}

void Tower::resetCooldown() {
    cooldown = fireRate;
}

float Tower::getCooldown() const {
    return cooldown;
}







// 各塔数值已拆到各自派生类构造函数（KingdomRush 风格）









// 各塔的实现已拆到独立文件（ArrowTower.cpp 等，KingdomRush 风格）