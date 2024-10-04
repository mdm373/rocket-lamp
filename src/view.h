#ifndef VIEW_INCLUDE
#define VIEW_INCLUDE

#include "poll_button.h"

typedef void (*View)(ButtonAction action, float scale);

void view_rainbow(ButtonAction action, float scale);
void view_white(ButtonAction action, float scale);
void view_mix(ButtonAction action, float scale);
void view_rocket(ButtonAction action, float scale);

#endif