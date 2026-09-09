#pragma once
#include "Tower.h"

class TarTower : public Tower {
public:
    TarTower(float x, float y);
    std::unique_ptr<Bullet> fireBullet(SDL_FPoint dir) override;   // 焦油塔发焦油弹（挂持续伤害）
};
