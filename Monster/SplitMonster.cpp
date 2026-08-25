#include "SplitMonster.h"

SplitMonster::SplitMonster(float x, float y)
    : Monster(MonsterType::SPLIT, x, y) {
    hp = 80.f; maxHp = 80.f; baseSpeed = 70.f; speed = 70.f;
}
