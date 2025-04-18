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

    gameOverCount = -1;
    timesUpCount = -1;
    
    for (uint8_t i = 0; i < Constants::Item_Count; i++) {
        world.getItem(i).setItemType(ItemType::None);
    }
    
    for (uint8_t i = 0; i < Constants::Enemy_Count; i++) {
        world.getEnemy(i).clear();
    }

    for (uint8_t i = 0; i < 8; i++) {
        world.setTree(i, FX::readIndexedUInt16(Constants::Tree_X, i));
    }




    world.getItem(0).setItemType(ItemType::Puff);
    world.getItem(0).setY(16);
    world.getItem(0).setX(-800);

    launchBanana(world.getItem(1));
    launchBanana(world.getItem(2));
    launchBanana(world.getItem(3));
    launchBanana(world.getItem(4));
    launchBanana(world.getItem(5));
    launchBanana(world.getItem(6));

    launchHeart(world.getItem(10));
    launchHeart(world.getItem(11));

    world.getItem(7).setItemType(ItemType::Fire);
    world.getItem(7).setY(42);
    world.getItem(7).setX(208);

    world.getItem(8).setItemType(ItemType::Fire);
    world.getItem(8).setY(42);
    world.getItem(8).setX(1008);

    world.getItem(9).setItemType(ItemType::Fire);
    world.getItem(9).setY(42);
    world.getItem(9).setX(1280);

    // world.getItem(1).setItemType(ItemType::Banana);
    // world.getItem(1).setY(15);
    // world.getItem(1).setX(80);


    // world.getItem(1).setItemType(ItemType::Banana);
    // world.getItem(1).setY(15);
    // world.getItem(1).setX(80);


    launchBarrel(world.getEnemy(0));
    launchBarrel(world.getEnemy(1));
    launchBarrel(world.getEnemy(2));
    launchBarrel(world.getEnemy(3));

    uint8_t i = 4;

    world.getEnemy(i).setEntityType(EntityType::Spider);
    world.getEnemy(i).setY(46);
    world.getEnemy(i).setX(160 - 16);
    world.getEnemy(i).setStance(Stance::Enemy_Spider_L1_00);
    world.getEnemy(i).pushSequence(Stance::Enemy_Spider_L1_00, Stance::Enemy_Spider_L1_15);
    world.getEnemy(i).setCounter(0);

    i++;
    world.getEnemy(i).setEntityType(EntityType::Spider);
    world.getEnemy(i).setY(46);
    world.getEnemy(i).setX(500 - 16);
    world.getEnemy(i).setStance(Stance::Enemy_Spider_L1_00);
    world.getEnemy(i).pushSequence(Stance::Enemy_Spider_L1_00, Stance::Enemy_Spider_L1_15);
    world.getEnemy(i).setCounter(0);

    i++;
    world.getEnemy(i).setEntityType(EntityType::Bird);
    world.getEnemy(i).setY(28);
    world.getEnemy(i).setX(160 - 16);
    world.getEnemy(i).setStance(Stance::Enemy_Flying_LH_00);
    world.getEnemy(i).pushSequence(Stance::Enemy_Flying_LH_00, Stance::Enemy_Flying_LH_19);
    world.getEnemy(i).setCounter(0);

    i++;
    world.getEnemy(i).setEntityType(EntityType::Bird);
    world.getEnemy(i).setY(10);
    world.getEnemy(i).setX(16);
    world.getEnemy(i).setStance(Stance::Enemy_Flying_RH_00);
    world.getEnemy(i).pushSequence(Stance::Enemy_Flying_RH_00, Stance::Enemy_Flying_RH_19);
    world.getEnemy(i).setCounter(0);


    updateDirectionCounter();
    world.setForeground(-64);

}

