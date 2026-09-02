#pragma once
#include "Tower.h"
#include <memory>
#include <functional>   // std::function（万能可调用盒子）
#include <unordered_map>

// "造塔动作"的类型：喂坐标 → 吐一座塔
// 用 std::function 而不是裸函数指针：
// lambda 返回子类(ArrowTower)时，函数指针签名要"分毫不差"会转不过去（unique_ptr<ArrowTower> 变不了 unique_ptr<Tower>）
// std::function 做类型擦除，自动接受这种转换 —— 找零收银台 vs 只收整钞😄
using TowerCreator = std::function<std::unique_ptr<Tower>(float, float)>;  //终究也是走上using了

class TowerFactory {
public:
    static std::unique_ptr<Tower> create(TowerType type, float x, float y); // 点名造塔
    static void registerTower(TowerType type, TowerCreator fn);             // 报名入口
private:
    static std::unordered_map<TowerType, TowerCreator>& table(); // 名册本体
};