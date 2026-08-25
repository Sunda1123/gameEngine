#include "Monster.h"
#include <cmath>


// 默认构造：先造一只普通怪占位（GameUI 里 monster 成员要先有个默认模样）
Monster::Monster()
    : type(MonsterType::ORDINARY),
      pos{0.0f, 0.0f},
      currentWaypoint(0),
      slowTimer(0.f)
{
    // 默认造一只普通怪（数值和 OrdinaryMonster 一致）
    hp = 100.f; maxHp = 100.f; baseSpeed = 60.f; speed = 60.f;
}


Monster::Monster(MonsterType type, float x, float y)
    : type(type),               //这冒号，没学明白
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
    
    
    if (slowTimer > 0)      //减速倒计时
    {
        slowTimer -= dt;
        if (slowTimer == 0) speed = baseSpeed;
    }

    if (currentWaypoint >= path.size()) {
        return;
    }

    SDL_FPoint target = path[currentWaypoint];    //标记目标

    float dx = target.x - pos.x;               //方向
    float dy = target.y - pos.y;
    float dist = sqrt(dx * dx + dy * dy);
    float step = speed * dt;

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


void Monster::applySlow(float factor, float duration) {
    speed = baseSpeed * factor;
    slowTimer = duration;
}