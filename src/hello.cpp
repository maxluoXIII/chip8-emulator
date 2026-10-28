#include "raylib.h"

import std;
import Chip8;

constexpr int PIXEL_WIDTH = 10;
constexpr int PIXEL_HEIGHT = 10;
constexpr int SCREEN_WIDTH = Chip8::DISPLAY_WIDTH * PIXEL_WIDTH;
constexpr int SCREEN_HEIGHT = Chip8::DISPLAY_HEIGHT * PIXEL_HEIGHT;

void drawScreen(const std::array<std::bitset<Chip8::DISPLAY_HEIGHT>, Chip8::DISPLAY_WIDTH>& display) {
    for (int x = 0; x < Chip8::DISPLAY_WIDTH; ++x) {
        for (int y = 0; y < Chip8::DISPLAY_HEIGHT; ++y) {
            Color pixColor = display[x][y] ? BLACK : RAYWHITE;
            DrawRectangle(x*PIXEL_WIDTH, y*PIXEL_HEIGHT, PIXEL_WIDTH, PIXEL_HEIGHT, pixColor);
        }
    }
}

int main(int argc, char* argv[]) {
    std::cout << "Hello world!\n";
    std::cout << "Display size: " << Chip8::DISPLAY_WIDTH << "x" << Chip8::DISPLAY_HEIGHT << "\n";

    // Initialization
    //--------------------------------------------------------------------------------------
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "CHIP-8 Emulator");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    Chip8::Chip8 chip {};

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            std::string screen_size_str = std::format("Screen size: {}x{}", SCREEN_WIDTH, SCREEN_HEIGHT);

            // DrawText(screen_size_str.c_str(), 0, 0, 20, LIGHTGRAY);
            drawScreen(chip.getDisplay());

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
    return 0;
}
