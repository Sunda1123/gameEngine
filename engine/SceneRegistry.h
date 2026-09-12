#pragma once
#include <memory>
#include <functional>
#include "Scene.h"   // Scene + SceneType 都在这儿


// 场景注册表（自注册工厂）—— 跟 TowerFactory 是同一个模式
//   每个场景在自己的 .cpp 里"报名"：SceneType → 创建函数
//   好处：加新场景【不用改任何已有文件】，引擎/游戏层都不用维护那个 switch
// ⚠️ 调用方只传 SceneType；"胜负/模式"这类附加信息在【报名时】就写进 lambda 里了
class SceneRegistry {
public:
    using Creator = std::function<std::unique_ptr<Scene>(SceneType)>;

    static void reg(SceneType type, Creator creator);            // 报名：这个 type 由谁来造
    static std::unique_ptr<Scene> create(SceneType type);        // 按 type 造（没报名的 type → 返回空）
};