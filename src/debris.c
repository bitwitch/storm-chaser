#include <assert.h>
#include <math.h>
#include "app.h"
#include "tornado.h"
#include "renderer.h"

#define MAX_DEBRIS  64

typedef struct {
    SDL_Texture *texture;
    int w, h;    
    float x, y, vx, vy;
    float speed;
    bool active;
} Debris;

static SDL_Texture *plank_texture;
static SDL_Texture *wrecked_car_texture;

static Debris debris_pool[MAX_DEBRIS];
static int debris_next_id;

static int orbit_radius = 50;
static int orbit_threshold = 25;
static int suck_distance = 1000;
static double elapsed_ms;

int debris_make(int x, int y, int w, int h, SDL_Texture *texture) {
    assert(debris_next_id < MAX_DEBRIS);
    int id = debris_next_id++;
    debris_pool[id] = (Debris){ 
        .x = x, .y = y, .w = w, .h = h, 
        .texture = texture, 
        .active = true };
    return id;
}

int debris_make_random(int x, int y, int w, int h) {
    SDL_Texture *texture = (rand() % 2 == 0)
        ? plank_texture 
        : wrecked_car_texture;
    return debris_make(x, y, w, h, texture);
};

void debris_init(void) {
    memset(debris_pool, 0, sizeof(debris_pool));
    debris_next_id = 0;

    if (plank_texture == NULL)
        plank_texture = load_texture("assets/planks.jpg");
    if (wrecked_car_texture == NULL)
        wrecked_car_texture = load_texture("assets/wrecked_car_01.png");

    debris_make(200, 500, 200, 100, plank_texture);
    debris_make(800, 500, 220, 110, wrecked_car_texture);
}

void debris_update(double delta_ms) {
    elapsed_ms += delta_ms;

    int min = tornado.x - orbit_radius - orbit_threshold;
    int max = tornado.x + orbit_radius + orbit_threshold;

    for (int i=0; i<debris_next_id; ++i) {
        Debris *d = &debris_pool[i];
        if (!d->active) continue;

        float center = d->x + 0.5*d->w;
        float x_distance = fabsf(center - tornado.x);

        /* get sucked into tornado */
        if (x_distance < suck_distance) {
            int dir = center < tornado.x ? 1 : -1;
            if (center < min || center > max) {
                d->vx += dir * tornado.pull/x_distance;

            /* if in close radius, orbit the tornado */
            } else {
                static int y_dir = 1;
                if (d->y > SCREEN_HEIGHT - d->h - 100)
                    y_dir = -1;
                else if (d->y < 50)
                    y_dir = 1;

                float y_hover_speed = 0.5f;
                d->vy = y_dir * y_hover_speed;
            }
        }

        d->x += d->vx;
        d->y += d->vy;

        if (fabs(d->vx) > 4.0 || d->y == 0)
            d->vx *= 0.8;

        if (fabs(d->vy) > 2.0)
            d->vy *= 0.8;

    }
}

void debris_render(void) {
    for (int i=0; i<debris_next_id; ++i) {
        Debris *d = &debris_pool[i];
        if (d->active) 
            blit_scaled(d->texture, d->x, d->y, d->w, d->h);
    }
}



