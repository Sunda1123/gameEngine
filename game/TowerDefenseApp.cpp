#include "TowerDefenseApp.h"
#include "../engine/SceneRegistry.h"

// 引擎的 run() 开场会喊这一声，问"第一个场景是谁"
// 现在答案也不用写死具体类了：报一个 SceneType 就行
std::unique_ptr<Scene> TowerDefenseApp::createFirstScene() {
    return SceneRegistry::create(SceneType::MainMenu);
}

// 引擎拿到"切换申请"后，会拿 SceneType 来问"这个对应哪个场景"
// 现在也不用 switch 了 —— 名册里报名过的场景，直接查表就有
std::unique_ptr<Scene> TowerDefenseApp::createScene(SceneType type) {
    return SceneRegistry::create(type);
}


