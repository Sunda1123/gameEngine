#pragma once
#include <SDL3/SDL.h>
#include <vector>
#include "../Monster/Monster.h"

enum class TowerType { Arrow, Cannon, Magic, Ice ,Tar};

class Tower {

    protected:

    TowerType type;
    SDL_FPoint pos;
    float damage{};
    float range{};
    float cooldown{};
    float fireRate{};
    float slowFactor{};
    float damageOverTime{};
    int level{};
    float burDuration{};

    
public:
    explicit Tower(TowerType type, float x, float y);        //explicit防止构造函数进行隐式转换，虽然三参没必要，但加上更严谨
    virtual ~Tower();                 //virtual析构对应Tower
    virtual void update(float dt);                          //帧率（u 跟 v能不能四啊，率跟陆💩）
    virtual void attack() = 0;        //attack的动作纯虚
    void upgrade();            //升级
    bool canFire() const;      //能不能开火，不能整成无限火力卡死我
    void resetCooldown();          //重置攻击冷却


    const SDL_FPoint& getPos() const { return pos; }     //拿坐标
    TowerType getType() const { return type; }        //拿防御塔类型
    float getDamage() const { return damage; }         //取攻击伤害，灌灌伤，骗骗花
    float getRange() const { return range; }             //拿射程
    int getLevel() const { return level; }               //获取当前等级
    float getCooldown() const;                     //看剩余冷却，给UI留着用，哪怕画个攻击冷却条呢
    float getSlowFactor() const { return slowFactor; }         //拿减速比例，给特殊塔用
    float getDamageOverTime() const {return damageOverTime; }    //拿持续伤害，给持续伤害塔
    float getBurDuration() const {return burDuration; }   //持续伤害时间
    //后边加眩晕，感电（跟链表似的伤害传递但逐级递减），这一加东西Monster那边也得跟着动    
    
    Monster* findTarget(const std::vector<Monster*>& monsters);//索敌，找Monster里边的最近的怪

};




// 每种塔一个独立文件（KingdomRush 风格）











/*
class Target
{

public:






protected:


}
*/