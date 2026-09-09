#pragma once
#include "Tower.h"

class IceTower : public Tower {//冰
public:
    IceTower(float x, float y);
    void attack() override;
    std::unique_ptr<Bullet> fireBullet(SDL_FPoint dir) override;   // 冰塔发冰弹（override 基类）
};
