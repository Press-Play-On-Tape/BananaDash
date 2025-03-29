#include <Arduboy2.h>


uint16_t playGame_PopEntry(Player &player) {

    uint16_t stance = player.pop();

    player.setStance(static_cast<Stance>(stance));

    StanceDetails stanceDetails;

    FX::seekData(Constants::StanceDetails + (static_cast<uint16_t>(stance) * 4));
    FX::readObject(stanceDetails);
    FX::readEnd();

    player.setY(player.getY() + stanceDetails.stanceY);

    if (world.incMiddleground(stanceDetails.middleground)) {
        world.incForeground(stanceDetails.foreground);
        world.incBackground(stanceDetails.background);
    }

    
    return stance;

}

uint8_t getStanceImg(Stance stance) {

    FX::seekData(Constants::StanceImgIdx + static_cast<uint16_t>(stance));
    uint8_t stanceImg = FX::readPendingUInt8();
    FX::readEnd();

    return stanceImg;

}



// ----------------------------------------------------------------------------
//  Initialise state ..
//
void playGame_Init() {

    world.getPlayer().reset();
    world.setGameState(GameState::PlayGame);

    for (uint8_t i = 0; i < 8; i++) {
        world.setPalm(i, FX::readIndexedUInt16(Constants::Palm_X, i));
    }

}

// ----------------------------------------------------------------------------
//    Handle state updates .. 
//
void playGame_Update() { 


    const uint8_t justPressed = getJustPressedButtons();
    const uint8_t pressed = getPressedButtons();
    Player &player = world.getPlayer();

    world.incFrameCount();
        
    if (world.getFrameCount() % 4 == 0) {

        if (player.isEmpty()) {

            switch (world.getGameState()) {

                case GameState::PlayGame:

                    if (pressed & A_BUTTON) {

                        switch (player.getStance()) {

                            case Stance::Player_Idle_RH:
                                player.pushSequence(Stance::Player_Standing_Jump_RH_00, Stance::Player_Standing_Jump_RH_07);
                                break;

                            case Stance::Player_Idle_LH:
                                player.pushSequence(Stance::Player_Standing_Jump_LH_00, Stance::Player_Standing_Jump_LH_07);
                                break;

                            case Stance::Player_Walk_RH_03:
                                player.pushSequence(Stance::Player_Running_Jump_RH_00, Stance::Player_Running_Jump_RH_07);
                                break;

                            case Stance::Player_Walk_LH_03:
                                player.pushSequence(Stance::Player_Running_Jump_LH_00, Stance::Player_Running_Jump_LH_07);
                                break;

                        }

                    }

                    if (pressed & UP_BUTTON) {

                        player.pushSequence(Stance::Player_Cliimbing_Vine_Up_1L_RH_00, Stance::Player_Cliimbing_Vine_Up_1L_RH_03);
                    
                    }

                    if (pressed & DOWN_BUTTON) {

                        player.pushSequence(Stance::Player_Cliimbing_Vine_Down_1L_RH_00, Stance::Player_Cliimbing_Vine_Down_1L_RH_03);
                    
                    }

                    if (pressed & RIGHT_BUTTON) {

                        if (player.getDirection() == Direction::Right) {
                            player.pushSequence(Stance::Player_Walk_RH_00, Stance::Player_Walk_RH_03);
                        }
                        else {
                            player.setStance(Stance::Player_Idle_RH);
                        }

                    }

                    if (pressed & LEFT_BUTTON) {

                        if (player.getDirection() == Direction::Left) {
                            player.pushSequence(Stance::Player_Walk_LH_00, Stance::Player_Walk_LH_03);
                        }
                        else {
                            player.setStance(Stance::Player_Idle_LH);
                        }

                    }

                    break;

            }

        }
        else {

            if (pressed & A_BUTTON && player.getStance() == Stance::Player_Walk_RH_01) {
                player.pushSequence(Stance::Player_Running_Jump_RH_00, Stance::Player_Running_Jump_RH_07, true);
            }

        }



        Point offset;
        uint16_t stance = player.getStance();

        if (!player.isEmpty() || player.hasStagedSequence()) {

            stance = playGame_PopEntry(player);

        }
        else {
        
            // Nothing in the stack.  Assume idle position?

            switch (player.getStance()) {

                case Stance::Player_Walk_RH_01:
                case Stance::Player_Walk_RH_03:
                case Stance::Player_Standing_Jump_RH_07:
                    player.setStance(Stance::Player_Idle_RH);
                    break;

                case Stance::Player_Walk_LH_01:
                case Stance::Player_Walk_LH_03:
                case Stance::Player_Standing_Jump_LH_07:
                    player.setStance(Stance::Player_Idle_LH);
                    break;

            }
        }




        // Has the player collided with an item?

        // for (uint8_t i = 0; i < Constants::ItemCount_Level; i++) {
        
        //     Rect playerRect = { 59, player.getY_RelativeToGround(), 10, 16 };
        //     Item &item = world.getItem(i);

            
        //     // Can we skip this one?

        //     if (item.getItemType() == ItemType::MysteryCrate && item.getFrame() == 8) continue;
        //     if (item.getItemType() == ItemType::MysteryCrate) { //SJH revet to above/
        //         if (item.getFrame() == 8) continue;
        //     }

        // }



        // If a sequence has been staged then commit it now (and adjust the players position etc ..

        if (player.commitSequence()) {

            stance = playGame_PopEntry(player);

        }


        // Handle falling and other special actions ..

        // switch (static_cast<Stance>(stance)) {

        //     // case Stance::Man_Walk_FallLand_LH_03_Puff:
        //     // case Stance::Man_Walk_FallLand_RH_03_Puff:
        //     //     launchPuffLand(player);
        //     //     break;
        // }


        // world.updateEnemies(a);
        player.update();


    }
    

}


