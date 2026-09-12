#pragma once
#include "../../engine/Scene.h"
#include "../../engine/UI/Button.h"
#include "../../engine/UI/TextRenderer.h"
#include <SDL3/SDL.h>

// 结算场景：一屏结果 + 两个按钮（再来一局 / 回主菜单）
class ResultScene : public Scene {
    Button retryBtn;   // 再来一局
    Button homeBtn;    // 回主菜单

    bool isVictory() const;   // 赢了吗（问基类存的 type_）
    bool isLAN() const;       // 是联机局吗（决定"再来一局"回哪）

public:
    explicit ResultScene(SceneType type);   // 传 GameOver 或 Victory

    void enter() override;
    void exit() override;
    void processEvents(const SDL_Event& e) override;
    void update(float dt) override;
    void render(SDL_Renderer* renderer) override;
};
