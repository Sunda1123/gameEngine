#pragma once
#include "Tower.h"

class IceTower : public Tower {//冰
public:
    IceTower(float x, float y);
    void attack() override;
};
