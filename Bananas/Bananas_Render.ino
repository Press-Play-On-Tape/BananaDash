#include <Arduboy2.h>


// ----------------------------------------------------------------------------
//  Render the state .. 
//
void playGame_Render(ArduboyGBase_Config<ABG_Mode::L4_Triplane> &a, uint8_t currentPhase) {

    Player &player = world.getPlayer();

    SpritesU::drawOverwriteFX((world.getBackground() / 2) - 128 + world.getXOffset(), 0, 128, 32, Images::Background, currentPlane);
    SpritesU::drawOverwriteFX((world.getBackground() / 2) + world.getXOffset(), 0, 128, 32, Images::Background, currentPlane);
    SpritesU::drawOverwriteFX((world.getBackground() / 2) + 128 + world.getXOffset(), 0, 128, 32, Images::Background, currentPlane);



    // ____________________________________________________________________________________________________________________________________________________________________________________
    //
    // Render trees ..

    for (uint8_t i = 4; i < 8; i++) {    

        uint24_t treeIdx = FX::readIndexedUInt24(Images::TreeImages, i);
        SpritesU::drawPlusMaskFX(world.getTree(i) + world.getXOffset(), 15, treeIdx, currentPlane);

    }


    for (uint8_t i = 0; i < 4; i++) {    

        uint24_t treeIdx = FX::readIndexedUInt24(Images::TreeImages, i);
        SpritesU::drawPlusMaskFX(world.getTree(i) + world.getXOffset(), 14, treeIdx, currentPlane);

    }


    // ____________________________________________________________________________________________________________________________________________________________________________________
    //
    // Render level ..
    
    int16_t xMin = (- 55 - world.getForeground() -+ world.getXOffset()) / 16;
    int16_t xMax = xMin + 9;

    for (uint8_t i = xMin; i < xMax; i++) {    

        // uint8_t levelIdx = FX::readIndexedUInt8(Level::Level, i);
        uint8_t levelIdx = Level::Level[i];

        switch (levelIdx) {
        
            case 0 ... 19:
                SpritesU::drawPlusMaskFX(55 + (i * 16) + world.getForeground() + world.getXOffset(), 34, 16, 24, Images::LowerOnly, (levelIdx * 3) + currentPlane);
                break;

            case 20 ... 59:
                SpritesU::drawPlusMaskFX(55 + (i * 16) + world.getForeground() + world.getXOffset(), 18, 16, 40, Images::Both, ((levelIdx - 20) * 3) + currentPlane);
                break;

            case 60 ... 79:
                SpritesU::drawPlusMaskFX(55 + (i * 16) + world.getForeground() + world.getXOffset(), 10, 16, 48, Images::UpperOnly, ((levelIdx - 60) * 3) + currentPlane);
                break;

        }

        // a.drawLine(55 + (i * 16) + world.getForeground() + world.getXOffset(), 0, 55 + (i * 16) + world.getForeground() + world.getXOffset(), 128, WHITE);

    }


    // ____________________________________________________________________________________________________________________________________________________________________________________
    //
    // Render items  ..

    for (uint8_t i = 0; i < Constants::Item_Count; i++) {    

        Item &item = world.getItem(i);

        if (item.getItemType() == ItemType::Banana) {

            SpritesU::drawPlusMaskFX(55 + item.getX() + world.getForeground() + world.getXOffset(), item.getY(), 16, 16, Images::Banana, currentPlane);

        }

        if (item.getItemType() == ItemType::Heart) {

            SpritesU::drawPlusMaskFX(58 + item.getX() + world.getForeground() + world.getXOffset(), item.getY(), 9, 8, Images::Heart, currentPlane);

        }

        if (item.getItemType() == ItemType::Fire) {

            SpritesU::drawPlusMaskFX(58 + item.getX() + world.getForeground() + world.getXOffset(), item.getY(), 16, 16, Images::Fire, (item.getFrame() * 3) + currentPlane);

        }

    }


    // ____________________________________________________________________________________________________________________________________________________________________________________
    //
    // Render enemies ..

    for (uint8_t i = 0; i < Constants::Enemy_Count; i++) {    

        Enemy &enemy = world.getEnemy(i);

        if (enemy.getEntityType() == EntityType::Barrel) {

            uint24_t imageIdx = getStanceImg(enemy.getStance());

            if (enemy.getCounter() == 0 || ((enemy.getCounter() / 8) % 2) == 0) { 
                SpritesU::drawPlusMaskFX(55 + enemy.getX() + world.getForeground() + world.getXOffset(), enemy.getY(), 16, 16, Images::Barrel, (imageIdx * 3) + currentPlane);
                // gEnemyRect = enemy.getRect(world.getForeground() + world.getXOffset());
            }

        }

        if (enemy.getEntityType() == EntityType::Bird) {

            uint24_t imageIdx = getStanceImg(enemy.getStance());
            SpritesU::drawPlusMaskFX(55 + enemy.getX() + world.getForeground() + world.getXOffset(), enemy.getY(), 14, 16, Images::Bird, (imageIdx * 3) + currentPlane);

            // gEnemyRect = enemy.getRect(world.getForeground() + world.getXOffset());

            // if (gEnemyRect.x != 0 && currentPlane == 2) DEBUG_BREAK

        }

        if (enemy.getEntityType() == EntityType::Spider) {

            uint24_t imageIdx = getStanceImg(enemy.getStance());
            SpritesU::drawPlusMaskFX(55 + enemy.getX() + world.getForeground() + world.getXOffset(), enemy.getY(), 16, 16, Images::Spider, (imageIdx * 3) + currentPlane);

            // gEnemyRect = enemy.getRect(world.getForeground() + world.getXOffset());
            // if (gEnemyRect.x != 0 && currentPlane == 2) DEBUG_BREAK

        }

    }


    if (healthCounter > 0) {

        healthCounter = healthCounter - 1;

        if (healthFlash == false || (healthCounter / 64) % 2 == 0) {

            SpritesU::drawPlusMaskFX(1, 1, 35, 8, Images::HUD_Health, (player.getHealth() * 3) + currentPlane);
            SpritesU::drawPlusMaskFX(54 + world.getXOffset(), player.getY(), 16, 16, Images::Player, (player.getImageIdx() * 3) + currentPlane);

        }
        else {

            SpritesU::drawPlusMaskFX(1, 1, 35, 8, Images::HUD_Health, (12 * 3) + currentPlane);

        }

    }
    else {

        SpritesU::drawPlusMaskFX(54 + world.getXOffset(), player.getY(), 16, 16, Images::Player, (player.getImageIdx() * 3) + currentPlane);
        SpritesU::drawPlusMaskFX(1, 1, 35, 8, Images::HUD_Banana, (world.getBananas() * 3) + currentPlane);

    }


    if (timeCounter > 0) {

        timeCounter = timeCounter - 1;

        if ((timeCounter / 64) % 2 == 0) {

            SpritesU::drawPlusMaskFX(101, 1, 26, 8, Images::HUD_Time, ((world.getTime() / 16) * 3) + currentPlane);

        }
        else {

            SpritesU::drawPlusMaskFX(101, 1, 26, 8, Images::HUD_Time, (100 * 3) + currentPlane);

        }

    }
    else {

        SpritesU::drawPlusMaskFX(101, 1, 26, 8, Images::HUD_Time, ((world.getTime() / 16) * 3) + currentPlane);

    }


    // a.drawRect(gPlayerRect.x, gPlayerRect.y, gPlayerRect.width, gPlayerRect.height);
    // a.drawRect(gEnemyRect.x, gEnemyRect.y, gEnemyRect.width, gEnemyRect.height);


    Item &item = world.getItem(0);

    if (item.getFrame() < Constants::Puff_Max) {

        uint8_t frame = (item.getFrame() / 8) + item.getData();
        SpritesU::drawPlusMaskFX(55 + item.getX() + world.getForeground() + world.getXOffset(), item.getY(), Images::Puff, (frame * 3) +  currentPlane);

    }

    if (directionCounter > 0) {

        SpritesU::drawPlusMaskFX(1, 54, 13, 8, Images::HUD_Directions, (6) + currentPlane);
        SpritesU::drawPlusMaskFX(114, 54, 13, 8, Images::HUD_Directions, (9 * 3) + currentPlane);
        directionCounter--;

    }

}
