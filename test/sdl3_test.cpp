#include <SDL3/SDL.h>
#include <iostream>

int main(int argc, char* argv[]) {
    // 1. 初始化SDL视频子系统  ⚠️ SDL3 里 SDL_Init 返回 bool（true=成功），不是 int 0
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // 2. 创建窗口  ⚠️ SDL3 里 SDL_CreateWindow 没有 X/Y 参数了，直接 宽/高
    SDL_Window* window = SDL_CreateWindow(
        "末世引擎 SDL3",     // 窗口标题
        800,                 // 宽度
        600,                 // 高度
        SDL_WINDOW_RESIZABLE // 可调大小
    );

    if (window == nullptr) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // 3. 创建渲染器（用于绘图）  ⚠️ SDL3 第二个参数是 NULL（不用驱动名）
    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);
    if (renderer == nullptr) {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // 4. 主循环：让窗口保持打开
    bool quit = false;
    SDL_Event event;

    while (!quit) {
        // 处理事件队列
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {  // ⚠️ SDL3 里叫 SDL_EVENT_QUIT（SDL2 叫 SDL_QUIT）
                quit = true;
            }
        }

        // 清屏为深色
        SDL_SetRenderDrawColor(renderer, 10, 10, 25, 255);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }

    // 5. 清理资源
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
