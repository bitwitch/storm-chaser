#ifndef __APP_H__
#define __APP_H__

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdint.h>

// TODO(shaw): lookup how many keys should be used
// according the the SDL_SCANCODE_XXX enum values
//#define MAX_KEYBOARD_KEYS 128

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

#define FPS         60
#define TIME_STEP   (1000.0f / FPS)

typedef struct {
	SDL_Renderer *renderer;
	SDL_Window *window;

    bool quit;

    // input state
	//int keyboard[MAX_KEYBOARD_KEYS];
    bool up, down, left, right, enter, fire;
    int mouse_x, mouse_y;
} App;


void init_sdl(void);
void do_input(void);

extern App app;

#endif
