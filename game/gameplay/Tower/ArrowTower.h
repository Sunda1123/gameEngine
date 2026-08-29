#pragma once
#include "Tower.h"

class ArrowTower : public Tower {//箭
public:
    ArrowTower(float x, float y);
    void attack() override;
};
