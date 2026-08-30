#pragma once
#include <SDL3/SDL.h>
#include <string>

// 塔防专属 HUD（game 层）：金币框（框+数字一体，文字用 engine 层的 drawTextAt 画）
void drawGoldBox(SDL_Renderer* renderer, int x, int y, int w, int h, int gold);
