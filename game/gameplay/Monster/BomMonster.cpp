#include "BomMonster.h"

BomMonster::BomMonster(float x, float y)
    : Monster(MonsterType::BOM, x, y) {
    hp = 70.f; maxHp = 70.f; baseSpeed = 55.f; speed = 55.f;
}
