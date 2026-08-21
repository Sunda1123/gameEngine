#pragma once
#include <SDL3/SDL.h>
#include<vector>

enum class MonsterType {ORDINARY , TANK , FAST , SPLIT ,BOM , POISON  };//暂时不知道再加点什么
class Monster
{

public:
    Monster(MonsterType type, float x, float y);
    virtual ~Monster(); 
    //后边再加怪可以攻击塔
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


protected:

    void initStats();          //初始化怪物类型和初始数据💩（到现在我都想不出来该给怪一个什么形象）
    MonsterType type;
    SDL_FPoint pos;          // 当前坐标
    float hp;                // 当前血量  （这色盘真难使，还得让我自己填数试）
    float maxHp;             // 最大血量（用来给SDL3画血条，依旧狗屎色盘）
    float baseSpeed;         // 原始速度，🚑减速结束后恢复到这个值
    float speed;             // 当前速度 
    int currentWaypoint;     // 下一个目标路点的索引（0 是出生点，初始指向 1）
    float slowTimer;         // 减速剩余时间（秒），> 0 说明正在被减速


};






struct StatusEffect {
    float damagePerSecond;   // 每秒掉多少血
    float remainingTime;     // 还剩几秒（到了就移除）
    float slowFactor;        // 减速多少
};


/*    留着写怪的特殊功能，到时候顺便把怪的伤害和范围补上，到后期吧，伤害和范围到后期补上，因为还得给塔加单独血条要不
class Monster : public Monster {//普通
public:

};

class Monster : public Monster {//坦克
public:

};

class Monster : public Monster {//速度
public:

};

class Monster : public Monster {//分裂
public:

};

class Monster : public Monster {//爆炸
public:

};

class Monster : public Monster {//毒
public:

};

*/