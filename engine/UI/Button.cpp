
#include "Button.h"

bool Button::HandleEvent(const SDL_Event& e) {
        // 鼠标是否"按下"且是左键
        if (e.type == SDL_EVENT_MOUSE_BUTTON_DOWN &&
            e.button.button == SDL_BUTTON_LEFT) {
            // 拿鼠标按下的像素坐标
            SDL_FPoint pt = { e.button.x, e.button.y };
            //判断这个点落是不是在按钮矩形 rect_ 里
            if (SDL_PointInRectFloat(&pt, &rect_)) {
                clicked_ = true;
                return true;  // 告诉外层：我被点了
            }
        }
        // 鼠标松开 → 取消按下状态
        if (e.type == SDL_EVENT_MOUSE_BUTTON_UP) {
            clicked_ = false;
        }
        // 鼠标移动→ 更新悬停（悬停 = 提示用户"能点"）
        if (e.type == SDL_EVENT_MOUSE_MOTION) {
            SDL_FPoint pt = { e.motion.x, e.motion.y };
            hovered_ = SDL_PointInRectFloat(&pt, &rect_);
        }
        return false;
}



//🐲🐲🐲🐲🐲🐲🐲🐲放塔的位置后边得圈一下，不圈不行了，路上都能放塔了⚡⚡⚡⚡⚡⚡⚡


    // 画按钮：按下=深红 / 悬停=浅橙 / 普通=橙
void Button::Render(SDL_Renderer* r) {
    if (clicked_) {
        SDL_SetRenderDrawColor(r, 200, 80, 60, 255);
    } else if (hovered_) {
        SDL_SetRenderDrawColor(r, 255, 140, 100, 255);
    } else {
        SDL_SetRenderDrawColor(r, 255, 110, 70, 255);
    }
    SDL_RenderFillRect(r, &rect_);
}

