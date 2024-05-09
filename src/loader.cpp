#include "loader.h"
#include "types.h"

bool image_loader(const std::string& filepath, GLuint &id) {
    SDL_Surface* surface = IMG_Load(filepath.c_str());
    if (surface == nullptr) {
        std::cerr << "Failed to load texture from the path: " << filepath << std::endl;
        return false;
    }
    
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    std::cout << filepath << " " << surface->w << " " << surface->h << std::endl;

    SDL_FreeSurface(surface);
    return true;
}

bool font_loader(const std::string& filepath, int fontSize) {
    font = TTF_OpenFont(filepath.c_str(), fontSize);
    if (font == nullptr) {
        std::cerr << "Failed to load font from the path: " << filepath << std::endl;
        return false;
    }

    return true;
}