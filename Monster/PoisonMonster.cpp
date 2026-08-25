#include "PoisonMonster.h"

PoisonMonster::PoisonMonster(float x, float y)
    : Monster(MonsterType::POISON, x, y) {
    hp = 90.f; maxHp = 90.f; baseSpeed = 65.f; speed = 65.f;
}
