#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <glad/glad.h>
#include <iostream>

#include "renderer.h"
#include "types.h"

#define M_PI 3.14159265358979323846

void render_background() {
    glBindTexture(GL_TEXTURE_2D, bgId);
    glEnable(GL_TEXTURE_2D); 

    const float h_unit = 2.0f / WIN_WIDTH;
    const float v_unit = 2.0f / WIN_HEIGHT;
    const float imageWidth = 640.0 * h_unit;
    const float imageHeight = 480.0 * v_unit;

    const float fullRatio = WIN_WIDTH / 640.0; 

    float left = -1.0;
    float right = left + imageWidth * fullRatio;
    float top = 1.0;
    float bottom = top - imageHeight * fullRatio;

    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f);
        glVertex2f(left, bottom);
        glTexCoord2f(1.0f, 0.0f);
        glVertex2f(right, bottom);
        glTexCoord2f(1.0f, 1.0f);
        glVertex2f(right, top);
        glTexCoord2f(0.0f, 1.0f);
        glVertex2f(left, top);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void render_hole(float x, float y) {
    glBindTexture(GL_TEXTURE_2D, holeId);
    glEnable(GL_TEXTURE_2D); 
    glEnable(GL_BLEND);


    const float h_unit = 2.0f / WIN_WIDTH;
    const float v_unit = 2.0f / WIN_HEIGHT;
    const float imageWidth = 16.0 * h_unit;
    const float imageHeight = 19.0 * v_unit;

    const float pos_x = x * h_unit;
    const float pos_y = y * v_unit;

    float left = -1.0 + pos_x;
    float right = left + imageWidth;
    float top = 1.0 + pos_y;
    float bottom = top - imageHeight;

    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f);
        glVertex2f(left, bottom);
        glTexCoord2f(1.0f, 0.0f);
        glVertex2f(right, bottom);
        glTexCoord2f(1.0f, 1.0f);
        glVertex2f(right, top);
        glTexCoord2f(0.0f, 1.0f);
        glVertex2f(left, top);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
}

void render_ball(float x, float y, float size) {
    glBindTexture(GL_TEXTURE_2D, ballId);
    glEnable(GL_TEXTURE_2D); 
    glEnable(GL_BLEND);


    const float h_unit = 2.0f / WIN_WIDTH;
    const float v_unit = 2.0f / WIN_HEIGHT;
    const float imageWidth = size * h_unit;
    const float imageHeight = size * v_unit;

    const float pos_x = x * h_unit;
    const float pos_y = y * v_unit;

    float left = -1.0 + pos_x;
    float right = left + imageWidth;
    float top = 1.0 + pos_y;
    float bottom = top - imageHeight;

    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f);
        glVertex2f(left, bottom);
        glTexCoord2f(1.0f, 0.0f);
        glVertex2f(right, bottom);
        glTexCoord2f(1.0f, 1.0f);
        glVertex2f(right, top);
        glTexCoord2f(0.0f, 1.0f);
        glVertex2f(left, top);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
}

void render_pointer(float x, float y, double angle) {
    glBindTexture(GL_TEXTURE_2D, pointerId);
    glEnable(GL_TEXTURE_2D); 
    glEnable(GL_BLEND);


    const float h_unit = 2.0f / WIN_WIDTH;
    const float v_unit = 2.0f / WIN_HEIGHT;
    const float imageWidth = 16.0 * h_unit;
    const float imageHeight = 64.0 * v_unit;

    const float pos_x = x * h_unit;
    const float pos_y = (y + 12) * v_unit;

    float left = -1.0 + pos_x;
    float right = left + imageWidth;
    float top = 1.0 + pos_y;
    float bottom = top - imageHeight;

    float centerX = (left + right) / 2.0f;
    float centerY = (top + bottom + 0.1) / 2.0f;

    glPushMatrix();
    glTranslatef(centerX, centerY, 0.0f);
    glRotatef(angle, 0.0f, 0.0f, 1.0f);
    glTranslatef(-centerX, -centerY, 0.0f);

    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f);
        glVertex2f(left, bottom);
        glTexCoord2f(1.0f, 0.0f);
        glVertex2f(right, bottom);
        glTexCoord2f(1.0f, 1.0f);
        glVertex2f(right, top);
        glTexCoord2f(0.0f, 1.0f);
        glVertex2f(left, top);
    glEnd();

    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
}

