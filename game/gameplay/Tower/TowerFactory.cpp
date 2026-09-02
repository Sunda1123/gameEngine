#include "TowerFactory.h"//这种东西怎么越学越多                 

// 名册本体：函数内 static（懒汉）——第一次用到才建，不怕"报名顺序"问题
std::unordered_map<TowerType, TowerCreator>& TowerFactory::table() {
    static std::unordered_map<TowerType, TowerCreator> t;
    return t;
}

// 报名：往名册登记 "这个类型 → 这个造法"
void TowerFactory::registerTower(TowerType type, TowerCreator fn) {
    table()[type] = fn;
}

// 点名：按类型查名册，查到就造；查不到返回空（Player 自己兜底）
std::unique_ptr<Tower> TowerFactory::create(TowerType type, float x, float y) {
    auto it = table().find(type);
    if (it == table().end()) return nullptr;
    return it->second(x, y);   // 叫名册里那座塔"造一个"
}