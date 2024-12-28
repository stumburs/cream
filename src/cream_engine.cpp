#include "cream_engine.hpp"

CreamEngine::CreamEngine()
{
    InitWindow(1920, 1080, "cream");

    this->lua.open_libraries(sol::lib::base);

    this->background_texture_set = false;
    this->background_color = BLACK;

    // Prints text to console
    this->lua.set_function("print", [&](const std::string &text)
                           { std::cout << text << std::endl; });

    // Sets the background color
    this->lua.set_function("setBackgroundColor", [&](const uint8_t r, const uint8_t g, const uint8_t b)
                           { this->background_color.r = r; this->background_color.g = g; this->background_color.b = b; });

    // Loads a texture into a map
    this->lua.set_function("loadTexture", [&](const std::string &texture_name, const std::string &texture_path)
                           { UnloadTexture(this->texture_map[texture_name]); this->texture_map[texture_name] = LoadTexture(texture_path.c_str()); });

    // Sets the background texture
    this->lua.set_function("setBackground", [&](const std::string &texture_name)
                           { this->background_texture = this->texture_map.at(texture_name); this->background_texture_set = true; });
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

        // Render
        BeginDrawing();
        {
            ClearBackground(background_color);
            if (this->background_texture_set)
            {
                DrawTexturePro(this->background_texture, {0.0f, 0.0f, (float)this->background_texture.width, -(float)this->background_texture.height}, {0.0f, 0.0f, (float)GetScreenWidth(), (float)GetScreenHeight()}, {0.0f, 0.0f}, 0.0f, WHITE);
            }
            DrawFPS(20, 20);
        }
        EndDrawing();
    }
    CloseWindow();
}
