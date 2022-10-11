#include <stdlib.h> // for rand
#include "app.h"
#include "renderer.h"
#include "game.h"
#include "background.h"
#include "player.h"
#include "tornado.h"
#include "debris.h"


/*static int reset_timer;*/

/*static void game_reset(void);*/

/*static bool bullet_hit_ship(Entity *b);*/
/*static bool bullet_hit_player(Entity *b);*/
/*static bool collide(Entity *a, Entity *b);*/
/*static bool player_hit_ship();*/

/*static void add_explosions(int x, int y, int num);*/
/*static void explosions_update(void);*/
/*static void explosions_render(void);*/

/*static void add_debris(Entity *e);*/
/*static void debris_update(void);*/
/*static void debris_render(void);*/

/*static void background_init(void);*/
/*static void background_update(void);*/
/*static void background_render(void);*/


/* time variables */
static uint64_t prev_counter;
static uint64_t performance_freq;

void game_init(void) {
    performance_freq = SDL_GetPerformanceFrequency();
    prev_counter     = SDL_GetPerformanceCounter();

    background_init();
    tornado_init();
    player_init();
    debris_init();

    /*game_reset();*/
}

/*static void game_reset(void) {*/
    /*player.x = 100;*/
    /*player.y = 100;*/
    /*player.health = 3;*/

    /*Entity *e;*/
    /*Explosion *ex;*/
    /*Debris *d;*/

    /*// delete bullets*/
    /*while (bullet_head.next) {*/
        /*e = bullet_head.next;*/
        /*free(e);*/
        /*bullet_head.next = e->next;*/
    /*}*/
    /*bullet_tail = &bullet_head;*/

    /*// delete ships*/
    /*while (ship_head.next) {*/
        /*e = ship_head.next;*/
        /*free(e);*/
        /*ship_head.next = e->next;*/
    /*}*/
    /*ship_tail = &ship_head;*/

    /*// delete explosions*/
    /*while (explosion_head.next) {*/
        /*ex = explosion_head.next;*/
        /*free(ex);*/
        /*explosion_head.next = ex->next;*/
    /*}*/
    /*explosion_tail = &explosion_head;*/

    /*// delete debris*/
    /*while (debris_head.next) {*/
        /*d = debris_head.next;*/
        /*free(d);*/
        /*debris_head.next = d->next;*/
    /*}*/
    /*debris_tail = &debris_head;*/


    /*reset_timer = FPS * 2;*/
/*}*/

void game_update(void) {
    static double accumulator = 0;
    static double delta_ms = 0;
    static uint64_t cur_counter = 0;
    static uint64_t counter_elapsed = 0;

    cur_counter = SDL_GetPerformanceCounter();
    counter_elapsed = cur_counter - prev_counter;
    delta_ms = (1000.0f * (double)counter_elapsed) / (double)performance_freq;
    prev_counter = cur_counter;

    accumulator += delta_ms;
    while (accumulator > TIME_STEP) {
        background_update();
        tornado_update(TIME_STEP);
        player_update(TIME_STEP);
        debris_update(TIME_STEP);
        accumulator -= TIME_STEP;
    }
}

void game_render(void) {
    background_render();
    tornado_render();
    player_render();
    debris_render();

    /*// draw ships*/
    /*Entity *e = &ship_head;*/
    /*for (e = e->next; e; e = e->next)*/
        /*blit(e->texture, e->x, e->y);*/

    /*// draw player*/
    /*if (player.health > 0)*/
        /*blit(player.texture, player.x, player.y);*/

    /*// draw bullets*/
    /*Entity *b = &bullet_head;*/
    /*for (b = b->next; b; b = b->next)*/
        /*blit(b->texture, b->x, b->y);*/

    /*debris_render();*/
    /*explosions_render();*/
}


/*static void player_update(void) {*/
    /*if (player.health <= 0) return;*/

    /*player.vx = player.vy = 0;*/

    /*// movement*/
    /*if (app.right && !app.left)*/
        /*player.x += player.speed;         */
    /*else if (app.left && !app.right)*/
        /*player.x -= player.speed;         */

    /*if (player.x <= 0) player.x = 0;*/
    /*else if (player.x+player.w >= SCREEN_WIDTH) player.x = SCREEN_WIDTH - player.w;*/

    /*if (app.up && !app.down)*/
        /*player.y -= player.speed;         */
    /*else if (app.down && !app.up)*/
        /*player.y += player.speed;         */

    /*if (player.y <= 0) player.y = 0;*/
    /*else if (player.y+player.h >= SCREEN_HEIGHT) player.y = SCREEN_HEIGHT - player.h;*/

    /*// shooting*/
    /*if (app.fire && player.reload <= 0) {*/
        /*fire_bullet();*/
        /*player.reload = 8;*/
    /*}*/
    /*if (player.reload-- < 0) player.reload = 0;*/

    /*// collide with enemies*/
    /*if (player_hit_ship()) {*/
        /*// do some effect here*/
    /*}*/
