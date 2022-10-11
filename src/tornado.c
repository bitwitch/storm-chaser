#include "app.h"
#include "renderer.h"
#include "entity.h"
#include "tornado.h"

Tornado tornado = {0};

void tornado_init(void) {
    tornado.w = 10; tornado.h = SCREEN_HEIGHT;
    tornado.x = SCREEN_WIDTH - 200;
    tornado.y = 0;
    tornado.pull = 100.0f;
}

void tornado_update(double delta_ms) {

}

void tornado_render(void) {
    fill_rect(tornado.x, tornado.y, tornado.w, tornado.h, 0x00FF00FF);
}


