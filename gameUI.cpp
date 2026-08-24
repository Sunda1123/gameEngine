#include "gameUI.h"
#include <cstdlib>   // exit()




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




bool Button::HandleEvent(const SDL_Event& e) {
        // 鼠标是否"按下"且是左键
        if (e.type == SDL_EVENT_MOUSE_BUTTON_DOWN &&
            e.button.button == SDL_BUTTON_LEFT) {
            // 拿鼠标按下的像素坐标
            SDL_FPoint pt = { e.button.x, e.button.y };
            //判断这个点落是不是在按钮矩形 rect_ 里
            if (SDL_PointInRectFloat(&pt, &rect_)) {
                clicked_ = true;
                return true;  // 告诉外层：我被点了
            }
        }
        // 鼠标松开 → 取消按下状态
        if (e.type == SDL_EVENT_MOUSE_BUTTON_UP) {
            clicked_ = false;
        }
        // 鼠标移动→ 更新悬停（悬停 = 提示用户"能点"）
        if (e.type == SDL_EVENT_MOUSE_MOTION) {
            SDL_FPoint pt = { e.motion.x, e.motion.y };
            hovered_ = SDL_PointInRectFloat(&pt, &rect_);
        }
        return false;
}






    // 画按钮：按下=深红 / 悬停=浅橙 / 普通=橙
void Button::Render(SDL_Renderer* r) {
    if (clicked_) {
        SDL_SetRenderDrawColor(r, 200, 80, 60, 255);
    } else if (hovered_) {
        SDL_SetRenderDrawColor(r, 255, 140, 100, 255);
    } else {
        SDL_SetRenderDrawColor(r, 255, 110, 70, 255);
    }
    SDL_RenderFillRect(r, &rect_);
}






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
    monsters.push_back(new Monster(MonsterType::ORDINARY,
                                   map.getPath()[0].x,
                                   map.getPath()[0].y));

    running = true;
    baseHealth = 100;
}




//析构函数（关机
GameUI::~GameUI() {
    for (auto t : towers) delete t;
    for (auto m : monsters) delete m;
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
        for (auto m : monsters) {
            m->update(dt, map.getPath());
        }

        // 到终点扣基地血
        // ⚠️ 现在怪到终点后每帧都会扣血；
        //    等做"多怪 + 到终点移除"时改成：扣一次就移除
        for (auto m : monsters) {
            if (m->hasReachedEnd(map.getPath())) {
                --baseHealth;
                if (baseHealth < 0) baseHealth = 0;
            }
        }

        //  绘制
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        map.render(renderer);

        // 画怪（红色方块）
        for (auto m : monsters) {
            SDL_FPoint p = m->getPos();
            SDL_SetRenderDrawColor(renderer, 220, 50, 50, 255);
            SDL_FRect rect = { p.x - 8, p.y - 8, 16, 16 };
            SDL_RenderFillRect(renderer, &rect);
        }

        SDL_RenderPresent(renderer);

        SDL_Delay(16);   // 固定 1/60 喵
    }
}

