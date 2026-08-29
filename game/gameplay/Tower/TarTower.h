#pragma once
#include "Tower.h"

class TarTower : public Tower {
public:
    TarTower(float x, float y);
    void attack() override;
};
