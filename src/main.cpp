#include <iostream>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <glad/glad.h>
#include <math.h>

#include "types.h"
#include "loader.h"
#include "init.h"
#include "load_assets.h"
#include "renderer.h"

#define M_PI 3.14159265358979323846

int WIN_WIDTH = 640;
int WIN_HEIGHT = 480;

Point ball1 = { WIN_WIDTH / 4.0 - 8, -WIN_HEIGHT + 100.0 };
Point ball2 = { 3 * WIN_WIDTH / 4.0 - 8, -WIN_HEIGHT + 100.0 };
double angle1 = 0;
double angle2 = 0;

float speed1 = 0.0;
float speed2 = 0.0;

float size1 = 16.0;
float size2 = 16.0;

double max_speed = 10;
double friction = 0.1;

Point start = {-1, -1};
Point end = {-1, -1};

int currentLevel = 1;
int totalLevels = 1;
bool started = false;

/**
 * Required DataTypes
*/
SDL_Window* window = nullptr;
SDL_GLContext context;
GLuint bgId;
GLuint ballId;
GLuint pointerId;
GLuint holeId;
GLuint powermeterFId;
GLuint powermeterBId;
GLuint powermeterOId;
GLuint splashScreenId;
GLuint logoId;

TTF_Font* font;

void close();
void display(bool);

int main() {
    if (!init()) {
        std::cerr << "Failed to initialize!" << std::endl;
        return -1;
    }

    /**
     * Loading all the assets of the game
    */
    load_assets();

    /**
     * Game Loop starts
    */
    bool quit = false;
    bool isDragging = false;
    bool isOver1 = false, isOver2 = false;
    SDL_Event event;

    const int UPDATE_FREQUENCY{ 128 };
    const float CYCLE_TIME{ 1.0f / UPDATE_FREQUENCY };

    static Timer system_timer;
    float accumulated_seconds{0.0f};
    while (!quit) {
        system_timer.tick();
        accumulated_seconds += system_timer.elapsed_seconds;

        if (isOver1) size1 -= 0.1;
        if (isOver2) size2 -= 0.1;
        if (isOver1 && size1 <= 0) {
            isOver1 = false;
            size1 = 16;
            ball1 = { WIN_WIDTH / 4.0 - 8, -WIN_HEIGHT + 100.0 };
        }

        if (isOver2 && size2 <= 0) {
            isOver2 = false;
            size2 = 16;
            ball2 = { 3 * WIN_WIDTH / 4.0 - 8, -WIN_HEIGHT + 100.0 };
        }

        if (std::isgreater(accumulated_seconds, CYCLE_TIME)) {
            accumulated_seconds = -CYCLE_TIME;

            /**
             * Event loop checking for events in the queue
            */
            while (SDL_PollEvent(&event)) {
                switch (event.type) {
                    case SDL_QUIT:
                        quit = true;
                        break;
                    case SDL_MOUSEBUTTONDOWN:
                        if (event.button.button == SDL_BUTTON_LEFT) {
                            isDragging = true;
                            end.x = event.button.x;
                            end.y = event.button.y;
                        }
                        break;
                    case SDL_MOUSEMOTION:
                        if (isDragging) {
                            start.x = event.motion.x;
                            start.y = event.motion.y;
                            
                            int dx = end.x - start.x;
                            int dy = end.y - start.y;
                            angle1 = angle2 = atan2(dy, dx) * 180.0 / M_PI;
                        }
                        break;
                    case SDL_MOUSEBUTTONUP:
                        if (isDragging && event.button.button == SDL_BUTTON_LEFT) {
                            isDragging = false;
                            start.x = event.button.x;
                            start.y = event.button.y;
                            int dx = end.x - start.x;
                            int dy = end.y - start.y;
                            speed1 = speed2 = std::max(0.0, std::min(max_speed, std::hypot(dx, dy) / 30));
                        }
                        break;
                    default: 
                        break;
                }
            }

            /**
             * Moving the ball and collision detection
            */
            if (speed1 > 0) {
                float dx = std::sin((angle1 + 90) * M_PI / 180.0) * speed1;
                float dy = std::cos((angle1 + 90) * M_PI / 180.0) * speed1;
                
                if (ball1.x + dx <= 0) {
                    angle1 = 180 - angle1;
                    continue;
                }

                if (ball1.x + dx + 16.0 >= WIN_WIDTH / 2.0) {
                    angle1 = 180 - angle1;
                    continue;
                }

                if (ball1.y + dy >= 0) {
                    angle1 = 360 - angle1;
                    continue;
                }

                if (ball1.y + dy - 16.0 <= -WIN_HEIGHT) {
                    angle1 = 360 - angle1;
                    continue;
                }

                
                ball1.x += dx;
                ball1.y += dy;
                speed1 -= friction;
                
                float delta = 8;
                if (ball1.x <= WIN_WIDTH / 4.0 + delta
                    && ball1.x >= WIN_WIDTH / 4.0 - 2 * delta
                    && ball1.y >= -50 - delta
                    && ball1.y <= -50 + delta
                ) {
                    speed1 = 0;
                    ball1.x = WIN_WIDTH / 4.0 - 8;
                    ball1.y = -50.0;
                    isOver1 = true;
                }
                
            }

            if (speed2 > 0) {
                float dx = std::sin((angle2 + 90) * M_PI / 180.0) * speed2;
                float dy = std::cos((angle2 + 90) * M_PI / 180.0) * speed2;
                
                if (ball2.x + dx <= WIN_WIDTH/2.0) {
                    angle2 = 180 - angle2;
                    continue;
                }

                if (ball2.x + dx + 16.0 >= WIN_WIDTH) {
                    angle2 = 180 - angle2;
                    continue;
                }

                if (ball2.y + dy >= 0) {
                    angle2 = 360 - angle2;
                    continue;
                }

                if (ball2.y + dy - 16.0 <= -WIN_HEIGHT) {
                    angle2 = 360 - angle2;
                    continue;
                }

                ball2.x += dx;
                ball2.y += dy;
                
                speed2 -= friction;

                float delta = 8;
                if (ball2.x <= 3 * WIN_WIDTH / 4.0 + delta
                    && ball2.x >= 3 * WIN_WIDTH / 4.0 - 2*delta
                    && ball2.y >= -50 - delta
                    && ball2.y <= -50 + delta
                ) {
                    speed2 = 0;
                    ball2.x = 3 * WIN_WIDTH / 4.0 - 8;
                    ball2.y = -50.0;
                    isOver2 = true;
                }
            }
            
            display(isDragging);

        }

    }

    close();

    return 0;
}

