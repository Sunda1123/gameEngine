#include<vector>

struct StatusEffect {
    float damagePerSecond;   // 每秒掉多少血
    float remainingTime;     // 还剩几秒（到了就移除）
    float slowFactor;        // 减速多少
};