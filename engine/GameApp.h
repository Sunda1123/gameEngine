#pragma once
#include <SDL3/SDL.h>

// 引擎"应用"基类：窗口 + 渲染器 + 主循环（发令枪）—— 跟"是啥游戏"无关
// 游戏继承它，只填三个钩子 = 游戏内容：
//   class MyGame : public GameApp {
//       MyGame() : GameApp("标题", 800, 600) {}
//   protected:
//       void processEvents() override;  // 收输入
//       void update(float dt) override; // 逻辑
//       void render() override;         // 画
//   };
class GameApp {
public:
    GameApp(const char* title, int w, int h);   // 自动开机：SDL + 窗口 + 渲染器
    virtual ~GameApp();                          // 自动关机：清 SDL
    void run();                                  // 主循环：processEvents→update→render→Delay

protected:
    SDL_Window*   window = nullptr;   // 子类画图要用（protected，子类可见）
    SDL_Renderer* renderer = nullptr;
    bool running = true;

    // 三个钩子：游戏内容来填（纯虚 = 契约）
    virtual void processEvents() = 0;
    virtual void update(float dt) = 0;
    virtual void render() = 0;
};
