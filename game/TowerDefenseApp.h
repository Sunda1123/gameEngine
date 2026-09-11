#pragma once
#include "../engine/GameApp.h"   // 引擎壳：窗口 + 渲染器 + 主循环
#include <memory>

// 塔防的"应用程序"：继承引擎壳，只多回答一个问题——"第一个场景是谁？"
// （游戏层唯一认识"具体场景"的地方；引擎那边只认识抽象的 Scene）
class TowerDefenseApp : public GameApp {
public:
    // 标题和窗口大小归这里定（引擎只管"开一个这么大的窗口"）
    TowerDefenseApp() : GameApp("I坤塔防", 800, 600) {}

protected:
    // 引擎问"第一个场景是谁"，这里回答
    std::unique_ptr<Scene> createFirstScene() override;

    // TODO: 引擎问"这个 SceneType 是哪个场景"，这里回答（游戏层才知道有哪些具体场景）
    std::unique_ptr<Scene> createScene(SceneType type) override;
};
