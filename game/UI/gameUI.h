#pragma once
#include "../../engine/GameApp.h"       // 引擎壳：窗口+渲染器+run 主循环（发令枪）
#include "../gameplay/World/World.h"    // 游戏世界：地图+玩家+玩法调度（gameplay 层）
#include "../../engine/UI/Button.h"     // Button 通用控件，住 engine 层
#include "../gameplay/Command/Command.h"   // 撤销栈元素：命令基类（放塔具体命令 .cpp 里再 include）
#include <memory>   // unique_ptr（撤销栈装命令）
#include <vector>


// GameUI = 继承引擎壳(GameApp)，只填三个钩子 + 塔防界面（按钮）
// 玩法逻辑在 World（gameplay 层）—— 引擎/游戏/界面 界限清晰
class GameUI : public GameApp {
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
    GameUI();   // 构造：引擎开机(GameApp 开窗口) + 本类载地图/摆按钮

protected:
    // 三个钩子：引擎 run 每帧喊，游戏填内容
    void processEvents() override;   // 收输入（点按钮/点地图）
    void update(float dt) override;  // 转发玩法给 world
    void render() override;          // 画塔/怪/子弹/按钮/血条
};