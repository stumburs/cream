#pragma once
#include "raylib.h"
#include <memory>

struct Player
{
public:
    float x, y;
    std::shared_ptr<Texture2D> texture;
};