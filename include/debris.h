#ifndef __DEBRIS_H__
#define __DEBRIS_H__

void debris_init(void);
void debris_update(double delta_ms);
void debris_render(void);
int debris_make(int x, int y, int w, int h, SDL_Texture *texture);
int debris_make_random(int x, int y, int w, int h);

#endif
