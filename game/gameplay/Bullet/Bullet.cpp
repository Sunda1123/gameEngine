#include "Bullet.h"
#include "../../../engine/math/Math2D.h"



Bullet::Bullet(SDL_FPoint pos, SDL_FPoint dir, float damage, float speed)
    : pos(pos), dir(dir), damage(damage), speed(speed) {}




void Bullet::update(float dt, const std::vector<Monster*>& monsters) {
    pos.x += dir.x * speed * dt;
    pos.y += dir.y * speed * dt;

    for (auto m : monsters) {
        if (dist(pos, m->getPos()) < 12.f) {   // 距离小于12 像素 = 命中
            m->takeDamage(damage);
            onHit(m);          // 钩子：派生子弹的额外特效（冰弹→减速）
            lifetime = 0;      // 打中就死，GameScene 删这个子弹
            return;
        }
    }

    lifetime -= dt;
}