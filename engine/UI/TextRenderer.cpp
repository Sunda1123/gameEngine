#include "TextRenderer.h"

#define WIN32_LEAN_AND_MEAN   // 少引 windows 杂七杂八，避免和 std::byte 打架
#include <windows.h>

using namespace std;

// renderText：把文本渲染成 SDL 纹理（背景透明）
// 内部工具（static，只在本文件用），对外只暴露 drawTextAt
static SDL_Texture* renderText(SDL_Renderer* renderer, const string& text, int fontSize,
                               Uint8 r, Uint8 g, Uint8 b, int maxWidth = 0)
{
    // 1. UTF-8 → UTF-16（GDI 用宽字符）
    int wlen = MultiByteToWideChar(CP_UTF8, 0, text.c_str(), -1, NULL, 0);
    if (wlen <= 0) return nullptr;
    wstring wtext(wlen, L'\0');
    MultiByteToWideChar(CP_UTF8, 0, text.c_str(), -1, &wtext[0], wlen);

    // 2. 造临时画布 + 字体（微软雅黑，系统自带）
    HDC hdc = CreateCompatibleDC(NULL);
    HFONT font = CreateFontW(fontSize, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
        DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY,
        DEFAULT_PITCH, L"微软雅黑");
    HGDIOBJ oldFont = SelectObject(hdc, font);

    // 3. 量文字尺寸（超过 maxWidth 自动折行）
    RECT rc = { 0, 0, maxWidth, 0 };
    DWORD fmt = DT_CALCRECT;
    if (maxWidth > 0) fmt |= DT_WORDBREAK;
    DrawTextW(hdc, wtext.c_str(), -1, &rc, fmt);
    int w = rc.right - rc.left;
    int h = rc.bottom - rc.top;
    if (w <= 0 || h <= 0) { w = 1; h = fontSize; }   // 空文本兜底

    // 4. 造 32 位内存位图（BGRA，像素可读）
    BITMAPINFO bmi = {};
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = w;
    bmi.bmiHeader.biHeight = -h;      // 负 = 自顶向下
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 32;
    bmi.bmiHeader.biCompression = BI_RGB;
    void* pixels = nullptr;
    HBITMAP bmp = CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, &pixels, NULL, 0);
    HGDIOBJ oldBmp = SelectObject(hdc, bmp);

    // 5. 写字
    SetBkMode(hdc, TRANSPARENT);
    SetTextColor(hdc, RGB(r, g, b));
    RECT rc2 = { 0, 0, w, h };
    DWORD fmt2 = DT_LEFT | DT_TOP | DT_NOCLIP;
    if (maxWidth > 0) fmt2 |= DT_WORDBREAK;
    DrawTextW(hdc, wtext.c_str(), -1, &rc2, fmt2);

    // 6. 黑色背景当透明：文字像素 alpha=255，背景 alpha=0
    int pitch = w * 4;
    for (int y = 0; y < h; y++) {
        Uint8* row = (Uint8*)pixels + y * pitch;
        for (int x = 0; x < w; x++) {
            Uint8* px = row + x * 4;   // BGRA
            if (px[0] > 16 || px[1] > 16 || px[2] > 16) px[3] = 255;
            else px[3] = 0;
        }
    }

    // 7. 转 SDL surface → 纹理
    SDL_Surface* surf = SDL_CreateSurfaceFrom(w, h, SDL_PIXELFORMAT_BGRA32, pixels, pitch);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surf);
    SDL_SetTextureBlendMode(tex, SDL_BLENDMODE_BLEND);
    SDL_DestroySurface(surf);

    // 8. 清理 GDI 资源
    SelectObject(hdc, oldFont);
    SelectObject(hdc, oldBmp);
    DeleteObject(bmp);
    DeleteObject(font);
    DeleteDC(hdc);
    return tex;
}

// 在窗口某处画一段文字（engine 层通用，公开给 game 用）
// 注意：默认参数 maxWidth=0 已在 TextRenderer.h 声明里给了，这里不能再给（重复=报错）
void drawTextAt(SDL_Renderer* renderer, const string& text, int x, int y, int fontSize,
                Uint8 r, Uint8 g, Uint8 b, int maxWidth)
{
    SDL_Texture* tex = renderText(renderer, text, fontSize, r, g, b, maxWidth);
    if (!tex) return;
    float tw, th;
    SDL_GetTextureSize(tex, &tw, &th);
    SDL_FRect dst = { (float)x, (float)y, tw, th };
    SDL_RenderTexture(renderer, tex, NULL, &dst);
    SDL_DestroyTexture(tex);
}
