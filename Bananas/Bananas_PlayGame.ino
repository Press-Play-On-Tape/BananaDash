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
    world.setTime(99 * 16);
    world.setBananas(0);

    for (uint8_t i = 0; i < 8; i++) {
        world.setPalm(i, FX::readIndexedUInt16(Constants::Palm_X, i));
    }

    world.getItem(0).setItemType(ItemType::Puff);
    world.getItem(0).setY(16);
    world.getItem(0).setX(-800);

    world.getItem(1).setItemType(ItemType::Banana);
    world.getItem(1).setY(15);
    world.getItem(1).setX(80);

    world.getEnemy(0).setEntityType(EntityType::Barrel);
    world.getEnemy(0).setY(-6);
    world.getEnemy(0).setX(80 - 16);
    world.getEnemy(0).setStance(Stance::Enemy_Fall_1L_00);
    world.getEnemy(0).pushSequence(Stance::Enemy_Fall_1L_00, Stance::Enemy_Fall_1L_06);
    world.getEnemy(0).setCounter(20);


    world.setForeground(-64);

}

// ----------------------------------------------------------------------------
//    Handle state updates .. 
//
void playGame_Update() { 


    const uint8_t justPressed = getJustPressedButtons();
    const uint8_t pressed = getPressedButtons();
    Player &player = world.getPlayer();

    world.incFrameCount();

    uint8_t tile = getTile(0);
    uint8_t tileL = getTile(-1);
    uint8_t tileR = getTile(1);

    if (world.getFrameCount() % 3 == 0) {

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

                            case Stance::Player_Walk_RH_01:
                            case Stance::Player_Walk_RH_03:
                                player.pushSequence(Stance::Player_Running_Jump_RH_00, Stance::Player_Running_Jump_RH_07);
                                break;

                            case Stance::Player_Walk_LH_01:
                            case Stance::Player_Walk_LH_03:
                                player.pushSequence(Stance::Player_Running_Jump_LH_00, Stance::Player_Running_Jump_LH_07);
                                break;

                        }

                    }

                    else if (pressed & UP_BUTTON && isAlignedWithTile()) {

                        if (world.canClimbUp(tile)) {
                            if (player.getDirection() == Direction::Right) {
                                player.pushSequence(Stance::Player_Climbing_Vine_Up_RH_00, Stance::Player_Climbing_Vine_Up_RH_03);
                            }
                            else {
                                player.pushSequence(Stance::Player_Climbing_Vine_Up_LH_00, Stance::Player_Climbing_Vine_Up_LH_03);
                            }
                        }
                    
                    }

                    else if (pressed & DOWN_BUTTON && isAlignedWithTile()) {

                        if (world.canClimbDown(tile)) {
                            if (player.getDirection() == Direction::Right) {
                                player.pushSequence(Stance::Player_Climbing_Vine_Down_RH_00, Stance::Player_Climbing_Vine_Down_RH_03);
                            }
                            else {
                                player.pushSequence(Stance::Player_Climbing_Vine_Down_LH_00, Stance::Player_Climbing_Vine_Down_LH_03);
                            }
                        }
                    
                    }


                    else if (pressed & RIGHT_BUTTON) {

                        if (player.getDirection() == Direction::Right) {

                            if (world.canWalkRight(EntityType::Player, world.getForeground(), player.getY(), tile, tileR)) {

                                if (player.getStance() == Stance::Player_Walk_RH_01) {
                                    player.pushSequence(Stance::Player_Walk_RH_02, Stance::Player_Walk_RH_03);
                                }
                                else {
                                    player.pushSequence(Stance::Player_Walk_RH_00, Stance::Player_Walk_RH_01);
                                }

                            }
                            else if (world.canFallRight(EntityType::Player, player.getY(), tile, tileR)) {

                                if (player.getStance() == Stance::Player_Walk_RH_01) {
                                    player.pushSequence(Stance::Player_Falling_1L_A_RH_00, Stance::Player_Falling_1L_A_RH_07);
                                }
                                else {
                                    player.pushSequence(Stance::Player_Falling_1L_B_RH_00, Stance::Player_Falling_1L_B_RH_07);
                                }

                            }    

                        }
                        else {

                            if (world.canGoIdle(tile)) {
                                player.setStance(Stance::Player_Idle_RH);
                            }

                        }

                    }

                    else if (pressed & LEFT_BUTTON) {

                        if (player.getDirection() == Direction::Left) {

                            if (world.canWalkLeft(EntityType::Player, world.getForeground(), player.getY(), tileL, tile)) {

                                if (player.getStance() == Stance::Player_Walk_LH_01) {
                                    player.pushSequence(Stance::Player_Walk_LH_02, Stance::Player_Walk_LH_03);
                                }
                                else {
                                    player.pushSequence(Stance::Player_Walk_LH_00, Stance::Player_Walk_LH_01);
                                }

                            }
                            else if (world.canFallLeft(EntityType::Player, player.getY(), tileL, tile)) {

                                if (player.getStance() == Stance::Player_Walk_LH_01) {
                                    player.pushSequence(Stance::Player_Falling_1L_A_LH_00, Stance::Player_Falling_1L_A_LH_07);
                                }
                                else {
                                    player.pushSequence(Stance::Player_Falling_1L_B_LH_00, Stance::Player_Falling_1L_B_LH_07);
                                }

                            }                                

                        }
                        else {

                            if (world.canGoIdle(tile)) {
                                player.setStance(Stance::Player_Idle_LH);
                            }

                        }

                    }

                    break;

            }

        }
        else {

            if (pressed & A_BUTTON && (player.getStance() == Stance::Player_Walk_RH_01 || player.getStance() == Stance::Player_Walk_RH_03)) {
                player.pushSequence(Stance::Player_Running_Jump_RH_00, Stance::Player_Running_Jump_RH_07, true);
            }

            if (pressed & A_BUTTON && (player.getStance() == Stance::Player_Walk_LH_01 || player.getStance() == Stance::Player_Walk_LH_03)) {
                player.pushSequence(Stance::Player_Running_Jump_LH_00, Stance::Player_Running_Jump_LH_07, true);
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
                case Stance::Player_Running_Jump_RH_07:
                    player.setStance(Stance::Player_Idle_RH);
                    player.setVelocityX(0);
                    break;

                case Stance::Player_Climbing_Vine_Up_RH_03:
                    if (!world.canClimbUp(tile)) {
                        player.setStance(Stance::Player_Idle_RH);
                        player.setVelocityX(0);
                    }
                    break;

                case Stance::Player_Climbing_Vine_Down_RH_03:
                    if (!world.canClimbDown(tile)) {
                        player.setStance(Stance::Player_Idle_RH);
                        player.setVelocityX(0);
                    }
                    break;

                case Stance::Player_Walk_LH_01:
                case Stance::Player_Walk_LH_03:
                case Stance::Player_Standing_Jump_LH_07:
                case Stance::Player_Running_Jump_LH_07:
                case Stance::Player_Falling_1L_A_LH_07:
                case Stance::Player_Falling_1L_B_LH_07:
                    player.setStance(Stance::Player_Idle_LH);
                    player.setVelocityX(0);
                    break;

                case Stance::Player_Climbing_Vine_Up_LH_03:
                    if (!world.canClimbUp(tile)) {
                        player.setStance(Stance::Player_Idle_LH);
                        player.setVelocityX(0);
                    }
                    break;

                case Stance::Player_Climbing_Vine_Down_LH_03:
                    if (!world.canClimbDown(tile)) {
                        player.setStance(Stance::Player_Idle_LH);
                        player.setVelocityX(0);
                    }
                    break;

            }

        }




        // Has the player collided with an item?

        for (uint8_t i = 0; i < Constants::Item_Count; i++) {
        
            Rect playerRect = { 57 + world.getXOffset(), player.getY() + 1, 10, 12 };
            Item &item = world.getItem(i);

            
            // Can we skip this one?

            switch (item.getItemType()) {
            
                case ItemType::Banana:
                    {
                        Rect bananaRect = { 55 + item.getX() + world.getForeground() + world.getXOffset(), item.getY(), 10 , 10};

                        if (item.getCounter() == 0 && collide(playerRect, bananaRect)) {
                        // if (collide(playerRect, bananaRect)) {
                            item.setCounter(5);
                            launchPuff(item);
                            world.setTime(world.getTime() + (5*16));
                            world.setBananas(world.getBananas() + 1);
                        }

gPlayerRect = playerRect;
gBananaRect = bananaRect;

                    }
                    break;

            }

        }



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



        playGame_HandleEnemies(a);








        world.decTime();


    }
    
    world.update();

}


