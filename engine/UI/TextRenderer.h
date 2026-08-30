#pragma once
#include <SDL3/SDL.h>
#include <string>

// 通用画字模块（engine 层，可复用，换游戏照样用）
// SDL3 不带字体，借系统"微软雅黑"（GDI）渲染文字到纹理再画到渲染器
// text 内容，x/y 左上角，fontSize 字号，r/g/b 颜色，maxWidth 折行宽度（0=不折行）
void drawTextAt(SDL_Renderer* renderer, const std::string& text, int x, int y, int fontSize,
                Uint8 r, Uint8 g, Uint8 b, int maxWidth = 0);
