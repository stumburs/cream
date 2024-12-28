#include "cream_engine.hpp"

CreamEngine::CreamEngine()
{
    InitWindow(1920, 1080, "cream");

    this->lua.open_libraries(sol::lib::base);

    this->background_texture_set = false;
    this->show_fps = false;
    this->background_color = BLACK;

    // Prints text to console
    this->lua.set_function("Print", [&](const std::string &text)
                           { std::cout << text << std::endl; });

    // Experimental
    // Save texture as variable in Lua
    this->lua.new_usertype<Texture2D>("Texture2D", "width", &Texture2D::width, "height", &Texture2D::height, "mipmaps", &Texture2D::mipmaps, "format", &Texture2D::format);

    // Player variable
    this->lua.new_usertype<Player>("Player", "x", &Player::x, "y", &Player::y, "texture", &Player::texture);

    // Create a player
    this->lua.set_function("CreatePlayer", [&](const std::shared_ptr<Texture2D> texture, float_t x, float_t y) -> std::shared_ptr<Player>
                           {
        auto player = std::make_shared<Player>();
        player->texture = texture;
        player->x = x;
        player->y = y;
        this->player = player;
        return player; });

    // Load texture as Lua variable
    this->lua.set_function("LoadTexture", [&](const std::string &texture_path) -> std::shared_ptr<Texture2D>
                           { auto texture = std::make_shared<Texture2D>(LoadTexture(texture_path.c_str())); return texture; });

    // Sets the background color
    this->lua.set_function("SetBackgroundColor", [&](const uint8_t r, const uint8_t g, const uint8_t b)
                           {
        this->background_color.r = r;
        this->background_color.g = g;
        this->background_color.b = b; });

    // Sets the background texture
    this->lua.set_function("SetBackground", [&](std::shared_ptr<Texture2D> texture)
                           {
        this->background_texture = texture;
        this->background_texture_set = true; });

    // Renders a sprite at position X, Y, and size W, H
    this->lua.set_function("DrawSprite", [&](std::shared_ptr<Texture2D> texture, int32_t X, int32_t Y, int32_t W, int32_t H)
                           { this->sprite_queue.emplace_back(Sprite{texture, X, Y, W, H}); });

    // Displays FPS at the top left
    this->lua.set_function("ShowFPS", [&](void)
                           { this->show_fps = true; });

    // Hides FPS at the top left
    this->lua.set_function("HideFPS", [&](void)
                           { this->show_fps = false; });
}

void CreamEngine::LoadScriptFile(const std::string &path)
{
    this->lua.script_file(path);
}

void CreamEngine::Run()
{
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        // Update
        if (this->player != nullptr)
        {
            player->Update();
            std::cout << player->x << '\n';
        }

        // Render
        BeginDrawing();
        {
            ClearBackground(background_color);
            if (this->background_texture_set)
            {
                DrawTexturePro(*this->background_texture, {0.0f, 0.0f, (float)this->background_texture->width, (float)this->background_texture->height}, {0.0f, 0.0f, (float)GetScreenWidth(), (float)GetScreenHeight()}, {0.0f, 0.0f}, 0.0f, WHITE);
            }

            for (const auto &sprite : this->sprite_queue)
            {
                DrawTexturePro(*sprite.tex, {0.0f, 0.0f, (float)sprite.tex->width, (float)sprite.tex->height}, {(float)sprite.x, (float)sprite.y, (float)sprite.w, (float)sprite.h}, {0.0f, 0.0f}, 0.0f, WHITE);
            }

            if (this->player != nullptr)
            {
                DrawTexturePro(*player->texture, {0.0f, 0.0f, (float)player->texture->width, (float)player->texture->height}, {(float)player->x, (float)player->y, (float)player->texture->width, (float)player->texture->height}, {0.0f, 0.0f}, 0.0f, WHITE);
            }

            if (this->show_fps)
            {
                DrawFPS(20, 20);
            }
        }
        EndDrawing();
    }
    CloseWindow();
}
