#pragma once
#include <SDL3/SDL.h>
#include <vector>
#include "../Monster/Monster.h"


class Bullet {
public:
    Bullet(SDL_FPoint pos, SDL_FPoint dir, float damage, float speed = 300.f);   // speed 有默认，塔发射可以不传
    virtual ~Bullet() = default;   // ★ 多态基类必须有 virtual 析构（不然删派生子弹时漏调派生析构）
    void update(float dt, const std::vector<Monster*>& monsters);  // 每帧飞 + 自己撞怪
    bool isDead() const { return lifetime <= 0; }   // 死了 GameScene 倒着删
    SDL_FPoint getPos() const { return pos; }       // 给 GameScene 画
    virtual void onHit(Monster* m) {}   //命中后的特效，默认没有（派生子弹 override 加自己的）
    virtual SDL_Color getColor() const { return {255, 230, 80, 255}; }  // 子弹颜色（默认黄，焦油弹 override 改绿）
private:
    SDL_FPoint pos;         // 当前坐标
    SDL_FPoint dir;         // 方向（单位向量）
    float speed = 300.f;    // 速度（每秒像素）
    float damage;           // 撞上扣的血
    float lifetime = 2.f;   // 还能活多久
};