void display(bool isDragging) {
    /**
     * Clearning buffer
    */
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    SDL_GetWindowSize(window, &WIN_WIDTH, &WIN_HEIGHT);
    glViewport(0, 0, WIN_WIDTH, WIN_HEIGHT);

    
    /**
     * Rendering Background Image
    */
    render_background();

    /**
     * Rendering splash screen
    */
    if (!started) {
        render_logo();
        render_splash(900.0);
        SDL_Color text_col{ 255, 255, 255, 255 };
        render_text("A", text_col);
        goto swap_window;
    }

    /**
     * Rendering hole
    */
    render_hole(WIN_WIDTH / 4.0 - 8, -50.0);
    render_hole(3 * WIN_WIDTH / 4.0 - 8, -50.0);

    /**
     * Rendering blocks
    */

    /**
     * Rendering Ball Image
    */
    render_ball(ball1.x, ball1.y, size1);
    render_ball(ball2.x, ball2.y, size2);

    /**
     * Rendering pointer
    */
    if (isDragging) {
        render_pointer(ball1.x, ball1.y, -angle1 + 90);
        render_pointer(ball2.x, ball2.y, -angle2 + 90);
    }

    /**
     * Rendering Power Meter
    */
    if (isDragging) {
        render_power_meter(ball1.x + 30, ball1.y + 32, start, end);
        render_power_meter(ball2.x + 30, ball2.y + 32, start, end);
    }

swap_window:
    /**
     * Swapping window buffers
    */
    SDL_GL_SwapWindow(window);
}

void close() {
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
}