#pragma once
#include "../../engine/Scene.h"
#include "../../engine/UI/Button.h"
#include "../../engine/UI/TextRenderer.h"
#include <SDL3/SDL.h>

// 主菜单场景：一屏标题 + "开始游戏"按钮
class MainMenuScene : public Scene {

    // TODO: 它需要哪些成员？（按钮？renderer？）
    Button startButton;  //开始游戏
    Button SettingsButton; //设置
    Button TeamSetupButton; //队伍配置

public:
    // TODO: 构造函数要什么参数，你来定
    MainMenuScene();

    // TODO: 进入时做什么
    void enter() override;

    // TODO: 离开时做什么
    void exit() override;

    // TODO: 点了按钮时做什么,三个按钮，得分分了
    void processEvents(const SDL_Event& e) override;

    // TODO: 每帧逻辑
    void update(float dt) override;

    // TODO: 画标题 + 按钮
    void render(SDL_Renderer* renderer) override;
};