void render_power_meter_overlay(float x, float y) {
    glEnable(GL_TEXTURE_2D); 
    glEnable(GL_BLEND);


    const float h_unit = 2.0f / WIN_WIDTH;
    const float v_unit = 2.0f / WIN_HEIGHT;

    /**
     * Render Overlay
    */
    glBindTexture(GL_TEXTURE_2D, powermeterOId);
    const float imageWidth = 16 * h_unit;
    const float imageHeight = 64 * v_unit;

    const float pos_x = x * h_unit;
    const float pos_y = y * v_unit;

    float left = -1.0 + pos_x;
    float right = left + imageWidth;
    float top = 1.0 + pos_y;
    float bottom = top - imageHeight;

    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f);
        glVertex2f(left, bottom);
        glTexCoord2f(1.0f, 0.0f);
        glVertex2f(right, bottom);
        glTexCoord2f(1.0f, 1.0f);
        glVertex2f(right, top);
        glTexCoord2f(0.0f, 1.0f);
        glVertex2f(left, top);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
}

void render_power_meter_bg(float x, float y) {
    glEnable(GL_TEXTURE_2D); 
    glEnable(GL_BLEND);


    const float h_unit = 2.0f / WIN_WIDTH;
    const float v_unit = 2.0f / WIN_HEIGHT;

    /**
     * Render Overlay
    */
    glBindTexture(GL_TEXTURE_2D, powermeterBId);
    const float imageWidth = 16 * h_unit;
    const float imageHeight = 64 * v_unit;

    const float pos_x = x * h_unit;
    const float pos_y = y * v_unit;

    float left = -1.0 + pos_x;
    float right = left + imageWidth;
    float top = 1.0 + pos_y;
    float bottom = top - imageHeight;

    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f);
        glVertex2f(left, bottom);
        glTexCoord2f(1.0f, 0.0f);
        glVertex2f(right, bottom);
        glTexCoord2f(1.0f, 1.0f);
        glVertex2f(right, top);
        glTexCoord2f(0.0f, 1.0f);
        glVertex2f(left, top);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
}

void render_power_meter_fg(float x, float y, Point p1, Point p2) {
    glEnable(GL_TEXTURE_2D); 
    glEnable(GL_BLEND);


    const float h_unit = 2.0f / WIN_WIDTH;
    const float v_unit = 2.0f / WIN_HEIGHT;

    const double dist = p1.x == -1 ? 0 : std::max(0.0, std::min(10.0, std::hypot(p2.x - p1.x, p2.y - p1.y) / 30.0)) / 10.0;

    /**
     * Render Overlay
    */
    glBindTexture(GL_TEXTURE_2D, powermeterFId);
    const float imageWidth = 8 * h_unit;
    const float imageHeight = 56 * dist * v_unit;

    const float pos_x = (x + 4) * h_unit;
    const float pos_y = (y - 4 - 56) * v_unit;

    float left = -1.0 + pos_x;
    float right = left + imageWidth;
    float top = 1.0 + pos_y;
    float bottom = top + imageHeight;

    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f);
        glVertex2f(left, bottom);
        glTexCoord2f(1.0f, 0.0f);
        glVertex2f(right, bottom);
        glTexCoord2f(1.0f, 1.0f);
        glVertex2f(right, top);
        glTexCoord2f(0.0f, 1.0f);
        glVertex2f(left, top);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
}

void render_power_meter(float x, float y, Point p1, Point p2) {
    // render_power_meter_overlay(x, y);
    render_power_meter_bg(x, y);
    render_power_meter_fg(x, y, p1, p2);
}

