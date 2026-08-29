#pragma once
#include "Tower.h"

class CannonTower : public Tower {//炮
public:
    CannonTower(float x, float y);
    void attack() override;
};
