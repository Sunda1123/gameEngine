#pragma once
#include <SDL3/SDL.h>

// 通用血条控件（engine 层，可复用，换游戏照样用）
// hpPercent 是 0~1 的血量百分比，>60% 绿 / 30~60% 黄 / <30% 红
void drawHealthBar(SDL_Renderer* renderer, int x, int y, int w, int h, float hpPercent);
