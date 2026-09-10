#include "MainMenuScene.h"

// TODO: 构造函数
MainMenuScene::MainMenuScene() {
    //按钮颜色预设
    startButton.SetColors({220,60,60,255}, {255,110,110,255}, {160,30,30,255});
    startButton.SetTextColor({255,255,255,255});
    TeamSetupButton.SetColors({220,60,60,255}, {255,110,110,255}, {160,30,30,255});
    TeamSetupButton.SetTextColor({255,255,255,255});
    SettingsButton.SetColors({220,60,60,255}, {255,110,110,255}, {160,30,30,255});
    SettingsButton.SetTextColor({255,255,255,255});
    //按钮位置预设
    startButton.setRect({200,200,150,50});
    TeamSetupButton.setRect({200,300,150,50});    
    SettingsButton.setRect({200,400,150,50});

    //按钮文字绑定
    startButton.SetLabel("开始游戏",36);
    TeamSetupButton.SetLabel("队伍配置",36);
    SettingsButton.SetLabel("设置",36);
}


//这俩给音乐啥的
// TODO: 进入场景时做什么
void MainMenuScene::enter() {

}
// TODO: 离开场景时做什么
void MainMenuScene::exit() {

}

// TODO: 点按钮后的事件，开始游戏，队伍配置，设置
void MainMenuScene::processEvents(const SDL_Event& e) {
    // 事件要转给按钮：悬停/按下的状态更新靠 HandleEvent（不转，按钮就不会变色）
    if (startButton.HandleEvent(e)) {
        // TODO: 请求切换到游戏场景（等 requestSceneChange 接好线再填）
    }
    if (TeamSetupButton.HandleEvent(e)) {
        // TODO: 请求切换到队伍配置场景
    }
    if (SettingsButton.HandleEvent(e)) {
        // TODO: 请求切换到设置场景
    }
}


// TODO: 每帧逻辑
void MainMenuScene::update(float dt) {
    //这个，貌似还没有
}



// TODO: 画标题 + 按钮
void MainMenuScene::render(SDL_Renderer* renderer) {
    //背景布置和屏幕清空
    //⚠️ SDL_SetRenderDrawColor 第一个参数是 renderer，别漏（漏了编不过）
    SDL_SetRenderDrawColor(renderer, 20, 22, 30, 255);
    SDL_RenderClear(renderer);

    // 标题（中文字走 GDI 绘制，所以不用管控制台编码）
    drawTextAt(renderer, "I坤塔防", 200, 100, 48, 255, 255, 255);

    // 三个按钮自己画底色+文字
    startButton.Render(renderer);
    TeamSetupButton.Render(renderer);
    SettingsButton.Render(renderer);
    SDL_RenderPresent(renderer);
}
