#include<vector>
#include "Tower.h"
#include "Monster.h"
#include "MAp.h"



class Player{
private:
    int initialGold;   //初始金币，后边定价再定这个
    int gold;       //现有金币
    int MaxbaseHealth;      //基地血量，也是玩家血量，到时候得画个血条
    int baseHealth;
public:   
    std::vector<Tower*> towers;
    std::vector<Monster*> monster;

    bool placeTower(int x, int y);        // 花钱放塔
    bool spawnMonster(float x , float y );             // 花钱放怪
};



//用来创建一个按钮的类
class Button {
public:
    Button(const SDL_FRect& rect) : rect_(rect) {}

    // 处理事件，返回是否被点击
    bool HandleEvent(const SDL_Event& e) {
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

    // 画按钮：按下=深红 / 悬停=浅橙 / 普通=橙
    void Render(SDL_Renderer* r) {
        if (clicked_) {
            SDL_SetRenderDrawColor(r, 200, 80, 60, 255);
        } else if (hovered_) {
            SDL_SetRenderDrawColor(r, 255, 140, 100, 255);
        } else {
            SDL_SetRenderDrawColor(r, 255, 110, 70, 255);
        }
        SDL_RenderFillRect(r, &rect_);
    }

private:
    SDL_FRect rect_;          // 按钮的位置+大小
    bool hovered_ = false;    // 鼠标是否悬停再按钮上
    bool clicked_ = false;    // 是否正在被按着
};