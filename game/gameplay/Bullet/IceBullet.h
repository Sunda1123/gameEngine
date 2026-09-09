#pragma once
#include "Bullet.h"   // 继承 Bullet（用别人先打招呼）

// 冰弹：普通子弹 + 命中额外给怪减速（冰塔发它）
// 基类管"飞/撞/寿命/扣血"，冰弹只 override onHit 加"减速特效" —— 差异下放
class IceBullet : public Bullet {
    float slowFactor;     // 减速比例（0.5 = 半速）
    float slowDuration;   // 减速持续秒数
public:
    IceBullet(SDL_FPoint pos, SDL_FPoint dir, float damage,
              float slowFactor, float slowDuration, float speed = 300.f)
        : Bullet(pos, dir, damage, speed),
          slowFactor(slowFactor), slowDuration(slowDuration) {}

protected:
    // 命中钩子：扣血之外，给怪挂减速（基类 update 命中时会调 onHit）
    void onHit(Monster* m) override {
        m->applySlow(slowFactor, slowDuration);
    }
};