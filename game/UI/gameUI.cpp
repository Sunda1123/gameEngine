#include "gameUI.h"
#include "HUD.h"
#include "../../engine/UI/HealthBar.h"   // 血条是通用控件，住 engine 层
#include <cstdlib>   // exit()




//⚡构造函数（开机）             好麻烦。这一块还是太缺经验了，没人带干事还是太难了，处处碰壁
// 构造：引擎壳(GameApp)自动开机（SDL+窗口+渲染器），这里只干"游戏的事"：载地图+摆按钮
GameUI::GameUI() : GameApp("地图加载示例", 800, 600) {
    //  加载地图（地图归 World 管）
    //  ⚠️ 相对路径是相对"运行目录"（project_root）的：../ 出去到 gameEngine 根，再进 game/data
    if (!world.loadMap("../game/data/filepath.json")) {
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
    spawnMonsterBtn.setRect({760, 70, 120, 40});  // 放怪按钮 TODO: 以后也要做成多怪选择（等我放塔的方式定下来再拓😸）

    //绑定文字：rect 就是框，字按 rect 居中贴上去（常驻按钮也要字，不然没字怪怪的）
    placeArrowTowerBtn.SetLabel("箭塔",   18);
    placeCannonTowerBtn.SetLabel("加农炮", 18);
    placeMagicTowerBtn.SetLabel("魔法",   18);
    placeIceTowerBtn.SetLabel("冰",      18);
    placeTarTowerBtn.SetLabel("焦油",    18);
    placeGoldTowerBtn.SetLabel("金币",   18);

    surchPlaceTowerBtn.SetLabel("选择放塔", 18);
    spawnMonsterBtn.SetLabel("放怪", 18);
    running = true;
}

// （析构不用写：SDL 清理归引擎基类 GameApp 析构管；塔/怪归 World/Player 析构管）


// （occupy 是 Map 的活，已放回 Map.cpp——GameUI 只负责调用 map.occupy，不碰格子细节）


//处理事件
void GameUI::processEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) running = false;

        // 记录：这次事件是不是点到了 UI 按钮（点了就不当"点地图放塔"，防误触重置 placingTower）
        bool clickedUI = false;

        // "选择放塔"按钮：点一下展开/收起塔菜单（终于不是摆设了）
        if (surchPlaceTowerBtn.HandleEvent(event)) {
            showTowerMenu = !showTowerMenu;
            clickedUI = true;
        }

        // 放怪按钮：常驻，点就出怪
        if (spawnMonsterBtn.HandleEvent(event)) {
            world.player.spawnMonster(world.map.getPath()[0].x, world.map.getPath()[0].y);
            clickedUI = true;
        }

        // 塔菜单展开时才接收 6 个塔按钮（点哪个→选它+进放置+收起菜单）
        if (showTowerMenu) {
            bool onArrow  = placeArrowTowerBtn.HandleEvent(event);
            bool onCannon = placeCannonTowerBtn.HandleEvent(event);
            bool onMagic  = placeMagicTowerBtn.HandleEvent(event);
            bool onIce    = placeIceTowerBtn.HandleEvent(event);
            bool onTar    = placeTarTowerBtn.HandleEvent(event);
            bool onGold   = placeGoldTowerBtn.HandleEvent(event);
            if (onArrow || onCannon || onMagic || onIce || onTar || onGold) clickedUI = true;

            if (onArrow)  { world.player.setTowerType(TowerType::Arrow);  placingTower = true; showTowerMenu = false; }
            if (onCannon) { world.player.setTowerType(TowerType::Cannon); placingTower = true; showTowerMenu = false; }
            if (onMagic)  { world.player.setTowerType(TowerType::Magic);  placingTower = true; showTowerMenu = false; }
            if (onIce)    { world.player.setTowerType(TowerType::Ice);    placingTower = true; showTowerMenu = false; }
            if (onTar)    { world.player.setTowerType(TowerType::Tar);    placingTower = true; showTowerMenu = false; }
            if (onGold)   { world.player.setTowerType(TowerType::Gold);   placingTower = true; showTowerMenu = false; }
        }

        // 放置模式：点地图 → 放当前选中的塔（这次点了 UI 按钮就不算点地图）
        if (placingTower && !clickedUI && event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
            int col = event.button.x / world.map.getTileSize();   // 像素 → 格子
            int row = event.button.y / world.map.getTileSize();
            if (world.map.isBuildable(col, row)) {
                float cx = col * world.map.getTileSize() + world.map.getTileSize()/2.0f;  // 格子中心
                float cy = row * world.map.getTileSize() + world.map.getTileSize()/2.0f;
                if (world.player.placeTower(cx, cy)) {
                    world.map.occupy(col, row);   // 占格
                }
            }
            placingTower = false;
        }
    }
}


//逻辑更新：玩法全在 World 里，界面只负责喊它
void GameUI::update(float dt){
    world.update(dt);
}


//绘制
void GameUI::render(){
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        world.map.render(renderer);

        // 画塔（蓝色方块）
        for (auto& t : world.player.towers) {
            SDL_FPoint p = t->getPos();
            SDL_SetRenderDrawColor(renderer, 50, 100, 255, 255);
            SDL_FRect rect = { p.x - 10, p.y - 10, 20, 20 };
            SDL_RenderFillRect(renderer, &rect);
        }

        // 画怪（红色方块）
        for (auto m : world.player.monsters) {
            SDL_FPoint p = m->getPos();
            SDL_SetRenderDrawColor(renderer, 220, 50, 50, 255);
            SDL_FRect rect = { p.x - 8, p.y - 8, 16, 16 };
            SDL_RenderFillRect(renderer, &rect);
        }

        // 画子弹（黄色小点）
        for (auto& b : world.player.bullets) {
            SDL_FPoint p = b->getPos();
            SDL_SetRenderDrawColor(renderer, 255, 230, 80, 255);
            SDL_FRect rect = { p.x - 3, p.y - 3, 6, 6 };
            SDL_RenderFillRect(renderer, &rect);
        }
        // 金币框 + 金币数字（左上角）
        drawGoldBox(renderer, 20, 20, 150, 30, world.player.getGold());

        // 基地血条（金币框下方 y=60，留 10 像素间距）
        // 血条数据统一从 Player 拿（getBaseHealth / getMaxBaseHealth）
        drawHealthBar(renderer, 20, 60, 150, 20,
                      (float)world.player.getBaseHealth() / (float)world.player.getMaxBaseHealth());

        // 右侧栏：常驻 = 选择放塔 + 放怪；点"选择放塔"才展开 6 塔菜单
        surchPlaceTowerBtn.Render(renderer);
        if (showTowerMenu) {
            placeArrowTowerBtn.Render(renderer);
            placeCannonTowerBtn.Render(renderer);
            placeMagicTowerBtn.Render(renderer);
            placeIceTowerBtn.Render(renderer);
            placeTarTowerBtn.Render(renderer);
            placeGoldTowerBtn.Render(renderer);
        }
        spawnMonsterBtn.Render(renderer);
        SDL_RenderPresent(renderer);

}

// 主循环不用写：run() 继承自引擎 GameApp（发令枪），自动调上面三个钩子