void updateDirectionCounter() {

    directionCounter = 340;
    directionCounter_Left = 0;
    directionCounter_Right = 0;
    
    for (uint8_t i = 0; i < Constants::Item_Count; i++) {
    
        Item &item = world.getItem(i);

        if (item.getItemType() == ItemType::Banana) {

            if (item.getX() < -world.getForeground()) {
                directionCounter_Left++;
            }
            else {
                directionCounter_Right++;
            }

        }
    
    }

}

// ----------------------------------------------------------------------------
//    Handle state updates .. 
//
void playGame_Update() { 

    const uint8_t justPressed = getJustPressedButtons();
    const uint8_t pressed = getPressedButtons();
    Player &player = world.getPlayer();

    frameCount = frameCount + 1;

    uint8_t tileL2 = getTile(-2);
    uint8_t tileL = getTile(-1);
    uint8_t tile = getTile(0);
    uint8_t tileR = getTile(1);
    uint8_t tileR2 = getTile(2);

    if (frameCount % 3 == 0) {

        if (player.isEmpty()) {

            switch (world.getGameState()) {

                case GameState::PlayGame_GameOver:
                case GameState::PlayGame_TimesUp:

                    if (pressed & A_BUTTON && timesUpCount > 30) {

                        world.setGameState(GameState::HighScore_Init);

                    }

                    break;

                case GameState::PlayGame:

                    if (pressed & B_BUTTON) {

                        updateDirectionCounter();
                        healthCounter = Constants::Health_Counter_Max / 2;
                        healthFlash = false;

                    }

                    if (pressed & A_BUTTON) {

                        switch (player.getStance()) {

                            case Stance::Player_Idle_RH:
                                player.pushSequence(Stance::Player_Standing_Jump_RH_00, Stance::Player_Standing_Jump_RH_11);
                                break;

                            case Stance::Player_Idle_LH:
                                player.pushSequence(Stance::Player_Standing_Jump_LH_00, Stance::Player_Standing_Jump_LH_11);
                                break;

                            case Stance::Player_Walk_RH_01:
                            case Stance::Player_Walk_RH_03:

                                if (world.canJumpRight(EntityType::Player, player.getY(), tile, tileR, tileR2)) {

                                    player.pushSequence(Stance::Player_Running_Jump_RH_00, Stance::Player_Running_Jump_RH_11);

                                }
                                break;

                            case Stance::Player_Walk_LH_01:
                            case Stance::Player_Walk_LH_03:

                                if (world.canJumpLeft(EntityType::Player, player.getY(), tileL2, tileL, tile)) {

                                    player.pushSequence(Stance::Player_Running_Jump_LH_00, Stance::Player_Running_Jump_LH_11);

                                }
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

                    else if (pressed & DOWN_BUTTON) {

                        if (isAlignedWithTile() && world.canClimbDown(tile)) {

                            if (player.getDirection() == Direction::Right) {
                                player.pushSequence(Stance::Player_Climbing_Vine_Down_RH_00, Stance::Player_Climbing_Vine_Down_RH_03);
                            }
                            else {
                                player.pushSequence(Stance::Player_Climbing_Vine_Down_LH_00, Stance::Player_Climbing_Vine_Down_LH_03);
                            }

                        }
                        else {

                            if (player.getDirection() == Direction::Right) {

                                if (player.getStance() != Stance::Player_Idle_RH && player.getStance() != Stance::Player_Lying_RH) {
                                    player.push(Stance::Player_Idle_RH);
                                }
                                else {
                                    player.push(Stance::Player_Lying_RH);
                                }

                            }
                            else {

                                if (player.getStance() != Stance::Player_Idle_LH && player.getStance() != Stance::Player_Lying_LH) {
                                    player.push(Stance::Player_Idle_LH);
                                }
                                else {
                                    player.push(Stance::Player_Lying_LH);
                                }

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
                            else if (world.canFallRight_TwoLevels(EntityType::Player, player.getY(), tile, tileR)) {

                                if (player.getStance() == Stance::Player_Walk_RH_01) {
                                    player.pushSequence(Stance::Player_Falling_2L_A_RH_00, Stance::Player_Falling_2L_A_RH_11);
                                }
                                else {
                                    player.pushSequence(Stance::Player_Falling_2L_B_RH_00, Stance::Player_Falling_2L_B_RH_11);
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
                            else if (world.canFallLeft_TwoLevels(EntityType::Player, player.getY(), tileL, tile)) {

                                if (player.getStance() == Stance::Player_Walk_LH_01) {
                                    player.pushSequence(Stance::Player_Falling_2L_A_LH_00, Stance::Player_Falling_2L_A_LH_11);
                                }
                                else {
                                    player.pushSequence(Stance::Player_Falling_2L_B_LH_00, Stance::Player_Falling_2L_B_LH_11);
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
                player.pushSequence(Stance::Player_Running_Jump_RH_00, Stance::Player_Running_Jump_RH_11, true);
            }

            if (pressed & A_BUTTON && (player.getStance() == Stance::Player_Walk_LH_01 || player.getStance() == Stance::Player_Walk_LH_03)) {
                player.pushSequence(Stance::Player_Running_Jump_LH_00, Stance::Player_Running_Jump_LH_11, true);
            }

        }



        Point offset;
        uint16_t stance = player.getStance();

        if (!player.isEmpty()) {

            stance = playGame_PopEntry(player);


            if (player.isEmpty()) {

                switch (player.getStance()) {

                    case Stance::Player_Running_Jump_RH_11:

                        if (world.canFallRight_Down_2Levels(EntityType::Player, player.getY(), tile, tileR)) {
    // Serial.println("canFallRight_Down_2Levels");
                            player.pushSequence(Stance::Player_Falling_2L_C_RH_00, Stance::Player_Falling_2L_C_RH_07);

                        }
                        else if (world.canFallRight_Down_1Level(EntityType::Player, world.getForeground(), player.getY(), tile, tileR)) {
    // Serial.println("canFallRight_Down_1Level");
                            player.pushSequence(Stance::Player_Falling_2L_C_RH_04, Stance::Player_Falling_2L_C_RH_07);

                        }

                        break;

                    case Stance::Player_Running_Jump_LH_11:
// Serial.println("Test");
                        if (world.canFallLeft_Down_2Levels(EntityType::Player, player.getY(), tileL, tile)) {
    // Serial.println("canFallLeft_Down_2Levels");
                            player.pushSequence(Stance::Player_Falling_2L_C_LH_00, Stance::Player_Falling_2L_C_LH_07);

                        }
                        else if (world.canFallLeft_Down_1Level(EntityType::Player, world.getForeground(), player.getY(), tileL, tile)) {
    // Serial.println("canFallLeft_Down_1Level");
                            player.pushSequence(Stance::Player_Falling_2L_C_LH_04, Stance::Player_Falling_2L_C_LH_07);

                        }

                        break;                        

                }

            }

        }
        else {
        
            // Nothing in the stack.  Assume idle position?

            switch (player.getStance()) {

                case Stance::Player_Walk_RH_01:
                case Stance::Player_Walk_RH_03:
                case Stance::Player_Standing_Jump_RH_11:
                case Stance::Player_Running_Jump_RH_11:
                case Stance::Player_Falling_1L_A_RH_07:
                case Stance::Player_Falling_1L_B_RH_07:                    
                case Stance::Player_Falling_2L_A_RH_11:
                case Stance::Player_Falling_2L_B_RH_11:
                case Stance::Player_Falling_2L_C_RH_07:

                    // if (world.canFall_2Levels(EntityType::Player, player.getY(), tile, tileR)) {

                    //     player.pushSequence(Stance::Player_Falling_2L_C_RH_00, Stance::Player_Falling_2L_C_RH_07);

                    // }
                    // else {

                        player.setStance(Stance::Player_Idle_RH);
                        player.setVelocityX(0);

                    // }
                    
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

                case Stance::Player_Lying_RH:

                    if (!(pressed & DOWN_BUTTON)) {
                        player.setStance(Stance::Player_Idle_RH);
                        player.setVelocityX(0);
                    }

                    break;

                case Stance::Player_Walk_LH_01:
                case Stance::Player_Walk_LH_03:
                case Stance::Player_Standing_Jump_LH_11:
                case Stance::Player_Running_Jump_LH_11:
                case Stance::Player_Falling_1L_A_LH_07:
                case Stance::Player_Falling_1L_B_LH_07:
                case Stance::Player_Falling_2L_A_LH_11:
                case Stance::Player_Falling_2L_B_LH_11:
                case Stance::Player_Falling_2L_C_LH_07:

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

                case Stance::Player_Lying_LH:

                    if (!(pressed & DOWN_BUTTON)) {
                        player.setStance(Stance::Player_Idle_LH);
                        player.setVelocityX(0);
                    }
                    
                    break;

            }

        }


        // Has the player collided with an item?

        Rect playerRect = player.getRect(world.getXOffset());
        gPlayerRect = playerRect;

        for (uint8_t i = 0; i < Constants::Item_Count; i++) {
        
            Item &item = world.getItem(i);

            
            // Can we skip this one?

            switch (item.getItemType()) {
            
                case ItemType::Banana:
                    {
                        Rect bananaRect = item.getRect(item.getX() + world.getForeground() + world.getXOffset());

                        if (item.getCounter() == 0 && collide(playerRect, bananaRect)) {

                            item.setCounter(5);
                            launchPuff(PuffType::Banana, item);
                            world.incTime(5 * 16);
                            world.setBananas(world.getBananas() + 1);
                            timeCounter = Constants::Time_Counter_Max;
                            playSFX(MusicSFX::SFX_PickUpItem);

                        }

// gPlayerRect = playerRect;
// gBananaRect = bananaRect;

                    }
                    break;

                case ItemType::Heart:
                    {
                        Rect heartRect = item.getRect(item.getX() + world.getForeground() + world.getXOffset());

                        if (item.getCounter() == 0 && collide(playerRect, heartRect)) {

                            item.setCounter(5);
                            launchPuff(PuffType::Heart, item);
                            player.incHealth(2);
                            healthCounter = Constants::Health_Counter_Max;
                            healthFlash = false;
                            launchHeart(item);
                            playSFX(MusicSFX::SFX_XPGain);

                        }

// gPlayerRect = playerRect;
// gEnemyRect = heartRect;

                    }
                    break;


                case ItemType::Fire:
                    {
                        if (healthCounter == 0) {
                            
                            int16_t wf = world.getForeground() % (16 * Constants::Tile_Count);
                            Rect fireRect = item.getRect(item.getX() + wf + world.getXOffset());

                            if (collide(playerRect, fireRect)) {

                                item.setCounter(5);
                                // Serial.println("Dead (Fire)");
                                player.decHealth();
                                healthCounter = Constants::Health_Counter_Max;
                                healthFlash = true;
                                playSFX(MusicSFX::SFX_PlayerBlip);

                            }
gPlayerRect = playerRect;
gEnemyRect = fireRect;
                        }

                    }
                    break;

            }

        }


        // Has the player collided with an enemy?

        if (world.getGameState() == GameState::PlayGame) {
            
            for (uint8_t i = 0; i < Constants::Enemy_Count; i++) {
            
                Enemy &enemy = world.getEnemy(i);

                switch (enemy.getEntityType()) {
                
                    case EntityType::Barrel:
                        
                        if (healthCounter == 0) {

                            Rect barrelRect = enemy.getRect(world.getForeground() + world.getXOffset());

                            if (collide(playerRect, barrelRect)) {

                                // Serial.println("Dead (Barrel)");
                                player.decHealth();
                                healthCounter = Constants::Health_Counter_Max;
                                healthFlash = true;
                                playSFX(MusicSFX::SFX_PlayerBlip);

                                // DEBUG_BREAK

                            }

    // gPlayerRect = playerRect;
    // gBananaRect = bananaRect;

                        }
                        break;

                    case EntityType::Bird:
                        
                        if (healthCounter == 0) {

                            Rect birdRect = enemy.getRect(world.getForeground() + world.getXOffset());

                            if (collide(playerRect, birdRect)) {

                                // Serial.println("Dead (Bird)");
                                player.decHealth();
                                healthCounter = Constants::Health_Counter_Max;
                                healthFlash = true;
                                playSFX(MusicSFX::SFX_PlayerBlip);

                                // DEBUG_BREAK

                            }

    // gPlayerRect = playerRect;
    // gBananaRect = bananaRect;

                        }
                        break;
                
                    case EntityType::Spider:

                        if (healthCounter == 0) {

                            Rect spiderRect = enemy.getRect(world.getForeground() + world.getXOffset());

                            if (enemy.getStance() < Stance::Enemy_Spider_Die_00 && collide(playerRect, spiderRect)) {

                                switch (player.getStance()) {

                                    case Stance::Player_Standing_Jump_RH_00 ... Stance::Player_Standing_Jump_RH_11:
                                    case Stance::Player_Running_Jump_RH_00 ... Stance::Player_Running_Jump_RH_11:
                                    case Stance::Player_Falling_1L_A_RH_00 ... Stance::Player_Falling_1L_A_RH_07:
                                    case Stance::Player_Falling_1L_B_RH_00 ... Stance::Player_Falling_1L_B_RH_07:

                                    case Stance::Player_Standing_Jump_LH_00 ... Stance::Player_Standing_Jump_LH_11:
                                    case Stance::Player_Running_Jump_LH_00 ... Stance::Player_Running_Jump_LH_11:
                                    case Stance::Player_Falling_1L_A_LH_00 ... Stance::Player_Falling_1L_A_LH_07:
                                    case Stance::Player_Falling_1L_B_LH_00 ... Stance::Player_Falling_1L_B_LH_07:
        
                                        enemy.pushSequence(Stance::Enemy_Spider_Die_00, Stance::Enemy_Spider_Die_05, true);
                                        break;

                                    default:
                                        // Serial.println("Dead (Spider)");
                                        player.decHealth();
                                        healthCounter = Constants::Health_Counter_Max;
                                        healthFlash = true;
                                        playSFX(MusicSFX::SFX_PlayerBlip);
                                        break;

                                }
        
    // gPlayerRect = playerRect;
    // gBananaRect = spiderRect;

                            }

                        }
                        break;

                }

            }

        }

        player.update();
        playGame_HandleEnemies(a, world.getGameState());
        world.decTime(); 

    }
    

    if (gameOverCount < 0 && timesUpCount < 0) {

        for (uint8_t i = 0; i < Constants::Item_Count; i++) {

            Item &item = world.getItem(i);
            ItemType itemType = item.getItemType();

            if (itemType == ItemType::None) break;
            
            ItemUpdate itemUpdate = item.update();

            switch (itemUpdate) {
            
                case ItemUpdate::LaunchBanana:
                    {

                        launchBanana(item);
                        updateDirectionCounter();

                    }

                    break;

            }

        }

        world.update();

    }


    // End of game ? -----------------------------------------------------------------------------------

    if (gameOverCount >= 0) {

        if (frameCount % 3 == 0 && gameOverCount < 37) {    
            gameOverCount++;
        }

    }

    if (timesUpCount >= 0) {

        if (frameCount % 3 == 0 && timesUpCount < 37) {    
            timesUpCount++;
        }

    }

    if (gameOverCount == -1 && player.getHealth() == 0) {

        gameOverCount = 0;
        world.setGameState(GameState::PlayGame_GameOver);
        playSFX(MusicSFX::SFX_Death);

    }

    if (timesUpCount == -1 && world.getTime() == 0) {

        timesUpCount = 0;
        world.setGameState(GameState::PlayGame_TimesUp);
        playSFX(MusicSFX::SFX_Death);

    }

}

void playGame(ArduboyGBase_Config<ABG_Mode::L4_Triplane> &a) {

    if (a.needsUpdate()) playGame_Update();

    Player &player = world.getPlayer();
    uint8_t currentPlane = a.currentPlane();
    
    uint8_t stanceImg = getStanceImg(player.getStance());
    player.setImageIdx(stanceImg);

    playGame_Render(a, currentPlane);


    if (gameOverCount >= 0) {
        
        GameOver gameOver;

        FX::seekData(Constants::GameOver + (gameOverCount * 24));
        FX::readObject(gameOver);
        FX::readEnd();

        SpritesU::drawPlusMaskFX(gameOver.char1X, gameOver.char1Y, Images::Font_Alpha_Big, (gameOver.char1 * 3) + currentPlane);
        SpritesU::drawPlusMaskFX(gameOver.char2X, gameOver.char2Y, Images::Font_Alpha_Big, (gameOver.char2 * 3) + currentPlane);
        SpritesU::drawPlusMaskFX(gameOver.char3X, gameOver.char3Y, Images::Font_Alpha_Big, (gameOver.char3 * 3) + currentPlane);
        SpritesU::drawPlusMaskFX(gameOver.char4X, gameOver.char4Y, Images::Font_Alpha_Big, (gameOver.char4 * 3) + currentPlane);
        SpritesU::drawPlusMaskFX(gameOver.char5X, gameOver.char5Y, Images::Font_Alpha_Big, (gameOver.char5 * 3) + currentPlane);
        SpritesU::drawPlusMaskFX(gameOver.char6X, gameOver.char6Y, Images::Font_Alpha_Big, (gameOver.char6 * 3) + currentPlane);
        SpritesU::drawPlusMaskFX(gameOver.char7X, gameOver.char7Y, Images::Font_Alpha_Big, (gameOver.char7 * 3) + currentPlane);
        SpritesU::drawPlusMaskFX(gameOver.char8X, gameOver.char8Y, Images::Font_Alpha_Big, (gameOver.char8 * 3) + currentPlane);
        
    }

    if (timesUpCount >= 0) {
        
        GameOver gameOver;

       FX::seekData(Constants::TimesUp + (timesUpCount * 24));
        FX::readObject(gameOver);
        FX::readEnd();

        SpritesU::drawPlusMaskFX(gameOver.char1X, gameOver.char1Y, Images::Font_Alpha_Big, (gameOver.char1 * 3) + currentPlane);
        SpritesU::drawPlusMaskFX(gameOver.char2X, gameOver.char2Y, Images::Font_Alpha_Big, (gameOver.char2 * 3) + currentPlane);
        SpritesU::drawPlusMaskFX(gameOver.char3X, gameOver.char3Y, Images::Font_Alpha_Big, (gameOver.char3 * 3) + currentPlane);
        SpritesU::drawPlusMaskFX(gameOver.char4X, gameOver.char4Y, Images::Font_Alpha_Big, (gameOver.char4 * 3) + currentPlane);
        SpritesU::drawPlusMaskFX(gameOver.char5X, gameOver.char5Y, Images::Font_Alpha_Big, (gameOver.char5 * 3) + currentPlane);
        SpritesU::drawPlusMaskFX(gameOver.char6X, gameOver.char6Y, Images::Font_Alpha_Big, (gameOver.char6 * 3) + currentPlane);
        SpritesU::drawPlusMaskFX(gameOver.char7X, gameOver.char7Y, Images::Font_Alpha_Big, (gameOver.char7 * 3) + currentPlane);
        SpritesU::drawPlusMaskFX(gameOver.char8X, gameOver.char8Y, Images::Font_Alpha_Big, (gameOver.char8 * 3) + currentPlane);
        
    }

}

