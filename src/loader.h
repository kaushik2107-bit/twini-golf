#pragma once
#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <glad/glad.h>

bool image_loader(const std::string& filepath, GLuint &id);
bool font_loader(const std::string& filepath, int fontSize);