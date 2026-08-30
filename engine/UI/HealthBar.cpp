#include "HealthBar.h"

// 画血条：深灰底 + 按血量变色的前景条 + 白框
void drawHealthBar(SDL_Renderer* renderer, int x, int y, int w, int h, float hpPercent) {
    // 限制一下百分比
    if (hpPercent < 0.0f) hpPercent = 0.0f;
    if (hpPercent > 1.0f) hpPercent = 1.0f;

    // 1. 背景条（深色底）
    SDL_FRect bgRect = { (float)x, (float)y, (float)w, (float)h };
    SDL_SetRenderDrawColor(renderer, 60, 60, 60, 255);   // 深灰
    SDL_RenderFillRect(renderer, &bgRect);

    // 2. 前景条（根据血量变色 + 宽度随百分比缩放）
    int fillW = (int)(w * hpPercent);
    SDL_FRect fillRect = { (float)x, (float)y, (float)fillW, (float)h };

    if (hpPercent > 0.6f)
        SDL_SetRenderDrawColor(renderer, 0, 200, 0, 255);    // 绿
    else if (hpPercent > 0.3f)
        SDL_SetRenderDrawColor(renderer, 200, 200, 0, 255);  // 黄
    else
        SDL_SetRenderDrawColor(renderer, 200, 0, 0, 255);    // 红

    SDL_RenderFillRect(renderer, &fillRect);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);    // 白色
    SDL_RenderRect(renderer, &bgRect);   // SDL3 画边框
}
