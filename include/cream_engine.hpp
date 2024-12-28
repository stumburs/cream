#pragma once
#include "sol/sol.hpp"
#include "raylib.h"
#include "unordered_map"

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
    Color background_color;
    Texture2D background_texture;
    std::unordered_map<std::string, Texture2D> texture_map;
};