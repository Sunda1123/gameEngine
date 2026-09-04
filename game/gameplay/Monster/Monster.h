#pragma once
#include <SDL3/SDL.h>
#include <vector>

enum class MonsterType {ORDINARY , TANK , FAST , SPLIT ,BOM , POISON  };//暂时不知道再加点什么
class Monster
{
protected:

    MonsterType type;
    SDL_FPoint pos;          // 当前坐标
    float hp;                // 当前血量  （这色盘真难使，还得让我自己填数试）
    float maxHp;             // 最大血量（用来给SDL3画血条，依旧狗屎色盘）
    float baseSpeed;         // 原始速度，🚑减速结束后恢复到这个值
    float speed;             // 当前速度 
    int currentWaypoint;     // 下一个目标路点的索引（0 是出生点，初始指向 1）
    float slowTimer;         // 减速剩余时间（秒），> 0 说明正在被减速

public:
    Monster();                                  // 默认构造：先占位（GameUI 成员要用）
    Monster(MonsterType type, float x, float y);
    virtual ~Monster(); 
    // TODO: 加"怪能攻击塔"（现在怪只会沿路走）
    virtual void onDeath();   // 死的时候调用，默认啥也不做
    virtual void update(float dt, const std::vector<SDL_FPoint>& path);   //帧调用减速时间，与当前点和方向
    void takeDamage(float amount);        //受到伤害
    void applySlow(float factor, float duration); //减速，被减速时调用
    bool hasReachedEnd(const std::vector<SDL_FPoint>& path) const; //用来判断怪是否到达了基地，来判定当前是否扣血
    bool isMoving(const std::vector<SDL_FPoint>& path) const; //到头就停，先停下来，再考虑把他拔下来放回库里

    const SDL_FPoint& getPos() const { return pos; }
    float getHp() const { return hp; }
    float getMaxHp() const { return maxHp; }
    float getSpeed() const { return speed; }
    MonsterType getType() const { return type; }
    int getWaypointIndex() const { return currentWaypoint; }
};






struct StatusEffect {
    float damagePerSecond;   // 每秒掉多少血
    float remainingTime;     // 还剩几秒（到了就移除）
    float slowFactor;        // 减速多少
};


// 每种怪一个独立文件（KingdomRush 风格）：
// OrdinaryMonster / TankMonster / FastMonster / SplitMonster / BomMonster / PoisonMonster