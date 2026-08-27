#pragma once
#include <SDL3/SDL.h>
#include "../Map/Map.h"
#include "../Monster/Monster.h"
#include "../Player/Player.h"


class Button {
private:
    SDL_FRect rect_;          // 按钮的位置+大小
    bool hovered_ = false;    // 鼠标是否悬停再按钮上
    bool clicked_ = false;    // 是否正在被按着
public:
    Button(const SDL_FRect& rect) : rect_(rect) {}//构造
    Button() = default;                       // 默认构造：先不设矩形
    void setRect(const SDL_FRect& r) { rect_ = r; }  // 事后设位置大小
    // 处理事件，返回是否被点击
    bool HandleEvent(const SDL_Event& e);
    // 画按钮：按下=深红 / 悬停=浅橙 / 普通=橙
    void Render(SDL_Renderer* r);
};


class GameUI {
private:
    SDL_Window*   window;     // 窗口
    SDL_Renderer* renderer;   // 渲染器
    Map           map;        // 地图
    Player        player;     // 玩家：放塔/放怪都喊它（创建具体类收在 Player 里，GameUI 只依赖基类）
    bool          running;    // 游戏还跑不跑
    int           baseHealth; // 基地血量（以后接 Player 就用 player 的）⚡⚡⚡⚡
    Button        placeTowerBtn;    // 放塔按钮（UI 零件，属于 GameUI）
    Button        spawnMonsterBtn;  // 放怪按钮

public:
    GameUI();   // 构造：自动开机
    ~GameUI();  // 析构：自动关机

    void run(); // 主循环

};