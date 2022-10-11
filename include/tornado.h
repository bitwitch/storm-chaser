#ifndef __TORNADO_H__
#define __TORNADO_H__

typedef struct {
    float x, y, vx, vy;
    int w, h;
    float speed;
    float pull;
} Tornado;

void tornado_init(void);
void tornado_update(double delta_ms);
void tornado_render(void);

extern Tornado tornado;

#endif
