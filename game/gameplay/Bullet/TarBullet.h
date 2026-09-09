#pragma once
#include "Bullet.h"

// 焦油弹：普通子弹 + 命中给怪挂"持续伤害"（每秒烧血）—— 焦油塔发它
// 跟冰弹同套路：基类管"飞/撞/扣血"，它只 override onHit 加 DOT 特效 —— 差异下放
class TarBullet : public Bullet {
    float dotDps;       // 每秒掉多少血（焦油烧）
    float dotDuration;  // 烧几秒（持续伤害时间）
public:
    TarBullet(SDL_FPoint pos, SDL_FPoint dir, float damage,
              float dotDps, float dotDuration, float speed = 300.f)
        : Bullet(pos, dir, damage, speed),
          dotDps(dotDps), dotDuration(dotDuration) {}

    // 颜色：焦油弹画成焦绿色（基类默认黄色），一眼认出是"烧"不是"撞"
    SDL_Color getColor() const override { return {90, 180, 70, 255}; }

protected:
    // 命中钩子：撞上那一下扣血归基类，这里额外给怪挂上持续伤害
    void onHit(Monster* m) override {
        m->applyDot(dotDps, dotDuration);
    }
};
