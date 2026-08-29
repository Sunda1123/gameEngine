#include "OrdinaryMonster.h"

OrdinaryMonster::OrdinaryMonster(float x, float y)
    : Monster(MonsterType::ORDINARY, x, y) {
    hp = 100.f; maxHp = 100.f; baseSpeed = 60.f; speed = 60.f;
}
