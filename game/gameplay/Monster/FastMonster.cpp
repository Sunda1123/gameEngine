#include "FastMonster.h"

FastMonster::FastMonster(float x, float y)
    : Monster(MonsterType::FAST, x, y) {
    hp = 60.f; maxHp = 60.f; baseSpeed = 120.f; speed = 120.f;
}
