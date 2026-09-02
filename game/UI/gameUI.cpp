#include "gameUI.h"
#include "HUD.h"
#include "../../engine/UI/HealthBar.h"   // 血条是通用控件，住 engine 层
#include <cstdlib>   // exit()




//⚡构造函数（开机）             好麻烦。这一块还是太缺经验了，没人带干事还是太难了，处处碰壁
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
    //  ⚠️ 相对路径是相对"运行目录"（project_root）的：../ 出去到 gameEngine 根，再进 game/data
    if (!map.loadFromJson("../game/data/filepath.json")) {
        SDL_Log("地图加载失败！请检查 game/data/filepath.json 是否存在。");
        exit(1);
    }
    surchPlaceTowerBtn.setRect({760, 20, 120, 40});    // 选择放塔按钮
    placeArrowTowerBtn.setRect({650, 70, 120, 40});    // 放箭塔按钮
    placeCannonTowerBtn.setRect({650, 120, 120, 40});    // 放炮塔按钮
    placeMagicTowerBtn.setRect({650, 170, 120, 40});    // 放法塔按钮
    placeIceTowerBtn.setRect({650, 220, 120, 40});    // 放冰塔按钮
    placeTarTowerBtn.setRect({650, 270, 120, 40});    // 放焦油塔按钮
    placeGoldTowerBtn.setRect({650, 320, 120, 40});    // 放金币塔按钮
    spawnMonsterBtn.setRect({760, 70, 120, 40});  // 放怪按钮  后边也得拓开，但等我放塔的找到最好的方式再拓😸


    running = true;
}


//析构函数（关机
GameUI::~GameUI() {
    // ⚠️ 塔和怪由 Player 析构统一清理，这里别重复 delete（防双重释放）
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


// （occupy 是 Map 的活，已放回 Map.cpp——GameUI 只负责调用 map.occupy，不碰格子细节）


//处理事件
void GameUI::processEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) running = false;

        // 6 个塔按钮：每个【独立】变量名！（这是你刚才炸的地方）
        bool onArrow  = placeArrowTowerBtn.HandleEvent(event);
        bool onCannon = placeCannonTowerBtn.HandleEvent(event);
        bool onMagic  = placeMagicTowerBtn.HandleEvent(event);
        bool onIce    = placeIceTowerBtn.HandleEvent(event);
        bool onTar    = placeTarTowerBtn.HandleEvent(event);
        bool onGold   = placeGoldTowerBtn.HandleEvent(event);
        bool onMon    = spawnMonsterBtn.HandleEvent(event);

        //  点哪个塔按钮 → 选那种塔 + 进放置模式
        if (onArrow)  { player.setTowerType(TowerType::Arrow);  placingTower = true; }
        if (onCannon) { player.setTowerType(TowerType::Cannon); placingTower = true; }
        if (onMagic)  { player.setTowerType(TowerType::Magic);  placingTower = true; }
        if (onIce)    { player.setTowerType(TowerType::Ice);    placingTower = true; }
        if (onTar)    { player.setTowerType(TowerType::Tar);    placingTower = true; }
        if (onGold)   { player.setTowerType(TowerType::Gold);   placingTower = true; }
        if (onMon)    { player.spawnMonster(map.getPath()[0].x, map.getPath()[0].y); }

        // 放置模式：点地图 → 放当前选中的塔
        if (placingTower && event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
            int col = event.button.x / map.getTileSize();   // 像素 → 格子
            int row = event.button.y / map.getTileSize();
            if (map.isBuildable(col, row)) {
                float cx = col * map.getTileSize() + map.getTileSize()/2.0f;  // 格子中心
                float cy = row * map.getTileSize() + map.getTileSize()/2.0f;
                if (player.placeTower(cx, cy)) {
                    map.occupy(col, row);   // 占格
                }
            }
            placingTower = false;
        }
    }
}


//逻辑更新
void GameUI::update(float dt){
        for (auto m : player.monsters) {
            m->update(dt, map.getPath());
        }

        // 塔自己干活：攻击塔打怪、经济塔产钱（行为收进 Tower::act，多态统一）
        // unique_ptr 不能拷贝，用 auto& 引用遍历
        for (auto& t : player.towers) {
            t->act(player, dt);
        }

        // 清理死掉的怪（倒着删，避免迭代器失效）
        for (int i = (int)player.monsters.size() - 1; i >= 0; i--) {
            if (player.monsters[i]->getHp() <= 0) {
                delete player.monsters[i];
                player.monsters.erase(player.monsters.begin() + i);
            }
        }

        // 到终点扣基地血（基地血归 Player 管，GameUI 不碰血数据）
        // ⚠️ 现在怪到终点后每帧都会扣血；
        //    等做"多怪 + 到终点移除"时改成：扣一次就移除
        for (auto m : player.monsters) {
            if (m->hasReachedEnd(map.getPath())) {
                player.takeBaseDamage(1);   // 让 Player 自己扣，GameUI 只负责汇报
            }
        }
}


//绘制
void GameUI::render(){
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        map.render(renderer);

        // 画塔（蓝色方块）
        for (auto& t : player.towers) {
            SDL_FPoint p = t->getPos();
            SDL_SetRenderDrawColor(renderer, 50, 100, 255, 255);
            SDL_FRect rect = { p.x - 10, p.y - 10, 20, 20 };
            SDL_RenderFillRect(renderer, &rect);
        }

        // 画怪（红色方块）
        for (auto m : player.monsters) {
            SDL_FPoint p = m->getPos();
            SDL_SetRenderDrawColor(renderer, 220, 50, 50, 255);
            SDL_FRect rect = { p.x - 8, p.y - 8, 16, 16 };
            SDL_RenderFillRect(renderer, &rect);
        }
        // 金币框 + 金币数字（左上角）
        drawGoldBox(renderer, 20, 20, 150, 30, player.getGold());

        // 基地血条（金币框下方 y=60，留 10 像素间距）
        // 血条数据统一从 Player 拿（getBaseHealth / getMaxBaseHealth）
        drawHealthBar(renderer, 20, 60, 150, 20,
                      (float)player.getBaseHealth() / (float)player.getMaxBaseHealth());

        // 右侧塔按钮栏（surch 备用 + 6 塔 + 放怪）
        surchPlaceTowerBtn.Render(renderer);
        placeArrowTowerBtn.Render(renderer);
        placeCannonTowerBtn.Render(renderer);
        placeMagicTowerBtn.Render(renderer);
        placeIceTowerBtn.Render(renderer);
        placeTarTowerBtn.Render(renderer);
        placeGoldTowerBtn.Render(renderer);
        spawnMonsterBtn.Render(renderer);
        SDL_RenderPresent(renderer);

}


//主循环
void GameUI::run() {
    while (running) {
        processEvents();    // 处理事件（内部用成员 placingTower）
        update(0.016f);     // 逻辑更新
        render();           // 绘制
        SDL_Delay(16);
    }
}