void render_splash(float width) {
    glBindTexture(GL_TEXTURE_2D, splashScreenId);
    glEnable(GL_TEXTURE_2D); 
    glEnable(GL_BLEND);


    const float h_unit = 2.0f / WIN_WIDTH;
    const float v_unit = 2.0f / WIN_HEIGHT;
    const float imageWidth = width * h_unit;
    const float imageHeight = 480.0 * v_unit;

    const float fullRatio = WIN_WIDTH / 640.0; 

    float left = -imageWidth / 2.0;
    float right = left + imageWidth * fullRatio;
    float top = 0.5;
    float bottom = top - imageHeight * fullRatio;

    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f);
        glVertex2f(left, bottom);
        glTexCoord2f(1.0f, 0.0f);
        glVertex2f(right, bottom);
        glTexCoord2f(1.0f, 1.0f);
        glVertex2f(right, top);
        glTexCoord2f(0.0f, 1.0f);
        glVertex2f(left, top);
    glEnd();

    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);
}

float oscillationSpeed = 0.05f;
float oscillationAmplitude = 0.1f;
int angle = 0;

void render_logo() {
    angle += 1;
    float disp = oscillationAmplitude * sin(angle * M_PI / 180);

    if (angle == 360) angle = 0;

    glBindTexture(GL_TEXTURE_2D, logoId);
    glEnable(GL_TEXTURE_2D); 
    glEnable(GL_BLEND);

    const float h_unit = 2.0f / WIN_WIDTH;
    const float v_unit = 2.0f / WIN_HEIGHT;
    const float imageWidth = 319.0 * h_unit / 1.2;
    const float imageHeight = 201.0 * v_unit / 1.2;

    const float fullRatio = WIN_WIDTH / 640.0; 

    float left = 0.0 - imageWidth / 2.0;
    float right = left + imageWidth * fullRatio;
    float top = 0.4 + disp;
    float bottom = top - imageHeight * fullRatio;

    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f);
        glVertex2f(left, top);
        glTexCoord2f(1.0f, 0.0f);
        glVertex2f(right, top);
        glTexCoord2f(1.0f, 1.0f);
        glVertex2f(right, bottom);
        glTexCoord2f(0.0f, 1.0f);
        glVertex2f(left, bottom);
    glEnd();

    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);
}

int next_power_of_2(int x) {
	double logbase2 = log(x) / log(2);
	return round(pow(2,ceil(logbase2)));
}


void render_text(const std::string& text, SDL_Color color) {
    SDL_Surface *initial, *intermediary;
    int w, h;
    GLuint texture;

    initial = TTF_RenderText_Blended(font, text.c_str(), color);

    w = next_power_of_2(initial->w);
    h = next_power_of_2(initial->h);

    intermediary = SDL_CreateRGBSurface(0, w, h, 32, 
        0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000
    );

    SDL_BlitSurface(initial, 0, intermediary, 0);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, w, h, 0, GL_BGRA, 
			GL_UNSIGNED_BYTE, intermediary->pixels );

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D, texture);
	glColor3f(1.0f, 1.0f, 1.0f);

    const float h_unit = 2.0f / WIN_WIDTH;
    const float v_unit = 2.0f / WIN_HEIGHT;

    const float imageWidth = w * h_unit;
    const float imageHeight = h * v_unit;

    const float fullRatio = WIN_WIDTH / 640.0; 

    float left = -imageWidth / 2.0 + 0.03;
    float right = left + imageWidth * fullRatio;
    float top = -0.43;
    float bottom = top - imageHeight * fullRatio;


    glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f); 
			glVertex2f(left, bottom);
		glTexCoord2f(1.0f, 1.0f); 
			glVertex2f(right, bottom);
		glTexCoord2f(1.0f, 0.0f); 
			glVertex2f(right, top);
		glTexCoord2f(0.0f, 0.0f); 
			glVertex2f(left, top);   
	glEnd();

    glFinish();
    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);


    SDL_FreeSurface(initial);
	SDL_FreeSurface(intermediary);
	glDeleteTextures(1, &texture);


}