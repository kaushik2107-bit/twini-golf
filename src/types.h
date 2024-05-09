#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <glad/glad.h>


extern int WIN_WIDTH;
extern int WIN_HEIGHT;

extern SDL_Window* window;
extern SDL_GLContext context;
extern GLuint bgId;
extern GLuint ballId;
extern GLuint pointerId;
extern GLuint holeId;

extern GLuint powermeterFId;
extern GLuint powermeterBId;
extern GLuint powermeterOId;

extern GLuint splashScreenId;
extern GLuint logoId;

extern TTF_Font* font;

struct Timer {
    Uint64 previous_ticks{};
    float elapsed_seconds{};

    void tick() {
        const Uint64 current_ticks{ SDL_GetPerformanceCounter() };
        const Uint64 delta{ current_ticks - previous_ticks };
        previous_ticks = current_ticks;
        static const Uint64 TICKS_PER_SECOND{ SDL_GetPerformanceFrequency() };
        elapsed_seconds = delta / static_cast<float>(TICKS_PER_SECOND);
    }
};

struct Point {
    double x; double y;
};

