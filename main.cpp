#include "game/TowerDefenseApp.h"

// 装配车间：这里认识所有人（引擎 + 游戏场景），负责把它们拼起来
// 引擎和游戏互不认识，只有 main 认识两边
int main(int argc, char* argv[]) {
    TowerDefenseApp app;   // 塔防的"应用程序"：继承引擎壳，回答"第一个场景是谁"
    app.run();             // 主循环（跑到关窗口为止）
    return 0;              // 析构：自动关机（清理资源）
}
