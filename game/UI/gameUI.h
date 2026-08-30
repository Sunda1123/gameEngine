#pragma once
#include <SDL3/SDL.h>
#include "../gameplay/Map/Map.h"
#include "../gameplay/Monster/Monster.h"
#include "../gameplay/Player/Player.h"
#include "../../engine/UI/Button.h"   // Button 是通用控件，住 engine 层



class GameUI {
private:
    SDL_Window*   window;     // 窗口
    SDL_Renderer* renderer;   // 渲染器
    Map           map;        // 地图
    Player        player;     // 玩家：放塔/放怪都喊它（创建具体类收在 Player 里，GameUI 只依赖基类）
    bool          running;    // 游戏还跑不跑
    bool          placingTower  = false;   //放置模式标志
    Button        placeTowerBtn;    // 放塔按钮（UI 零件，属于 GameUI）
    Button        spawnMonsterBtn;  // 放怪按钮

public:
    GameUI();   // 构造：自动开机
    ~GameUI();  // 析构：自动关机
    void render();//绘制
    void update(float dt);//逻辑更新
    void processEvents();//处理事件
    void run(); // 主循环

};