#include "TankMonster.h"

TankMonster::TankMonster(float x, float y)
    : Monster(MonsterType::TANK, x, y) {
    hp = 300.f; maxHp = 300.f; baseSpeed = 40.f; speed = 40.f;
}
