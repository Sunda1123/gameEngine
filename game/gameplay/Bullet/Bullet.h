#pragma once
#include <SDL3/SDL.h>
#include <vector>
#include "../Monster/Monster.h"


class Bullet {
public:
    Bullet(SDL_FPoint pos, SDL_FPoint dir, float damage, float speed = 300.f);   // speed 有默认，塔发射可以不传
    void update(float dt, const std::vector<Monster*>& monsters);  // 每帧飞 + 自己撞怪
    bool isDead() const { return lifetime <= 0; }   // 死了 GameUI 倒着删
    SDL_FPoint getPos() const { return pos; }       // 给 GameUI 画
private:
    SDL_FPoint pos;         // 当前坐标
    SDL_FPoint dir;         // 方向（单位向量）
    float speed = 300.f;    // 速度（每秒像素）
    float damage;           // 撞上扣的血
    float lifetime = 2.f;   // 还能活多久
};