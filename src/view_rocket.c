#include <stdlib.h>
#include "rgb_color.h"
#include "view.h"

#define ROCKET_SIZE (END_ROCKET_PIXEL-END_FIRE_PIXEL)
#define FLAME_SIZE END_FIRE_PIXEL
#define MAX_RANK 11

static RgbColorComps fire_base;
static RgbColorComps fire_bright;
static RgbColorComps fire_dark;
static RgbColorComps moon_face;
static RgbColorComps rocket_body;
static uint8_t moon_pos;
static uint8_t rocket_rank[ROCKET_SIZE];
static rgb_color flame_colors[FLAME_SIZE];
static uint8_t rocket_pos;
static uint8_t rocket_speed;
static uint8_t flame_speed;
static uint8_t flame_duration;

void populate_flame() {
for (int i = 0; i < FLAME_SIZE; ++i) {
    int rnd = rand() % 16;
    RgbColorComps color = fire_base;
    if(rnd <= 0 ) {
      color = fire_dark;
    }
    if(rnd > 0 && rnd < 4) {
      color = fire_bright;
    }
    flame_colors[i] = comps_as_rgb_color(color);
  }
}

void view_rocket(ButtonAction action, float scale) { 
  if(action == BUTTON_ACTION_PRESS_LONG_UP) {
    flame_speed = 2;
    flame_duration = 0;
    populate_flame();
    rocket_speed = 6;
    rocket_pos = 0;
    fire_base = as_rgb_color_comps(154, 15, 10);
    fire_bright =  as_rgb_color_comps(255, 92, 0);
    fire_dark =  as_rgb_color_comps(141, 2, 31);
    moon_face = as_rgb_color_comps(30, 50, 255);
    rocket_body = as_rgb_color_comps(255, 255, 255);
    moon_pos = 0;
    rocket_rank[0] = 2;
    rocket_rank[1] = 3;
    rocket_rank[2] = 4;
    rocket_rank[3] = 5;

    rocket_rank[4] = 2;
    rocket_rank[5] = 3;
    rocket_rank[6] = 4;
    rocket_rank[7] = 5;
    rocket_rank[8] = 6;
    rocket_rank[9] = 7;
    rocket_rank[10] = 8;
    rocket_rank[11] = 9;
    
    rocket_rank[12] = 9;
    rocket_rank[13] = 8;
    rocket_rank[14] = 7;
    rocket_rank[15] = 6;
    rocket_rank[16] = 5;
    rocket_rank[17] = 4;
    rocket_rank[18] = 3;
    rocket_rank[19] = 2;
  }
  if(action == BUTTON_ACTION_PRESS_UP) {
    flame_speed = (flame_speed + 2) % 8;
    if(flame_speed < 2 ) {
      flame_speed = 2;
    }
    rocket_pos = 0;
    rocket_speed = (rocket_speed + 3) % 15;
    if(rocket_speed < 3) {
      rocket_speed = 3;
    }
  }
  
  for (int i = 0; i < FLAME_SIZE; ++i) {
    rgb_color_put(flame_colors[i]);
  }
  flame_duration = flame_duration + FRAME_MS;
  if(flame_duration > (flame_speed * FRAME_MS)) {
    populate_flame();
    flame_duration = 0;
  }

  int rocket_pos_scaled = MAX_RANK*rocket_speed - rocket_pos;
  for (int i = 0; i < ROCKET_SIZE; ++i) {
    float distance = (abs( (rocket_rank[i]*rocket_speed) - rocket_pos_scaled)) / 2.0f;
    float scaled = 0;
    if(distance == 0) {
      scaled = 1;
    }
    if(distance <= 5 && distance > 0) {
      scaled = 1.0f / (float)distance;
    }
    
    rgb_color_put(comps_as_rgb_color_scaled(rocket_body, scaled));
  }
  rocket_pos = (rocket_pos+1) % (MAX_RANK*rocket_speed);

  for (int i = END_ROCKET_PIXEL; i < NUM_PIXELS; ++i) {
    rgb_color_put(comps_as_rgb_color_scaled(moon_face,  1.0f - scale));
  }
}