#pragma once
#include "raylib.h"
#include <memory>

struct Player
{
public:
    void Update();
    float x, y;
    std::shared_ptr<Texture2D> texture;
};