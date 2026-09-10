#include "TowerDefenseApp.h"
#include "UI/MainMenuScene.h"

// 引擎的 run() 开场会喊这一声，问"第一个场景是谁"
// 答案：主菜单先上（以后想改成"直接进游戏"就改这里，引擎一个字都不用动）
std::unique_ptr<Scene> TowerDefenseApp::createFirstScene() {
    return std::make_unique<MainMenuScene>();
}
