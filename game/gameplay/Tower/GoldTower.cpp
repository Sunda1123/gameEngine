#include "GoldTower.h"
#include "../Player/Player.h"   // act 里要 player.addGold

GoldTower::GoldTower(float x, float y) : Tower(TowerType::Gold, x, y) {
    fireRate = 2.0f; cost = 50;
    cooldown = fireRate;   
}

void GoldTower::act(Player& player, float dt) {
    if (cooldown > 0.f) cooldown -= dt;
    if (cooldown <= 0.f) {
        player.addGold(10);      
        cooldown = fireRate;
    }
}
