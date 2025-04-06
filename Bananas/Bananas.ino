#define ABG_IMPLEMENTATION
#define ABG_TIMER1
#define ABG_SYNC_PARK_ROW
#define SPRITESU_IMPLEMENTATION

#include <ArduboyFX.h>  
#include "src/utils/ArduboyG.h"
// #include "src/utils/Constants.h"
#include "src/utils/Enums.h"
#include "fxdata/fxdata.h"
#include "fxdata/images/Images.h"
#include "src/images/Images.h"
#include <ArduboyFX.h>  
#include "src/entities/Entities.h"
#include "src/utils/Stack.h"

#define SPRITESU_OVERWRITE
#define SPRITESU_PLUSMASK
#define SPRITESU_RECT
#define SPRITESU_FX

#include "src/utils/SpritesU.hpp"

extern ArduboyGBase_Config<ABG_Mode::L4_Triplane> a;
decltype(a) a;

#define SYNTHU_IMPLEMENTATION
#define SYNTHU_NUM_CHANNELS 2
#define SYNTHU_UPDATE_EVERY_N_FRAMES 3
#define SYNTHU_ENABLE_SFX 1
#define SYNTHU_FX_READDATABYTES_FUNC FX::readDataBytes
#include "src/utils/SynthU.hpp"
#define ABG_TIMER1

// #ifndef DEBUG
// ARDUBOY_NO_USB
// #endif

Cookie cookie;
World &world = cookie.world;
uint8_t currentPlane;
uint8_t titleCounter = 0;

Rect gPlayerRect;
Rect gEnemyRect;

void setup(void) {

    a.boot();
    a.startGray();
    
    FX::begin(FX_DATA_PAGE, FX_SAVE_PAGE);

}

void loop(void) {

    FX::enableOLED();
    a.waitForNextPlane(DARK_GRAY);
    FX::disableOLED();

    currentPlane = a.currentPlane();


	switch (world.getGameState()) {

		case GameState::SplashScreen_Start ... GameState::SplashScreen_End:
			splashScreen(a);
			break;

		case GameState::Title_Init:
			titleScreen_Activate();
			[[fallthrough]];

		case GameState::Title_Start ... GameState::Title_End:
			titleScreen_Update();
			titleScreen_Render();
			// arduboy.displayWithBackground(Background::Black);
			break;

		case GameState::PlayGame_Init:
			playGame_Init();
			[[fallthrough]];

		case GameState::PlayGame:
			playGame(a);
			break;

		default: break;

	}

}
