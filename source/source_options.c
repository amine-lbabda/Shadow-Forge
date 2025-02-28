#include <SDL/SDL_mixer.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include "options.h"

int verif_collision_2(SDL_Event e, image button) {
    if (!button.image) return 0;
    return (e.motion.x > button.rect.x && e.motion.x < button.rect.x + button.rect.w &&
            e.motion.y > button.rect.y && e.motion.y < button.rect.y + button.rect.h);
}
