#pragma once

#include "types.h"

void render_background();
void render_splash(float width);
void render_hole(float x, float y);
void render_ball(float x, float y, float size);
void render_pointer(float x, float y, double angle);
void render_power_meter(float x, float y, Point p1, Point p2);
void render_logo();

void render_text(const std::string& text, SDL_Color text_color);
