#pragma once
#include <SDL3/SDL.h>


class Button {
private:
    SDL_FRect rect_;          // 按钮的位置+大小
    bool hovered_ = false;    // 鼠标是否悬停再按钮上
    bool clicked_ = false;    // 是否正在被按着
public:
    Button(const SDL_FRect& rect) : rect_(rect) {}//构造
    Button() = default;                       // 默认构造：先不设矩形
    void setRect(const SDL_FRect& r) { rect_ = r; }  // 事后设位置大小
    // 处理事件，返回是否被点击
    bool HandleEvent(const SDL_Event& e);
    // 画按钮：按下=深红 / 悬停=浅橙 / 普通=橙
    void Render(SDL_Renderer* r);
};