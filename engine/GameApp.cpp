#include "GameApp.h"
#include <cstdlib>   // exit()

// 自动开机：SDL + 窗口 + 渲染器（引擎的事，游戏不用管）
GameApp::GameApp(const char* title, int w, int h) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("SDL 初始化失败: %s", SDL_GetError());
        exit(1);   // TODO: 换更优雅的错误处理（现在 exit 太粗暴）
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
}

// 自动关机：清 SDL（引擎的事）
GameApp::~GameApp() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

// 主循环（发令枪）：固定节奏喊三个钩子，具体干啥由游戏填
void GameApp::run() {
    while (running) {
        processEvents();    // 钩子①：收输入（游戏填）
        update(0.016f);     // 钩子②：逻辑（游戏填）
        render();           // 钩子③：画（游戏填）
        SDL_Delay(16);
    }
}
