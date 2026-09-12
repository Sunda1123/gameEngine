#include "ResultScene.h"
#include "../../engine/SceneRegistry.h"

// 构造：把自己的"结果类型"报给基类（GameOver 或 Victory）
ResultScene::ResultScene(SceneType type) : Scene(type) {
    // 再来一局（蓝色系）
    retryBtn.setRect({180, 320, 180, 56});
    retryBtn.SetLabel("再来一局", 24);
    retryBtn.SetColors({60, 140, 220, 255}, {110, 180, 255, 255}, {30, 100, 170, 255});
    retryBtn.SetTextColor({255, 255, 255, 255});

    // 回主菜单（灰色系）
    homeBtn.setRect({440, 320, 180, 56});
    homeBtn.SetLabel("回主菜单", 24);
    homeBtn.SetColors({120, 120, 130, 255}, {170, 170, 180, 255}, {80, 80, 90, 255});
    homeBtn.SetTextColor({255, 255, 255, 255});
}

// 进场/退场：暂时给音乐留着，先空着
void ResultScene::enter() {}
void ResultScene::exit() {}

// 点按钮 → 申请换场景（还是那条"场景只申请，引擎来执行"的老路）
void ResultScene::processEvents(const SDL_Event& e) {
    if (retryBtn.HandleEvent(e)) {
        // 再来一局：单机局回单机，联机局回联机（联机场景还没做，点了会没反应）
        requestSceneChange(isLAN() ? SceneType::LocalAreaNetwork : SceneType::SinglePlayer);
    }
    if (homeBtn.HandleEvent(e)) {
        requestSceneChange(SceneType::MainMenu);       // 回主菜单
    }
}

void ResultScene::update(float dt) {
    // 结算界面不用更新逻辑（以后有动画再放这儿）
}

void ResultScene::render(SDL_Renderer* renderer) {
    // 背景：赢了发绿，输了发红（一眼能看出来）
    if (isVictory()) SDL_SetRenderDrawColor(renderer, 16, 40, 20, 255);
    else             SDL_SetRenderDrawColor(renderer, 40, 16, 20, 255);
    SDL_RenderClear(renderer);

    if (isVictory()) drawTextAt(renderer, "vectory", 300, 140, 64, 120, 255, 120);
    else             drawTextAt(renderer, "You are lost", 260, 140, 56, 255, 120, 120);

    retryBtn.Render(renderer);
    homeBtn.Render(renderer);
    SDL_RenderPresent(renderer);
}

// 赢没赢：问基类存的那个 type_（单机/联机各有一套胜败）
bool ResultScene::isVictory() const {
    return getType() == SceneType::Victory1 || getType() == SceneType::Victory2;
}

// 是不是联机局的结算
bool ResultScene::isLAN() const {
    return getType() == SceneType::GameOver2 || getType() == SceneType::Victory2;
}

// ===== 报名（自注册）=====
// 四个结果各报一次；注意 lambda 直接把收到的 type 转发给构造函数
// —— "我到底是哪一种结果"这个信息，在【报名这一层】就定型了，调用方只丢一个 SceneType 进来
static bool regResultScene = [] {
    SceneRegistry::reg(SceneType::GameOver1, [](SceneType t) { return std::make_unique<ResultScene>(t); });
    SceneRegistry::reg(SceneType::Victory1,  [](SceneType t) { return std::make_unique<ResultScene>(t); });
    SceneRegistry::reg(SceneType::GameOver2, [](SceneType t) { return std::make_unique<ResultScene>(t); });
    SceneRegistry::reg(SceneType::Victory2,  [](SceneType t) { return std::make_unique<ResultScene>(t); });
    return true;
}();
