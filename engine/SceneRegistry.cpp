#include "SceneRegistry.h"
#include <SDL3/SDL.h>      // SDL_Log（查不到时吭一声）
#include <unordered_map>

// 名册本体：用"函数内静态"而不是全局静态变量
// 好处：第一次用到时才构造，绕开"全局对象构造顺序不确定"那个坑
static std::unordered_map<SceneType, SceneRegistry::Creator>& table() {
    static std::unordered_map<SceneType, SceneRegistry::Creator> t;
    return t;
}

// 报名：把 type 和它的创建函数存进名册
void SceneRegistry::reg(SceneType type, Creator creator) {
    table()[type] = std::move(creator);
}

// 创建：查名册 → 有就调它造一个，没有就返回空（调用方负责判断空）
std::unique_ptr<Scene> SceneRegistry::create(SceneType type) {
    auto it = table().find(type);
    if (it == table().end()) {
        // ⚠️ 查不到 = 这个场景没报名。必须吭一声！
        // 不然只会表现为"点了没反应"，能查半天（报名制的暗坑就在这儿：
        // 漏了文件既不报编译错也不报链接错，只有运行到那一刻才知道）
        SDL_Log("[SceneRegistry] SceneType(%d) 没有报名 —— 检查那个场景的 .cpp：注册代码写了吗？加进 build.bat 了吗？",
                (int)type);
        return nullptr;
    }
    return it->second(type);                   // 把 type 原样递进去，让它自己决定怎么造
}
