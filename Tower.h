#pragma once
#include <SDL3/SDL.h>

enum class TowerType { Arrow, Cannon, Magic, Ice };

class Tower {
public:
    Tower(TowerType type, float x, float y);
    virtual ~Tower();
    virtual void update(float dt);
    virtual void attack() = 0;
    void upgrade();
    bool canFire() const;
    void resetCooldown();



    const SDL_FPoint& getPos() const { return pos; }
    TowerType getType() const { return type; }
    float getDamage() const { return damage; }
    float getRange() const { return range; }
    int getLevel() const { return level; }
    float getCooldown() const;
    float getSlowFactor() const { return slowFactor; }

protected:
    void initStats();

    TowerType type;
    SDL_FPoint pos;
    float damage{};
    float range{};
    float cooldown{};
    float fireRate{};
    float slowFactor{};
    int level{};
};




//塔类型和每个塔的功能

class ArrowTower : public Tower {
public:
    ArrowTower(float x, float y);
    void attack() override;
};

class CannonTower : public Tower {
public:
    CannonTower(float x, float y);
    void attack() override;
};

class MagicTower : public Tower {
public:
    MagicTower(float x, float y);
    void attack() override;
};

class IceTower : public Tower {
public:
    IceTower(float x, float y);
    void attack() override;
};



/*
class Target
{

public:






protected:


}
*/