#pragma once
#include <SDL3/SDL.h>
#include <vector>
#include <string>
#include <cstdint>

enum class TileType : uint8_t {
    EMPTY = 0,
    BUILDABLE = 1,
    PATH = 2,
    SPAWN = 3,
    BASE = 4
};

//遍历格子类型
struct Tile {
    TileType type = TileType::EMPTY;
    bool occupied = false;
};

class Map {
public:
    Map() = default;
    bool loadFromJson(const std::string& filepath);           //Map.h中完成功能🐲
    const std::vector<SDL_FPoint>& getPath() const { return pathPoints; }
    void render(SDL_Renderer* renderer) const;                //Map.h中完成功能🐲
    bool isBuildable(int x, int y) const;                     //能建 = 空地且没被占（实现在 Map.cpp）
    bool occupy(int x, int y);                                //占一个格子（放塔后调用，防叠塔）
    bool isOccupied(int x, int y) const;                      //这格被占了没（撤销要查）
    bool release(int x, int y);                               //释放一个格子（撤销放塔用，occupy 的反向）

    int getWidth() const { return width; }          //Map.cpp中width调用🚑
    int getHeight() const { return height; }        //Map.cpp中height调用🚑
    int getTileSize() const { return tileSize; }    //Map.cpp中tileSize调用🚑

private:
    int width = 0, height = 0, tileSize = 48;
    std::vector<Tile> tiles;              //Map.h中实现填入😋
    std::vector<SDL_FPoint> pathPoints;                //Map.h中实现填入😋

    Tile& at(int x, int y) { return tiles[y * width + x]; }
    const Tile& at(int x, int y) const { return tiles[y * width + x]; }
};