#include "Map.h"
#include "json.hpp"
#include <fstream>

using json = nlohmann::json;




//读取json地图文件
bool Map::loadFromJson(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "无法打开地图文件: " << filepath << std::endl;
        return false;
    }


    //读filepath.json
    json j;
    file >> j;


// 防御：检查必要字段
    if (!j.contains("width") || !j.contains("height") || !j.contains("tileSize") ||
        !j.contains("tiles") || !j.contains("path")) {
        return false;
    }
    width = j["width"];
    height = j["height"];
    tileSize = j["tileSize"];
    // 防御：尺寸合法
    if (width <= 0 || height <= 0) return false;
    pathPoints.clear();          // ← 清旧数据
    tiles.resize(width * height); // ← 重新分配


    // 填格子
    const auto& tileRows = j["tiles"];
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int val = tileRows[y][x];
            at(x, y).type = static_cast<TileType>(val);
        }
    }


    // 填路径
    const auto& path = j["path"];
    for (const auto& point : path) {
        int px = point[0];
        int py = point[1];
        pathPoints.push_back({
            px * tileSize + tileSize / 2.0f,
            py * tileSize + tileSize / 2.0f
        });
    }
    return true;
}




bool Map::isBuildable(int x, int y) const                //⚠️后边补上塔用上的地方不能再用了
{
    if (x < 0 || y < 0 || x >= width || y >= height) return false;

    TileType type = at(x, y).type;

    return type == TileType::BUILDABLE;
}




void Map::render(SDL_Renderer* renderer) const
{
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int r, g, b;
            switch (at(x, y).type) {
                case TileType::EMPTY:
                    r = 30; g = 30; b = 30;
                    break;
                case TileType::PATH:
                    r = 100; g = 100; b = 100;
                    break;
                case TileType::BUILDABLE:
                    r = 50; g = 150; b = 50;
                    break;
                case TileType::SPAWN:
                    r = 255; g = 0; b = 50;
                    break;
                case TileType::BASE:
                    r =  0; g = 255; b = 50;
                    break;
                default:
                    r = 30; g = 30; b = 30;
                    break;
            }
            
            SDL_SetRenderDrawColor(renderer, r, g, b, 255);
            
            SDL_FRect rect = {(float)(x * tileSize), (float)(y * tileSize), (float)tileSize, (float)tileSize};
            SDL_RenderFillRect(renderer, &rect);
        }
    }
}