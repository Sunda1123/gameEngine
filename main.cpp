#include "UI/gameUI.h"

int main(int argc, char* argv[]) {
    GameUI game;   // 构造：自动开机（SDL/窗口/渲染器/地图/怪）
    game.run();    // 主循环（跑到关窗口为止）
    return 0;      // 析构：自动关机（清理资源）
}

