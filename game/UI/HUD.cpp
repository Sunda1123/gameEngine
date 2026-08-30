#include "HUD.h"
#include "../../engine/UI/TextRenderer.h"   // 画字用 engine 层的通用件 drawTextAt

// 金币框 + 金币数字（框+文字一体：暗金底 + 金边 + 框内"金币: N"）
void drawGoldBox(SDL_Renderer* renderer, int x, int y, int w, int h, int gold) {
    // 1. 底（暗金）
    SDL_FRect boxRect = { (float)x, (float)y, (float)w, (float)h };
    SDL_SetRenderDrawColor(renderer, 50, 40, 0, 255);
    SDL_RenderFillRect(renderer, &boxRect);

    // 2. 金边（255,215,0 = 纯正金色）
    SDL_SetRenderDrawColor(renderer, 255, 215, 0, 255);
    SDL_RenderRect(renderer, &boxRect);

    // 3. 框内画数字：从框左上角偏移 (x+8, y+4)，字号 20，金色
    drawTextAt(renderer, std::string("金币: ") + std::to_string(gold), x + 8, y + 4, 20, 255, 215, 0);
}
