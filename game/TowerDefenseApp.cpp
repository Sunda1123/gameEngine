#include "TowerDefenseApp.h"
#include "UI/MainMenuScene.h"
#include "UI/GameScene.h"

// 引擎的 run() 开场会喊这一声，问"第一个场景是谁"
// 答案：主菜单先上（以后想改成"直接进游戏"就改这里，引擎一个字都不用动）
std::unique_ptr<Scene> TowerDefenseApp::createFirstScene() {
    return std::make_unique<MainMenuScene>();
}

// 引擎拿到"切换申请"后，会拿 SceneType 来问"这个对应哪个场景"
// 注意：这个 switch 必须住在【游戏层】——引擎一旦认识具体场景，就废了
std::unique_ptr<Scene> TowerDefenseApp::createScene(SceneType type) {
    switch (type) {
        case SceneType::MainMenu:     return std::make_unique<MainMenuScene>();
        case SceneType::SinglePlayer: return std::make_unique<GameScene>();

        // 其他场景还没做：返回空，引擎拿到空就不切（不会崩，也不报错）
        default: return nullptr;
    }
}
