constexpr const static uint8_t UPLOAD_DELAY = 16;


// ----------------------------------------------------------------------------
//  Initialise state ..
//
void titleScreen_Activate() {

    // gameStats.resetGame();

    world.setGameState(GameState::Title_Start);

}


// ----------------------------------------------------------------------------
//  Handle state updates ..
//
void titleScreen_Update() {

    const uint8_t justPressed = getJustPressedButtons();
    const uint8_t pressed = getPressedButtons();



    // Handle other input ..

    if (justPressed & UP_BUTTON && world.getGameState() != GameState::Title_Play_Game) {
    
        world.decGameState();

    }

    if (justPressed & DOWN_BUTTON  && world.getGameState() != GameState::Title_Highs) {
    
        world.incGameState();

    }
   

    if (justPressed & A_BUTTON || justPressed & B_BUTTON) {

        switch (world.getGameState()) {
        
            case GameState::Title_Play_Game:
                world.setGameState(GameState::PlayGame_Init); 
                break;
            
        }

    }


}


// ----------------------------------------------------------------------------
//  Render the state ..
//
void titleScreen_Render() {

    uint8_t idx = static_cast<uint8_t>(world.getGameState()) - static_cast<uint8_t>(GameState::Title_Play_Game);
    SpritesU::drawOverwriteFX(0, 0, Images::Title, (idx * 3) + currentPlane);


}
