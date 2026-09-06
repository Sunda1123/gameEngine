#pragma once
#include <SDL3/SDL.h>
#include <cmath>

// 项目里位置都用 SDL_FPoint{x,y} 表示，给它的三个工具函数：

// 向量长度（勾股定理）
inline float length(SDL_FPoint v) {
    return std::sqrt(v.x * v.x + v.y * v.y);
}

// 归一化 → 方向（长度变 1）；怪移动、子弹飞行都用它
inline SDL_FPoint normalize(SDL_FPoint v) {
    float len = length(v);
    if (len < 0.0001f) return {0, 0};   // 防除零
    return {v.x / len, v.y / len};
}

// 两点距离
inline float dist(SDL_FPoint a, SDL_FPoint b) {
    return length({b.x - a.x, b.y - a.y});
}



// 这里留个通用二次曲线工具（万一以后画曲线 UI 用）
inline float coniSection(float x, float a, float b, float c) {
    return a * x * x + b * x + c; 
}


// 角度转弧度
inline float deg2rad(float deg) {
    return deg * (3.14159265358979323846f / 180.f);
}


// 弧度转角度
inline float rad2deg(float rad) {
    return rad * (180.f / 3.14159265358979323846f);
}


// ⚠️ 炮弹"飞行轨迹"别写在 Math2D —— 炮弹是"有状态的对象"（每帧要记住自己的位置/速度），
//    得做成 Bullet 类，每帧在它自己的 update() 里推进：
//      pos.x += vx*dt;  pos.y += vy*dt;  vy += g*dt;   // ← 这是子弹类的活，不是纯函数
//    Math2D 只放"无状态纯函数"（length/normalize/dist），供子弹/怪/塔每帧调用
// （普通子弹的直线飞行不用额外函数：每帧 pos += normalize(目标-自己) * speed * dt，上面 normalize 就够了）