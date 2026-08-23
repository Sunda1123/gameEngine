#pragma once
#include <SDL3/SDL.h>
#include "Map.h"
#include "Monster.h"

// ============================================
// GameUI：把"一帧游戏"打包成一个类
// 以前这些变量散在 main 里 → 现在全是类的成员
// ============================================
class GameUI {
private:
    SDL_Window*   window;     // 窗口
    SDL_Renderer* renderer;   // 渲染器
    Map           map;        // 地图
    Monster       monster;    // 场上的怪（以后可升级成 vector<Monster*>）⚡⚡⚡⚡
    bool          running;    // 游戏还跑不跑
    int           baseHealth; // 基地血量（以后接 Player 就用 player 的）⚡⚡⚡⚡

public:
    GameUI();   // 构造：自动开机
    ~GameUI();  // 析构：自动关机

    void run(); // 主循环

};