#pragma once
#include <SDL3/SDL.h>
#include <string>


class Button {
private:
    SDL_FRect rect_;          // 按钮的位置+大小
    bool hovered_ = false;    // 鼠标是否悬停再按钮上
    bool clicked_ = false;    // 是否正在被按着
    std::string label_;       // 按钮上显示的字（空 = 不画字）
    int fontSize_ = 18;       // 字号

    // 三态配色（默认 = 橙系，跟以前写死的一模一样 → 老按钮外观零变化）
    SDL_Color normalColor_ = {255, 110, 70, 255};    // 普通
    SDL_Color hoverColor_  = {255, 140, 100, 255};   // 悬停（亮一点）
    SDL_Color pressColor_  = {200, 80, 60, 255};     // 按下（暗一点）
    SDL_Color textColor_   = {90, 40, 20, 255};      // 字色（默认深棕，衬橙底）
public:
    Button(const SDL_FRect& rect) : rect_(rect) {}//构造
    Button() = default;                       // 默认构造：先不设矩形
    void setRect(const SDL_FRect& r) { rect_ = r; }  // 事后设位置大小
    void SetLabel(const std::string& text, int size = 18) { label_ = text; fontSize_ = size; }  // 给按钮贴字

    // 换配色：一次给三个态（普通/悬停/按下）—— 按钮自己按状态挑色，外面不用管
    void SetColors(SDL_Color normal, SDL_Color hover, SDL_Color press) {
        normalColor_ = normal; hoverColor_ = hover; pressColor_ = press;
    }
    // 只换字色（底色换了、字看不清时用）
    void SetTextColor(SDL_Color c) { textColor_ = c; }

    // 处理事件，返回是否被点击
    bool HandleEvent(const SDL_Event& e);
    // 画按钮：自己按状态挑色（按下/悬停/普通）+ 居中画 label
    void Render(SDL_Renderer* r);
};