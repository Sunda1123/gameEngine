#pragma once
#include "Tower.h"

class MagicTower : public Tower {//法
public:
    MagicTower(float x, float y);
    void attack() override;
};
