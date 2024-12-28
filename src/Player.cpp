#include "Player.hpp"

void Player::Update()
{
    if (IsKeyDown(KEY_D))
    {
        this->x += 200 * GetFrameTime();
    }
    if (IsKeyDown(KEY_A))
    {
        this->x -= 200 * GetFrameTime();
    }
}
