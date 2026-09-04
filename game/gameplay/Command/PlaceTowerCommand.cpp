#include "PlaceTowerCommand.h"
#include "../Player/Player.h"
#include "../Map/Map.h"

// 构造函数
PlaceTowerCommand::PlaceTowerCommand(Player* p, Map* m, float x, float y)
    : player(p), map(m), x(x), y(y) {}   // col/row/costPaid/towerIndex 走 .h 里的默认值

// 执行：放塔
void PlaceTowerCommand::execute() {
    // 1. 像素坐标 → 格子坐标
    int tileSize = map->getTileSize();
    col = (int)(x / tileSize);
    row = (int)(y / tileSize);

    // 2. 检查格子是否被占用
    if (map->isOccupied(col, row)) {
        return;  // 格子被占，不放塔
    }

    // 3. 让 player 放塔（它自己判断钱够不够 + 扣钱 + 造塔 + 进列表，B 方案）
    //    返回扣了多少钱；0 = 没放成（钱不够/名册没有）
    int cost = player->placeTower(x, y);
    if (cost <= 0) return;

    // 4. 记现场（undo 要还的账）：扣了多少钱 + 塔在列表第几个
    costPaid = cost;
    towerIndex = player->getTowerCount() - 1;

    // 5. 占用地图格子
    map->occupy(col, row);
}

// 撤销：退钱、删塔、释放格子
void PlaceTowerCommand::undo() {
    // 1. 退钱
    player->addGold(costPaid);

    // 2. 删塔（按索引）
    if (towerIndex >= 0 && towerIndex < player->getTowerCount()) {
        player->removeTower(towerIndex);
    }

    // 3. 释放格子
    map->release(col, row);
}