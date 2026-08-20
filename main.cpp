#include <SDL3/SDL.h>
#include "Map.h"

int main(int argc, char* argv[]) {
    //  初始化 SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("SDL 初始化失败: %s", SDL_GetError());
        return 1;
    }




    // 创建窗口
    SDL_Window* window = SDL_CreateWindow("地图加载示例", 800, 600, SDL_WINDOW_RESIZABLE);
    if (!window) {
        SDL_Log("窗口创建失败: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }





    // 创建渲染器
    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer) {
        SDL_Log("渲染器创建失败: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }





    // 定义 Map 对象
    Map map;





    //加载地图 JSON
    if (!map.loadFromJson("filepath.json")) {
        SDL_Log("地图加载失败！请检查 filename.json 是否存在。");
        return 1;
    }




    // 游戏主循环标志
    int running = 1;
    SDL_Event event;
    while (running) {
        // 处理事件
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = 0;
            }
        }











        //绘制流程开始

        // 清屏
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // 渲染地图
        map.render(renderer);

        //显示到屏幕
        SDL_RenderPresent(renderer);
        
        // 控制帧率
        SDL_Delay(16);
    }







    // 清理资源
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

