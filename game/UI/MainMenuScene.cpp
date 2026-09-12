#include "MainMenuScene.h"
#include "../../engine/SceneRegistry.h"

// 构造函数：把"我是主菜单"报给基类（跟 ArrowTower 报 TowerType 一个套路）
MainMenuScene::MainMenuScene() : Scene(SceneType::MainMenu) {
    //按钮颜色预设
    startButton.SetColors({220,60,60,255}, {255,110,110,255}, {160,30,30,255});
    startButton.SetTextColor({255,255,255,255});
    SinglePlayerBtn.SetColors({220,60,60,255}, {255,110,110,255}, {160,30,30,255});
    SinglePlayerBtn.SetTextColor({255,255,255,255});
    LocalAreaNetworkBtn.SetColors({220,60,60,255}, {255,110,110,255}, {160,30,30,255});
    LocalAreaNetworkBtn.SetTextColor({255,255,255,255});
    TeamSetupButton.SetColors({220,60,60,255}, {255,110,110,255}, {160,30,30,255});
    TeamSetupButton.SetTextColor({255,255,255,255});
    SettingsButton.SetColors({220,60,60,255}, {255,110,110,255}, {160,30,30,255});
    SettingsButton.SetTextColor({255,255,255,255});
    //按钮位置预设
    startButton.setRect({200,200,150,50});
    SinglePlayerBtn.setRect({200,250,150,40});
    LocalAreaNetworkBtn.setRect({200,300,150,40});
    TeamSetupButton.setRect({200,350,150,40});    
    SettingsButton.setRect({200,400,150,50});

    //按钮文字绑定
    startButton.SetLabel("开始游戏",36);
    SinglePlayerBtn.SetLabel("单机模式",36);
    LocalAreaNetworkBtn.SetLabel("局域网联机",36);
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

    // 选择游戏模式按钮
    if (startButton.HandleEvent(e)) {
        showGameMenu = !showGameMenu;
    }

    // 事件要转给按钮：悬停/按下的状态更新靠 HandleEvent（不转，按钮就不会变色）
    if(showGameMenu){
        bool onSinglePlayer = SinglePlayerBtn.HandleEvent(e);
        bool onLocalAreaNetwork = LocalAreaNetworkBtn.HandleEvent(e);
    
        if (onSinglePlayer)     requestSceneChange(SceneType::SinglePlayer);      // 申请切到单机模式
        if (onLocalAreaNetwork) requestSceneChange(SceneType::LocalAreaNetwork);  // 申请切到局域网联机
    }







    if (TeamSetupButton.HandleEvent(e)) {
        requestSceneChange(SceneType::TeamSetup);      // 还没做：引擎拿到空场景会忽略
    }


    if (SettingsButton.HandleEvent(e)) {
        requestSceneChange(SceneType::Settings);       // 同上
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

    // 常驻按钮
    startButton.Render(renderer);
    TeamSetupButton.Render(renderer);
    SettingsButton.Render(renderer);

    // 模式菜单展开时才画那两个（跟 GameScene 的"选择放塔"一个套路）
    if (showGameMenu) {
        SinglePlayerBtn.Render(renderer);
        LocalAreaNetworkBtn.Render(renderer);
    }
    SDL_RenderPresent(renderer);
}

// ===== 报名（自注册）=====
// 这一行就是"加新场景"的全部成本：场景自己报名，别人一个字都不用改
static bool regMainMenuScene = [] {
    SceneRegistry::reg(SceneType::MainMenu, [](SceneType) {
        return std::make_unique<MainMenuScene>();
    });
    return true;
}();
