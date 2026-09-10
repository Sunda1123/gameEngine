#pragma once
#include <SDL3/SDL.h>
#include <memory>
#include "Scene.h"

// 引擎"应用"基类：窗口 + 渲染器 + 主循环（发令枪）—— 跟"是啥游戏"无关

class GameApp {
public:
    GameApp(const char* title, int w, int h);   // 自动开机：SDL + 窗口 + 渲染器
    virtual ~GameApp();                          // 自动关机：清 SDL
    void run();                                  // 主循环：驱动"当前场景"跑

protected:
    SDL_Window*   window = nullptr;   // 子类画图要用（protected，子类可见）
    SDL_Renderer* renderer = nullptr;
    bool running = true;
    std::unique_ptr<Scene> currentScene;    // 引擎持有"当前场景"（同一时刻只有一个）

    // 引擎给游戏留的洞（纯虚 = 契约）：第一个场景是谁？我不知道，你说
    virtual std::unique_ptr<Scene> createFirstScene() = 0;

};
