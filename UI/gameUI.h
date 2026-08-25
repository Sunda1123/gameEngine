#pragma once
#include <SDL3/SDL.h>
#include "../Map/Map.h"
#include "../Monster/Monster.h"
#include "../Player/Player.h"

// ============================================
// GameUI：把"一帧游戏"打包成一个类
// 以前这些变量散在 main 里 → 现在全是类的成员
// ============================================
class GameUI {
private:
    SDL_Window*   window;     // 窗口
    SDL_Renderer* renderer;   // 渲染器
    Map           map;        // 地图
    std::vector<Tower*> towers;  //塔
    std::vector<Monster*> monsters;   //怪
    bool          running;    // 游戏还跑不跑
    int           baseHealth; // 基地血量（以后接 Player 就用 player 的）⚡⚡⚡⚡

public:
    GameUI();   // 构造：自动开机
    ~GameUI();  // 析构：自动关机

    void run(); // 主循环

};


//用来创建一个按钮的类
class Button {
public:
    Button(const SDL_FRect& rect) : rect_(rect) {}//构造

    // 处理事件，返回是否被点击
    bool HandleEvent(const SDL_Event& e);
    // 画按钮：按下=深红 / 悬停=浅橙 / 普通=橙
    void Render(SDL_Renderer* r);
private:
    SDL_FRect rect_;          // 按钮的位置+大小
    bool hovered_ = false;    // 鼠标是否悬停再按钮上
    bool clicked_ = false;    // 是否正在被按着
};