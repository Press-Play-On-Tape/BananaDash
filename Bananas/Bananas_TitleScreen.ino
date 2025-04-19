constexpr const static uint8_t UPLOAD_DELAY = 16;


void titleScreen_Init() {

    // gameStats.resetGame();

    world.setGameState(GameState::Title_Start);


}

void title_SaveSoundSettings() {
    
    soundSettings.setSounds(!soundSettings.getSounds());
    
    if (soundSettings.getSounds()) {
        playMusic();
    }
    else {
        SynthU::stop();
    }

    saveCookie();

}


void titleScreen_Update() {

    const uint8_t justPressed = getJustPressedButtons();
    const uint8_t pressed = getPressedButtons();



    // Handle other input ..

    if (justPressed & UP_BUTTON && world.getGameState() != GameState::Title_Play_Game) {
    
        world.decGameState();

    }

    if (justPressed & DOWN_BUTTON  && world.getGameState() != GameState::Title_Sounds) {
    
        world.incGameState();

    }
   

    if (justPressed & A_BUTTON || justPressed & B_BUTTON) {

        switch (world.getGameState()) {
        
            case GameState::Title_Play_Game:
                world.setGameState(GameState::PlayGame_Init); 
                break;
        
            case GameState::Title_Highs:
                highScore_Entry = 5;
                world.setGameState(GameState::HighScore_View); 
                break;
        
            case GameState::Title_Sounds:
                title_SaveSoundSettings();
                break;
            
        }

    }


}


void titleScreen(ArduboyGBase_Config<ABG_Mode::L4_Triplane> &a) {

    if (a.needsUpdate()) { titleScreen_Update(); }

    titleScreen_Render();

}


void titleScreen_Render() {

    uint8_t idx = static_cast<uint8_t>(world.getGameState()) - static_cast<uint8_t>(GameState::Title_Play_Game);

    if (!soundSettings.getSounds()) idx = idx + 3;

    SpritesU::drawOverwriteFX(0, 0, Images::Title, (idx * 3) + currentPlane);


}
