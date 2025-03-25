#include <ArduboyFX.h>  
#include "src/utils/ArduboyG.h"
#include "src/utils/Constants.h"
#include "src/utils/Enums.h"
#include "fxdata/fxdata.h"
#include "src/entities/Entities.h"
#include "src/utils/SpritesU.hpp"


uint8_t getJustPressedButtons() {

    a.pollButtons();
    return a.justPressedButtons();

}

uint8_t getPressedButtons() {

    return a.pressedButtons();

}

template<typename T> T absT(const T & v) {

	return (v < 0) ? -v : v;

}


void saveCookie() {

    FX::saveGameState(cookie);

}

bool collide(Rect rect1, Rect rect2) {

   return !(rect2.x                >= rect1.x + rect1.width  ||
            rect2.x + rect2.width  <= rect1.x                ||
            rect2.y                >= rect1.y + rect1.height ||
            rect2.y + rect2.height <= rect1.y);

}


bool collide(Point point, Rect rect) {

   return ((point.x >= rect.x) && (point.x < rect.x + rect.width) &&
           (point.y >= rect.y) && (point.y < rect.y + rect.height));

 }

inline void debug_break() {

    asm volatile("break\n");

}

