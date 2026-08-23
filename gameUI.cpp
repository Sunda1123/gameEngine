#include "gameUI.h"
#include <cstdlib>   // exit()

//⚡构造函数（开机）
GameUI::GameUI() {
    //  初始化 SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("SDL 初始化失败: %s", SDL_GetError());
        exit(1);   // 开机失败直接退出（⚡⚡⚡以后可换更优雅的错误处理）
    }

    //  创建窗口
    window = SDL_CreateWindow("地图加载示例", 800, 600, SDL_WINDOW_RESIZABLE);
    if (!window) {
        SDL_Log("窗口创建失败: %s", SDL_GetError());
        exit(1);
    }

    //  创建渲染器
    renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer) {
        SDL_Log("渲染器创建失败: %s", SDL_GetError());
        exit(1);
    }

    //  加载地图
    if (!map.loadFromJson("filepath.json")) {
        SDL_Log("地图加载失败！请检查 filepath.json 是否存在。");
        exit(1);
    }

    //  创建怪物（⚡ 以后改成鼠标点按钮创建）
    monster = Monster(MonsterType::ORDINARY,
                      map.getPath()[0].x,
                      map.getPath()[0].y);

    running = true;
    baseHealth = 100;
}

//析构函数（关机
GameUI::~GameUI() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

//主循环
void GameUI::run() {
    SDL_Event event;
    while (running) {
        // ① 处理事件
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
        }

        //让怪沿路径走
        float dt = 0.016f;                     // 1/60 秒每帧
        monster.update(dt, map.getPath());

        // 到终点扣基地血
        // ⚠️ 现在只有一只怪，到终点后每帧都会扣血；
        //    等做"多怪 + 到终点移除"时改成：扣一次就移除
        if (monster.hasReachedEnd(map.getPath())) {
            --baseHealth;
            if (baseHealth < 0) baseHealth = 0;
        }

        //  绘制
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        map.render(renderer);

        // 画怪（红色方块）
        SDL_FPoint p = monster.getPos();
        SDL_SetRenderDrawColor(renderer, 220, 50, 50, 255);
        SDL_FRect m = { p.x - 8, p.y - 8, 16, 16 };
        SDL_RenderFillRect(renderer, &m);

        SDL_RenderPresent(renderer);

        SDL_Delay(16);   // 固定 1/60 喵
    }
}

// 画血条（⚡⚡⚡自由函数，备用；以后接进 run
void drawHealthBar(SDL_Renderer* renderer, int x, int y, int w, int h, float hpPercent) {
    // 限制一下百分比
    if (hpPercent < 0.0f) hpPercent = 0.0f;
    if (hpPercent > 1.0f) hpPercent = 1.0f;

    // 1. 背景条（深色底）
    SDL_FRect bgRect = { (float)x, (float)y, (float)w, (float)h };
    SDL_SetRenderDrawColor(renderer, 60, 60, 60, 255);   // 深灰
    SDL_RenderFillRect(renderer, &bgRect);

    // 2. 前景条（根据血量变色 + 宽度随百分比缩放）
    int fillW = (int)(w * hpPercent);
    SDL_FRect fillRect = { (float)x, (float)y, (float)fillW, (float)h };

    if (hpPercent > 0.6f)
        SDL_SetRenderDrawColor(renderer, 0, 200, 0, 255);    // 绿
    else if (hpPercent > 0.3f)
        SDL_SetRenderDrawColor(renderer, 200, 200, 0, 255);  // 黄
    else
        SDL_SetRenderDrawColor(renderer, 200, 0, 0, 255);    // 红

    SDL_RenderFillRect(renderer, &fillRect);

    // 3. 可选：画个边框
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);    // 白色
    SDL_RenderRect(renderer, &bgRect);   // ← SDL3 里画边框用这个
}