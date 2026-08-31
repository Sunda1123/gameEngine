#pragma once
// 所有塔的"总入口"：include 这一个，就认识全部塔（省得写 6 行 include）
// 注意：这不是 Tower.h（基类）！这个是"伞状头"，专门聚合所有塔
// 以后加新塔：只要往这里加一行，其他用塔的地方不用动
#include "Tower.h"
#include "ArrowTower.h"
#include "CannonTower.h"
#include "MagicTower.h"
#include "IceTower.h"
#include "TarTower.h"
#include "GoldTower.h"
