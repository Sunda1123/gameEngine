# 🏰 gameEngine — 我的游戏引擎学习项目（2D 塔防，目标 2v2 联机）

> 一个**正在学习游戏引擎开发**的 CS 学生，用 C++ 手写的小小塔防引擎。（怎么架构这么难，我找不到变量了）

## 🎮 项目是啥

用 **C++17 + SDL3** 写的 2D 塔防游戏引擎，规划为 **2v2 局域网联机**：每人既要**放塔守家**，也要**跳到对面地盘放怪进攻**。

## ✨ 已完成的（09-07 更新）

- 🗺️ **地图 Map**：JSON 读图（格子类型 + 路径）、占格/释放、渲染上色
- 🏗️ **塔 Tower**：多态 6 塔（箭/炮/法/冰/焦油/金币，各一个文件）+ **TowerFactory 自注册工厂**（加新塔只需新建文件自动报名）
- 🔫 **子弹系统**：塔索敌 → 发射子弹 → 直线飞 → 命中扣血（`engine/math` Math2D：length/normalize/dist）
- 👾 **怪 Monster**：沿路径平滑移动、6 种类型、状态效果（减速/持续伤害接口已留）
- 💰 **经济闭环**：放塔/放怪扣钱、经济塔产钱、**杀怪给钱**（每只怪自带 rewardGold）、金币 HUD
- 🩸 **基地血条**：血归 Player 管（封装），绿/黄/红变色
- 🎮 **放塔交互**：点"选择放塔"展开塔菜单 → 选塔 → 点地图放塔（点按钮不会误触放置）
- 📜 **Command 撤销体系骨架**（Command 基类 + PlaceTowerCommand，待接通）
- 🎨 **分层架构**：`engine/`（通用层：UI + math）+ `game/gameplay/`（Map/Monster/Player/Tower/Bullet/Command）+ SDL3 渲染

## 🕹️ 怎么玩

右侧点「选择放塔」→ 展开塔菜单 → 点一座塔 → 点地图放下；点「放怪」在出生点出怪；塔自动开火射子弹，打死怪爆金币 💰

## 🛠️ 技术栈

- **C++17** · **SDL3** · **nlohmann/json**

## 🚀 编译运行

```bash
# 在 project_root/ 下
build.bat        # 一键编译，生成 game.exe
game.exe         # 运行
```

## 📁 目录结构（简化）

```
gameEngine/
├── engine/
│   ├── UI/           # 通用引擎层：Button / TextRenderer(画字) / HealthBar(血条)
│   └── math/         # Math2D：向量 length / normalize / dist（头文件库）
├── game/
│   ├── UI/           # gameUI 主循环 + HUD（金币框）
│   ├── gameplay/     # Map / Monster / Player / Tower / Bullet / Command
│   └── data/         # 地图数据 filepath.json
└── project_root/     # build.bat + game.exe
```

## 🗺️ 路线图

- [x] 地图模块（JSON 读图 + 路径 + 占格）
- [x] 塔模块（多态 6 塔 + TowerFactory 报名制）
- [x] 子弹系统 + 杀怪给钱（经济闭环）
- [x] 基地血条 + UI 分层 + 放塔菜单交互
- [ ] Command 撤销接通（放错塔能撤回）
- [ ] 塔升级接进玩法（upgrade 已有，UI 待接）
- [ ] 特殊塔效果接子弹（冰减速 / 焦油持续伤害）
- [ ] 多出怪点 / 基地血量归零出局
- [ ] 本地 4 玩家 + 画面跳转
- [ ] 局域网联机（socket）


