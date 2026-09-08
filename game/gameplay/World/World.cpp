#include "World.h"

bool World::loadMap(const std::string& filepath) {
    return map.loadFromJson(filepath);
}

// 每帧玩法调度：原 GameUI::update 整段搬进来
// （GameUI 现在只管窗口/界面，玩法逻辑全归世界）
void World::update(float dt) {
    // 怪沿路走
    for (auto m : player.monsters) {
        m->update(dt, map.getPath());
    }

    // 塔自己干活：攻击塔打怪、经济塔产钱（行为收进 Tower::act，多态统一）
    for (auto& t : player.towers) {
        t->act(player, dt);
    }

    // 子弹飞 + 自己撞怪（撞到/寿命尽会标记死）
    for (auto& b : player.bullets){
        b->update(dt, player.monsters);
    }

    // 清理死掉的怪（倒着删，防迭代器失效）+ 杀怪给钱
    for (int i = (int)player.monsters.size() - 1; i >= 0; i--) {
        if (player.monsters[i]->getHp() <= 0) {
            player.addGold(player.monsters[i]->getRewardGold());   // 怪爆金币
            delete player.monsters[i];
            player.monsters.erase(player.monsters.begin() + i);
        }
    }

    // 清理死掉的子弹
    for (int i = (int)player.bullets.size() - 1; i >= 0; --i) {
        if (player.bullets[i]->isDead())
            player.bullets.erase(player.bullets.begin() + i);
    }

    // 到终点扣基地血（⚠️ 现在每帧扣，待改"扣一次就移除"）
    for (auto m : player.monsters) {
        if (m->hasReachedEnd(map.getPath())) {
            player.takeBaseDamage(1);
        }
    }
}
