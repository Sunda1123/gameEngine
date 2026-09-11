#pragma once
#include <SDL3/SDL.h>
#include <memory>


// 场景基类：一屏"画面"
// 引擎每帧只服务"当前场景"：收输入 → 更新 → 绘制


class GameApp;   // 前置声明：Scene 只需知道"有这么个类型"，不需要知道它长什么样
                 //（Scene 和 GameApp 互相需要 → 头文件里只能拿指针；真要用它的成员就把 include 放进 .cpp）

enum class SceneType {
    MainMenu,          // 主菜单（标题界面，游戏入口）
    SinglePlayer,      // 单人模式（vs AI，本地打电脑）
    LocalAreaNetwork,  // 局域网联机（2v2，同一网络多人对战）（最后阶段的东西） 
    TeamSetup,         // 队伍配置（选单位：怪或者塔）
    Pause,             // 暂停（游戏中暂停菜单）
    GameOver,          // 失败（基地被推平，你输了）
    Victory,           // 胜利（对面基地归零，你赢了）
    Settings,          // 设置（音量/分辨率/按键）
    Credits,           // 制作人员（致谢/关于）
};

class Scene {

public:
    virtual ~Scene() = default;

    // TODO: 进入这个场景时做什么
    virtual void enter() {}

    // TODO: 离开这个场景时做什么
    virtual void exit() {}

    // TODO: 处理一次输入事件
    virtual void processEvents(const SDL_Event& e) {}

    // TODO: 每帧逻辑更新
    virtual void update(float dt) {}

    // TODO: 每帧绘制（用传进来的 renderer 画）
    virtual void render(SDL_Renderer* renderer) = 0;

    // TODO: 成员 —— 记住"引擎在哪"（场景不拥有引擎，只是拿着用）
    GameApp* app_ = nullptr;
    // TODO: 提供接线入口，让引擎在场景上场时把自己接进来
    void setApp(GameApp* a) {app_ = a ;}
    // TODO: 请求切换场景 —— 只是"申请"：把话转给引擎，自己不换（也不能换）
    void requestSceneChange(SceneType newScene);

};
