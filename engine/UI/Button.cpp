
#include "Button.h"
#include "TextRenderer.h"

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



// TODO: 放置模式下把"可放塔"的格子圈出来高亮（不然路上/已占格都分不清能不能放）


    // 画按钮：自己按状态挑色（按下 / 悬停 / 普通）
void Button::Render(SDL_Renderer* r) {
    SDL_Color bg = clicked_ ? pressColor_ : (hovered_ ? hoverColor_ : normalColor_);
    SDL_SetRenderDrawColor(r, bg.r, bg.g, bg.b, bg.a);
    SDL_RenderFillRect(r, &rect_);

    // 有字才画：近似居中
    // 注意：std::string::size() 数的是【字节】，中文 UTF-8 一个字 = 3 字节，
    //       所以宽度要按"字数"算（÷3），不然估大 3 倍字就歪左边了
    if (!label_.empty()) {
        int chars = (int)label_.size() / 3;   // 咱按钮都是中文，每字 3 字节
        int textW = chars * fontSize_;        // 中文字宽 ≈ 字号
        int tx = (int)rect_.x + ((int)rect_.w - textW) / 2;
        int ty = (int)rect_.y + ((int)rect_.h - fontSize_) / 2;
        drawTextAt(r, label_, tx, ty, fontSize_, textColor_.r, textColor_.g, textColor_.b);
    }
}

