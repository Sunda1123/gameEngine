#pragma once
#include "../../engine/Scene.h"         // 场景基类：一屏画面（钩子契约在这儿）
#include "../gameplay/World/World.h"    // 游戏世界：地图+玩家+玩法调度（gameplay 层）
#include "../../engine/UI/Button.h"     // Button 通用控件，住 engine 层
#include "../gameplay/Command/Command.h"   // 撤销栈元素：命令基类（放塔具体命令 .cpp 里再 include）
#include <memory>   // unique_ptr（撤销栈装命令）
#include <vector>


// GameScene = 游戏场景：一屏塔防画面（继承 Scene）
// 玩法逻辑在 World（gameplay 层），窗口/主循环在引擎 GameApp 层 —— 三层界限清晰
class GameScene : public Scene {
private:
    World         world;      // 游戏世界：地图+玩家+每帧玩法调度
    bool          placingTower  = false;   //放置模式标志
    bool          showTowerMenu = false;   //塔选择菜单展开没（点"选择放塔"开关）
    Button        placeArrowTowerBtn;   // 放箭塔按钮
    Button        placeCannonTowerBtn;  // 炮塔
    Button        placeMagicTowerBtn;  //法塔
    Button        placeIceTowerBtn;  // 冰塔
    Button        placeTarTowerBtn;  // 焦油塔
    Button        placeGoldTowerBtn;  // 金币塔
    Button        surchPlaceTowerBtn;   //检索放塔按钮
    Button        spawnMonsterBtn;  // 放怪按钮
    Button        undoBtn;       // 撤销按钮（撤回上一步放塔）
    std::vector<std::unique_ptr<Command>> history;   // 操作历史（撤销栈）：每次放塔压一条命令
    void undo();   // 撤回上一步：退钱+删塔+清格（让撤销栈顶命令还账，弹掉它）

public:
    GameScene();   // 构造：准备自己这一屏（载地图、摆按钮）—— 窗口归引擎管

    void processEvents(const SDL_Event& e) override;   // 处理"一个"事件（引擎 poll 好喂进来）
    void update(float dt) override;                    // 转发玩法给 world
    void render(SDL_Renderer* renderer) override;      // 画塔/怪/子弹/按钮/血条
};
