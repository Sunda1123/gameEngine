#pragma once
#include "Tower.h"

// 经济塔：不打怪，定时产钱（增益类建筑）
// attack 继承基类默认空壳（不攻击），只重写 act = 产钱
class GoldTower : public Tower {
public:
    GoldTower(float x, float y);
    void act(Player& player, float dt) override;   // 重写行为 = 产钱
};