void playGame(ArduboyGBase_Config<ABG_Mode::L4_Triplane> &a) {

    if (a.needsUpdate()) playGame_Update();

    Player &player = world.getPlayer();
    uint8_t currentPlane = a.currentPlane();
    
    uint8_t stanceImg = getStanceImg(player.getStance());
    player.setImageIdx(stanceImg);

    SpritesU::drawOverwriteFX((world.getBackground() / 2) + 128, 0, 128, 64, Images::Background, currentPlane);
    SpritesU::drawOverwriteFX((world.getBackground() / 2), 0, 128, 64, Images::Background, currentPlane);
    // SpritesU::drawPlusMaskFX(0, 0, Images::Foreground, currentPlane);


    // ____________________________________________________________________________________________________________________________________________________________________________________
    //
    // Render palms ..

    for (uint8_t i = 4; i < 8; i++) {    

        uint24_t palmIdx = FX::readIndexedUInt24(Images::PalmImages, i);
        SpritesU::drawPlusMaskFX(world.getPalm(i), 15, palmIdx, currentPlane);

    }


    for (uint8_t i = 0; i < 4; i++) {    

        uint24_t palmIdx = FX::readIndexedUInt24(Images::PalmImages, i);
        SpritesU::drawPlusMaskFX(world.getPalm(i), 14, palmIdx, currentPlane);

    }

    for (uint8_t i = 0; i < 12; i++) {    

        uint8_t levelIdx = FX::readIndexedUInt8(Level::Level, i);

        switch (levelIdx) {
        
            case 0 ... 19:
                SpritesU::drawPlusMaskFX((i * 16) + world.getForeground(), 10, 16, 48, Images::LowerOnly, (levelIdx * 3) + currentPlane);
                break;

            case 20 ... 39:
                SpritesU::drawPlusMaskFX((i * 16) + world.getForeground(), 10, 16, 48, Images::Both, ((levelIdx - 20) * 3) + currentPlane);
                break;

            case 40 ... 59:
                SpritesU::drawPlusMaskFX((i * 16) + world.getForeground(), 10, 16, 48, Images::UpperOnly, ((levelIdx - 40) * 3) + currentPlane);
                break;

        }

    }




    SpritesU::drawPlusMaskFX(12, player.getY(), 16, 16, Images::Player, (player.getImageIdx() * 3) + currentPlane);



}

