#include "Monster.h"
#include <cmath>   // sqrt 用（显式包含，别靠间接）


// 默认构造：先造一只普通怪占位（GameScene 里 monster 成员要先有个默认模样）
Monster::Monster()
    : type(MonsterType::ORDINARY),
      pos{0.0f, 0.0f},
      currentWaypoint(0),
      slowTimer(0.f)
{
    // 默认造一只普通怪（数值和 OrdinaryMonster 一致）
    hp = 100.f; maxHp = 100.f; baseSpeed = 60.f; speed = 60.f;
}


Monster::Monster(MonsterType type, float x, float y)    //重载，两个Monster调用时二选一
    : type(type),
      pos{x, y},
      currentWaypoint(0),      // 出生点，从第 0 个路标出发
      slowTimer(0.f)       // 初始没减速
{
    // 具体数值由派生类构造函数设置（KingdomRush 风格）
}





Monster::~Monster() = default;       //像我这种的笨比必备





bool Monster::hasReachedEnd(const std::vector<SDL_FPoint>& path) const//到没到
{
    if(currentWaypoint >= path.size()) return true;
    return false;
}

bool Monster::isMoving(const std::vector<SDL_FPoint>& path) const//到了就给我停，俩bool辅助update
{
    if(currentWaypoint >= path.size()) return false;
    return true;
}





void Monster::update(float dt,const std::vector<SDL_FPoint>& path) {     //运动模块

    // 持续伤害（焦油）：每秒按 dotDps 烧血，时间烧完停（dotTimer 归零）
    if (dotTimer > 0) {
        takeDamage(dotDps * dt);     // dt 秒 × 每秒伤害 = 这帧烧多少
        dotTimer -= dt;
        if (dotTimer <= 0) { dotTimer = 0; dotDps = 0.f; }   // 烧完清零
    }

    if (slowTimer > 0)      //减速倒计时
    {
        slowTimer -= dt;
        if (slowTimer <= 0) {     // 用 <= 别用 ==（浮点相减不精确，可能刚好跳过 0）
            slowTimer = 0;
            slowStacks = 0;       // 叠层清零（停手就慢慢恢复）
            speed = baseSpeed;    // 减速结束恢复原速
        }
    }

    if (currentWaypoint >= path.size()) {
        return;
    }

    SDL_FPoint target = path[currentWaypoint];    //标记目标

    float dx = target.x - pos.x;               //方向
    float dy = target.y - pos.y;
    float dist = sqrt(dx * dx +dy * dy);
    float step = speed * dt ;

    if (dist <= step) {            // 这帧能到
        pos = target;
        currentWaypoint++;
    } else {                      // 朝目标走一步
        pos.x += dx / dist * step;
        pos.y += dy / dist * step;
    }

}


// 各怪数值已拆到各自派生类构造函数

void Monster::takeDamage(float amount)
{
    hp -= amount;
    if (hp < 0) hp = 0;
}

// 减速：寒冰叠层（越打越慢）—— 每次命中叠一层，速度按 0.5^层数 递减
void Monster::applySlow(float factor, float duration) {
    slowStacks++;                                   // 叠一层：0.5 → 0.25 → 0.125…
    slowTimer = duration;                           // 续满减速时间（持续冻）
    speed = baseSpeed * std::pow(factor, slowStacks);
    if (speed < baseSpeed * 0.3f) speed = baseSpeed * 0.3f;   // 别真冻成 0，留 10% 最低速
}

// 持续伤害（焦油）：挂上"每秒掉血"。（简化版：刷新持续时间，不叠伤害；要叠伤以后再说）
void Monster::applyDot(float dps, float duration) {
    dotDps = dps;
    dotTimer = duration;
}

void Monster::onDeath() {
    // 默认：死了就没了
    // TODO: 特殊怪的 onDeath 还没 override（Split 分裂 / Bom 爆炸 / Poison 毒）
}


 