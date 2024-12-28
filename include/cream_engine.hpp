#pragma once
#include "sol/sol.hpp"
#include "raylib.h"
#include "unordered_map"
#include <list>

struct Sprite
{
    std::shared_ptr<Texture2D> tex;
    int32_t x, y, w, h;
};

class CreamEngine
{
public:
    CreamEngine();
    void LoadScriptFile(const std::string &path);
    void Run();

private:
    sol::state lua;

    // Game variables
    bool background_texture_set;
    bool show_fps;
    Color background_color;
    std::shared_ptr<Texture2D> background_texture;
    std::list<Sprite> sprite_queue; // To be rendered
};
