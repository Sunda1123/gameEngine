#include"Monster.h"
#include<cmath>


Monster::Monster(MonsterType type, float x, float y)
    : type(type),               //这冒号，没学明白
      pos{x, y},
      currentWaypoint(0),      // 出生点，从第 0 个路标出发
      slowTimer(0.f)       // 初始没减速
{
    initStats();
}





Monster::~Monster() = default;       //像我这种的笨比必备





bool Monster::hasReachedEnd(const std::vector<SDL_FPoint>& path) const//到没到
{
    if(currentWaypoint >= path.size()) return true;
    return false;
}

bool Monster::isMoving(const std::vector<SDL_FPoint>& path) const//到了就给我停，俩bool辅助update
{
    if(currentWaypoint >= path.size()) return false;
    return true;
}





void Monster::update(float dt,const std::vector<SDL_FPoint>& path) {     //运动模块
    
    
    if (slowTimer > 0)      //减速倒计时
    {
        slowTimer -= dt;
        if (slowTimer == 0) speed = baseSpeed;
    }

    if (currentWaypoint >= path.size()) {
        return;
    }

    SDL_FPoint target = path[currentWaypoint];    //标记目标

    float dx = target.x - pos.x;               //方向
    float dy = target.y - pos.y;
    float dist = sqrt(dx * dx + dy * dy);
    float step = speed * dt;

    if (dist <= step) {            // 这帧能到
        pos = target;
        currentWaypoint++;
    } else {                      // 朝目标走一步
        pos.x += dx / dist * step;
        pos.y += dy / dist * step;
    }

}


void Monster::initStats() {
    switch (type) {
        case MonsterType::ORDINARY:
            hp = 100.f; maxHp = 100.f; baseSpeed = 60.f; speed = 60.f;
            break;
        case MonsterType::TANK:
            hp = 300.f; maxHp = 300.f; baseSpeed = 40.f; speed = 40.f;
            break;
        case MonsterType::FAST:
            hp = 60.f; maxHp = 60.f; baseSpeed = 120.f; speed = 120.f;
            break;
        case MonsterType::SPLIT:
            hp = 80.f; maxHp = 80.f; baseSpeed = 70.f; speed = 70.f;
            break;
        case MonsterType::BOM:
            hp = 70.f; maxHp = 70.f; baseSpeed = 55.f; speed = 55.f;
            break;
         case MonsterType::POISON:
            hp = 90.f; maxHp = 90.f; baseSpeed = 65.f; speed = 65.f;
            break;
            
            
            
         /*         留一个复制用的
            case MonsterType::
        
            break;
            */
        }
}




//后边补一个怪的特殊能力，情况有点复杂，不太好改