/*}*/

/*static void fire_bullet(void) {*/
    /*Entity *b = calloc(1, sizeof(Entity));*/
    /*b->w = bullet_width;*/
    /*b->h = bullet_height;*/
    /*b->x = player.x + 0.8*player.w - 0.5*b->w; */
    /*b->y = player.y + 0.5*player.h - 0.5*b->h;*/
    /*b->vx = 8.0;*/
    /*b->health = 1;*/
    /*b->side = SIDE_PLAYER;*/
    /*b->texture = bullet_texture;*/
    /*bullet_tail->next = b;*/
    /*bullet_tail = b;*/
/*}*/

/*static void enemy_fire_bullet(Entity *e) {*/
    /*Entity *b = calloc(1, sizeof(Entity));*/
    /*SDL_QueryTexture(enemy_bullet_texture, NULL, NULL, &b->w, &b->h);*/
    /*b->x = e->x + 0.2*e->w - 0.5*b->w;*/
    /*b->y = e->y + 0.5*e->h - 0.5*b->h;*/
    /*b->vx = e->vx + -(2 + rand() % 7);*/
    /*b->health = 1;*/
    /*b->side = SIDE_ENEMY;*/
    /*b->texture = enemy_bullet_texture;*/
    /*bullet_tail->next = b;*/
    /*bullet_tail = b;*/
/*}*/

/*static bool player_hit_ship() {*/
    /*Entity *e = &ship_head;*/
    /*for (e = e->next; e; e = e->next) {*/
        /*if (e->side != player.side && collide(&player, e)) {*/
            /*if (--player.health == 0) {*/
                /*add_explosions(player.x, player.y, 32);*/
                /*add_debris(&player);*/
            /*}*/
            /*if (--e->health == 0) {*/
                /*add_explosions(e->x, e->y, 32);*/
                /*add_debris(e);*/
            /*}*/
            /*return true;*/
        /*}*/
    /*}*/
    /*return false;*/
/*}*/

/*static void bullets_update(void) {*/
    /*Entity *b = &bullet_head;*/
    /*Entity *prev = b;*/

    /*for (b = b->next; b; b = b->next) {*/
        /*b->x += b->vx;*/
        /*b->y += b->vy;*/

        /*if (bullet_hit_ship(b) || bullet_hit_player(b) || b->x < -b->w || b->x > SCREEN_WIDTH) {*/
            /*if (b == bullet_tail)*/
                /*bullet_tail = prev;*/
            /*prev->next = b->next;*/
            /*free(b);*/
            /*b = prev;*/
        /*}*/
        /*prev = b;*/
    /*}*/
/*}*/

/*static bool bullet_hit_ship(Entity *b) {*/
    /*Entity *e = &ship_head;*/
    /*for (e = e->next; e; e = e->next) {*/
        /*if (b->side != e->side && collide(b, e)) {*/
            /*--b->health;*/
            /*if (--e->health == 0) {*/
                /*add_explosions(e->x, e->y, 32);*/
                /*add_debris(e);*/
            /*}*/
            /*return true;*/
        /*}*/
    /*}*/
    /*return false;*/
/*}*/

/*static bool bullet_hit_player(Entity *b) {*/
    /*if (b->side != player.side && collide(b, &player)) {*/
        /*--b->health;*/
        /*if (--player.health == 0) {*/
            /*add_explosions(player.x, player.y, 32);*/
            /*add_debris(&player);*/
        /*}*/
        /*return true;*/
    /*}*/
    /*return false;*/
/*}*/

/*static bool collide(Entity *a, Entity *b) {*/
    /*return (MAX(a->x, b->x) < MIN(a->x + a->w, b->x + b->w)) && */
           /*(MAX(a->y, b->y) < MIN(a->y + a->h, b->y + b->h));*/
/*}*/

/*static void spawn_enemies(void) {*/
    /*static int spawn_timer;*/

    /*if (--spawn_timer <= 0) {*/
        /*spawn_timer = 30 + (rand() % 60);*/
        /*Entity *e = calloc(1, sizeof(Entity));*/
        /*SDL_QueryTexture(enemy_texture, NULL, NULL, &e->w, &e->h);*/
        /*e->x = SCREEN_WIDTH;*/
        /*e->y = rand() % SCREEN_HEIGHT;*/
        /*while (e->y + e->h > SCREEN_HEIGHT) */
            /*e->y = rand() % SCREEN_HEIGHT;*/
        /*e->vx = -(2 + (rand() % 4));*/
        /*e->health = 1;*/
        /*e->side = SIDE_ENEMY;*/
        /*e->texture = enemy_texture;*/
        /*ship_tail->next = e;*/
        /*ship_tail = e;*/
    /*}*/
