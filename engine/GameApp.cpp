#include "GameApp.h"
#include <cstdlib> 

// 自动开机：SDL + 窗口 + 渲染器（引擎的事，游戏不用管）
GameApp::GameApp(const char* title, int w, int h) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("SDL 初始化失败: %s", SDL_GetError());
        exit(1);   // TODO: 换更优雅的错误处理（现在 exit 太粗暴）🐲
    }
    window = SDL_CreateWindow(title, w, h, SDL_WINDOW_RESIZABLE);
    if (!window) {
        SDL_Log("窗口创建失败: %s", SDL_GetError());
        exit(1);
    }
    renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer) {
        SDL_Log("渲染器创建失败: %s", SDL_GetError());
        exit(1);
    }
    // 注意：这里【不造场景】——引擎不认识任何具体场景，第一个场景等 run() 里问游戏要
}

// 自动关机：清 SDL（引擎的事）
GameApp::~GameApp() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    // currentScene 是 unique_ptr，有虚析构 → 最后一个场景在这里自己收干净
}

// 主循环（发令枪）：引擎只管节奏和平台，内容全交给"当前场景"
void GameApp::run() {
    //问游戏要第一个场景（引擎不知道是啥，也不该知道）
    currentScene = createFirstScene();
    if (!currentScene) {
        SDL_Log("游戏没有提供启动场景，开不了演。");
        return;
    }
    currentScene->enter();        // 上场
    currentScene->setApp(this);   // 接线：把引擎自己的地址交给场景（场景才能申请换场景）

    while (running) {
        // 事件：引擎负责从系统取，一个个喂给场景（场景只管"这一个我怎么办"）
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) running = false;   // 关窗口是引擎级的事件，引擎自己处理
            else currentScene->processEvents(e);
        }

        // ④ 逻辑 + 绘制：全转发给当前场景
        currentScene->update(0.016f);
        currentScene->render(renderer);

        // ⑤ 帧末：有人申请换场景 → 这时候换才安全（场景已经跑完，不在自己函数里了）
        if (pendingScene) {
            std::unique_ptr<Scene> next = createScene(*pendingScene);  // 问游戏层要新场景
            if (next) {                          // 游戏层给了才切（还没做的场景会返回空）
                currentScene->exit();            // 旧的下场
                currentScene = std::move(next);  // 换人（旧的在这儿自动析构）
                currentScene->setApp(this);      // 给新场景接线
                currentScene->enter();           // 新的上场
            }
            pendingScene.reset();                // 信封处理完，抽屉清空
        }

        SDL_Delay(16);
    }

    currentScene->exit();   // ⑤ 退场（停 BGM、存档之类的收尾）
}

// 场景打电话过来："我想换成 XXX"——引擎只记下，不立刻动手
void GameApp::requestSceneChange(SceneType type) {
    
    pendingScene = type;   // 把信封塞进抽屉（真的切换等帧末）
}
