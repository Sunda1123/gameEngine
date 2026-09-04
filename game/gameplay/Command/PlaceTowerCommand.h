#pragma once
#include "Command.h"

class Player;
class Map;

// "放一座塔"命令：execute = 放塔+扣钱+占格；undo = 退钱+删塔+清格
// 撤销要能"还账"，所以 execute 时必须把现场存下来（执行时存、撤销时还得上）：
//   costPaid    = 这次扣了多少钱（每座塔价格不同，执行时才知道）
//   towerIndex  = 放进去后它在 towers 列表第几个（undo 好删对那座）
class PlaceTowerCommand : public Command {
    Player* player;    // 钱和塔列表都归它管
    Map*    map;       // 格子归它管（放塔占格、撤销清格）
    float   x, y;      // 放哪（格子中心像素）
    int     col = -1, row = -1;   // 放哪格（execute 里算出来，undo 清格要用）
    int     costPaid = 0;    // ★ 执行时扣的钱（撤销原样退）
    int     towerIndex = -1; // ★ 执行后塔在列表的位置（撤销删它）
public:
    PlaceTowerCommand(Player* p, Map* m, float x, float y);
    void execute() override;
    void undo() override;
};
