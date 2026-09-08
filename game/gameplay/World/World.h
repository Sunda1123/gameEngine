#pragma once
#include <string>
#include "../Map/Map.h"
#include "../Player/Player.h"

// 游戏"世界"：玩法的大本营（gameplay 层）
// 它知道这局游戏有：一张地图 map + 一个玩家 player（塔/怪/子弹列表都归 Player 管）
// 每帧 update(dt) = 玩法调度：怪走、塔打、子弹飞、清死物、终点扣血
// GameUI（界面/引擎壳）只管喊 world.update() 和画，不再亲自管玩法 —— 界限回来了
class World {
public:
    Map    map;      // 地图
    Player player;   // 玩家（持塔/怪/子弹）

    bool loadMap(const std::string& filepath);  // 载入地图（失败返回 false，由外面提示）
    void update(float dt);                      // 每帧玩法调度（从 GameUI 搬进来的）
};
