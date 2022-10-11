#include "app.h"
#include "renderer.h"
#include "entity.h"

static double elapsed_ms;
static Entity van;
static Entity camera_guy;

void player_init(void) {
    elapsed_ms = 0;

    /* news van */
    if (van.texture == NULL) {
        van.texture = load_texture("assets/van.png");
        SDL_QueryTexture(van.texture, NULL, NULL, &van.w, &van.h);
    }
    van.speed = 6;
    van.health = 100;
    van.side = SIDE_PLAYER;
    van.x = 15;
    van.y = SCREEN_HEIGHT - van.h - 60;

    /* camera guy */
    if (camera_guy.texture == NULL) {
        camera_guy.texture = load_texture("assets/cameraman.png");
        SDL_QueryTexture(camera_guy.texture, NULL, NULL, &camera_guy.w, &camera_guy.h);
    }
    camera_guy.speed = 6;
    camera_guy.health = 100;
    camera_guy.side = SIDE_PLAYER;
    camera_guy.x = 15;
    camera_guy.y = SCREEN_HEIGHT - camera_guy.h - 60;
}

void player_update(double delta_ms) {
    elapsed_ms += delta_ms;

    /* news van */
    van.vx = 0;
    van.vy = 0;
    if (app.left)  van.vx  = -van.speed;
    if (app.right) van.vx  =  van.speed;
    van.vy = sin(elapsed_ms * 0.1f);
    van.x += van.vx;
    van.y += van.vy;
    if (van.x < 0) van.x = 0;
    if (van.x + van.w >= SCREEN_WIDTH)
        van.x = SCREEN_WIDTH - van.w;

    /* camera guy */
    camera_guy.x = app.mouse_x - 0.5*camera_guy.w;
    camera_guy.y = app.mouse_y - 0.5*camera_guy.h;


}

void player_render(void) {
    blit(van.texture, van.x, van.y);
    blit(camera_guy.texture, camera_guy.x, camera_guy.y);
}