void playGame(ArduboyGBase_Config<ABG_Mode::L4_Triplane> &a) {

    if (a.needsUpdate()) playGame_Update();

    Player &player = world.getPlayer();
    uint8_t currentPlane = a.currentPlane();
    
    uint8_t stanceImg = getStanceImg(player.getStance());
    player.setImageIdx(stanceImg);

    SpritesU::drawOverwriteFX((world.getBackground() / 2) - 128 + world.getXOffset(), 0, 128, 32, Images::Background, currentPlane);
    SpritesU::drawOverwriteFX((world.getBackground() / 2) + world.getXOffset(), 0, 128, 32, Images::Background, currentPlane);
    SpritesU::drawOverwriteFX((world.getBackground() / 2) + 128 + world.getXOffset(), 0, 128, 32, Images::Background, currentPlane);



    // ____________________________________________________________________________________________________________________________________________________________________________________
    //
    // Render palms ..

    for (uint8_t i = 4; i < 8; i++) {    

        uint24_t palmIdx = FX::readIndexedUInt24(Images::PalmImages, i);
        SpritesU::drawPlusMaskFX(world.getPalm(i) + world.getXOffset(), 15, palmIdx, currentPlane);

    }


    for (uint8_t i = 0; i < 4; i++) {    

        uint24_t palmIdx = FX::readIndexedUInt24(Images::PalmImages, i);
        SpritesU::drawPlusMaskFX(world.getPalm(i) + world.getXOffset(), 14, palmIdx, currentPlane);

    }

    for (uint8_t i = 0; i < 19; i++) {    

        uint8_t levelIdx = FX::readIndexedUInt8(Level::Level, i);

        switch (levelIdx) {
        
            case 0 ... 19:
                SpritesU::drawPlusMaskFX(55 + (i * 16) + world.getForeground() + world.getXOffset(), 34, 16, 24, Images::LowerOnly, (levelIdx * 3) + currentPlane);
                break;

            case 20 ... 39:
                SpritesU::drawPlusMaskFX(55 + (i * 16) + world.getForeground() + world.getXOffset(), 18, 16, 40, Images::Both, ((levelIdx - 20) * 3) + currentPlane);
                break;

            case 40 ... 59:
                SpritesU::drawPlusMaskFX(55 + (i * 16) + world.getForeground() + world.getXOffset(), 10, 16, 48, Images::UpperOnly, ((levelIdx - 40) * 3) + currentPlane);
                break;

        }

        // a.drawLine(55 + (i * 16) + world.getForeground() + world.getXOffset(), 0, 55 + (i * 16) + world.getForeground() + world.getXOffset(), 128, WHITE);

    }

    for (uint8_t i = 0; i < Constants::Item_Count; i++) {    

        Item &item = world.getItem(i);

        if (item.getItemType() == ItemType::Banana) {

            SpritesU::drawPlusMaskFX(55 + item.getX() + world.getForeground() + world.getXOffset(), item.getY(), Images::Banana, currentPlane);
        }

    }


    for (uint8_t i = 0; i < Constants::Enemy_Count; i++) {    

        Enemy &enemy = world.getEnemy(i);

        if (enemy.getEntityType() == EntityType::Barrel) {

            uint24_t imageIdx = getStanceImg(enemy.getStance());
            SpritesU::drawPlusMaskFX(55 + enemy.getX() + world.getForeground() + world.getXOffset(), enemy.getY(), 16, 16, Images::Barrel, (imageIdx * 3) + currentPlane);

        }

    }

    SpritesU::drawPlusMaskFX(54 + world.getXOffset(), player.getY(), 16, 16, Images::Player, (player.getImageIdx() * 3) + currentPlane);

    SpritesU::drawPlusMaskFX(1, 1, 35, 8, Images::HUD_Banana, (world.getBananas() * 3) + currentPlane);
    SpritesU::drawPlusMaskFX(101, 1, 26, 8, Images::HUD_Time, ((world.getTime() / 16) * 3) + currentPlane);

    // a.drawRect(gPlayerRect.x, gPlayerRect.y, gPlayerRect.width, gPlayerRect.height);
    // a.drawRect(gBananaRect.x, gBananaRect.y, gBananaRect.width, gBananaRect.height);


    Item &item = world.getItem(0);

    if (item.getFrame() < Constants::Puff_Max) {

        uint8_t frame = item.getFrame() / 8;
        SpritesU::drawPlusMaskFX(55 + item.getX() + world.getForeground() + world.getXOffset(), item.getY(), Images::Puff, (frame * 3) +  currentPlane);

    }

}