/*}*/

//////////////////////////////////////////////////////////////////////////////
// EXPLOSIONS
//////////////////////////////////////////////////////////////////////////////
/*static void add_explosions(int x, int y, int num) {*/
    /*for (int i=0; i<num; ++i) {*/
        /*Explosion *e = calloc(1, sizeof(Explosion));*/
        /*e->x  = x + (rand()%32 - rand()%32);*/
        /*e->y  = y + (rand()%32 - rand()%32);*/
        /*e->vx = 0.1 * (rand()%10 - rand()%10);*/
        /*e->vy = 0.1 * (rand()%10 - rand()%10);*/

		/*switch (rand() % 4) {*/
            /*case 0:  e->r = 255; break;*/
            /*case 1:  e->r = 255; e->g = 128; break;*/
            /*case 2:  e->r = 255; e->g = 255; break;*/
            /*default: e->r = 255; e->g = 255; e->b = 255; break;*/
		/*}*/

        /*e->a = rand() % (FPS*2);*/

        /*explosion_tail->next = e;*/
        /*explosion_tail = e;*/
    /*}*/
/*}*/

/*static void explosions_update(void) {*/
    /*Explosion *e = &explosion_head;*/
    /*Explosion *prev = e;*/
    /*for (e = e->next; e; e = e->next) {*/
        /*e->x += e->vx;*/
        /*e->y += e->vy;*/
        /*if (e->a-- <= 0) {*/
            /*if (e == explosion_tail)*/
                /*explosion_tail = prev;*/
            /*prev->next = e->next;*/
            /*free(e);*/
            /*e = prev;*/
        /*}*/
        /*prev = e;*/
    /*}*/
/*}*/

/*static void explosions_render(void) {*/
    /*Explosion *e = &explosion_head;*/

	/*SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_ADD);*/

    /*for (e = e->next; e; e = e->next) {*/
        /*SDL_SetTextureColorMod(explosion_texture, e->r, e->g, e->b);*/
		/*SDL_SetTextureAlphaMod(explosion_texture, e->a);*/
		/*blit(explosion_texture, e->x, e->y); */
    /*}*/

	/*SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_NONE);*/
/*}*/

//////////////////////////////////////////////////////////////////////////////
// DEBRIS
//////////////////////////////////////////////////////////////////////////////
/*static void add_debris(Entity *e) {*/
    /*int rows = 2;*/
    /*int cols = 2;*/
    /*int row_h = e->h/rows;*/
    /*int col_w = e->w/rows;*/

    /*for (int row=0; row<rows; ++row)*/
    /*for (int col=0; col<cols; ++col)*/
    /*{*/
        /*Debris *d = calloc(1, sizeof(Debris));*/
        /*d->x  = e->x + 0.5*e->w;*/
        /*d->y  = e->y + 0.5*e->h;*/
        /*d->vx = 0.3 * (rand()%10 - rand()%10);*/
        /*d->vy = 0.3 * (rand()%10 - rand()%10);*/
        /*d->life = FPS*2;*/
        /*d->texture = e->texture;*/
        /*d->rect = (SDL_Rect) {*/
            /*.x = col * col_w,*/
            /*.y = row * row_h,*/
            /*.w = col_w,*/
            /*.h = row_h,*/
        /*};*/

        /*debris_tail->next = d;*/
        /*debris_tail = d;*/
    /*}*/
/*}*/

/*static void debris_update(void) {*/
    /*Debris *d = &debris_head;*/
    /*Debris *prev = d;*/
    /*for (d = d->next; d; d = d->next) {*/
        /*d->x += d->vx;*/
        /*d->y += d->vy;*/
        /*if (d->life-- <= 0) {*/
            /*if (d == debris_tail)*/
                /*debris_tail = prev;*/
            /*prev->next = d->next;*/
            /*free(d);*/
            /*d = prev;*/
        /*}*/
        /*prev = d;*/
    /*}*/
/*}*/

/*static void debris_render(void) {*/
    /*Debris *d = &debris_head;*/
    /*for (d = d->next; d; d = d->next) {*/
		/*SDL_SetTextureAlphaMod(d->texture, d->life);*/
        /*blit_rect(d->texture, &d->rect, d->x, d->y);*/
		/*SDL_SetTextureAlphaMod(d->texture, 255);*/
    /*}*/
/*}*/


