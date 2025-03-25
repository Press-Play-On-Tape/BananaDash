constexpr const static uint8_t UPLOAD_DELAY = 16;


// ----------------------------------------------------------------------------
//  Initialise state ..
//
void titleScreen_Activate() {

    // gameStats.resetGame();

    world.setGameState(GameState::Title);

}


// ----------------------------------------------------------------------------
//  Handle state updates ..
//
void titleScreen_Update() {

    const uint8_t justPressed = getJustPressedButtons();
    const uint8_t justpressedPressed = getPressedButtons();


    // Restart ?

    // if (pressed & DOWN_BUTTON) {

    //     if (titleScreenVars.restart < UPLOAD_DELAY) {
    //         titleScreenVars.restart++;
    //     }
    //     else {
    //         arduboy.exitToBootloader();
    //     }

    // }
    // else {
    //     titleScreenVars.restart = 0;
    // }


    // Handle other input ..


    if (justPressed & A_BUTTON || justPressed & B_BUTTON) {
        world.setGameState(GameState::PlayGame_Init); 
    }


}


// ----------------------------------------------------------------------------
//  Render the state ..
//
void titleScreen_Render() {

    SpritesU::drawOverwriteFX(0, 0, Images::Title, currentPlane);


}
