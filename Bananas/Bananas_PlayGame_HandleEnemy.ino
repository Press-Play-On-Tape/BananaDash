#include <ArduboyFX.h>  
#include "src/utils/ArduboyG.h"
#include "src/utils/Constants.h"
#include "src/utils/Enums.h"


void playGame_HandleEnemies(ArduboyGBase_Config<ABG_Mode::L4_Triplane> &a) {

    Player &player = world.getPlayer();

    for (uint8_t i = 0; i < Constants::Enemy_Count; i++) {

        Enemy &enemy = world.getEnemy(i);
        uint16_t stance;


        // if (enemy.getX() == 0) continue;

        if (!enemy.isEmpty()) {


            switch (enemy.getEntityType()) {

                case EntityType::Barrel:
                    {    

                        // Delay entry?

                        if (enemy.getY() == -6 && enemy.getCounter() > 0) {
                            enemy.setCounter(enemy.getCounter() - 1);
                            continue;
                        }


                        // Update position ..

                        Point offset;
                        stance = enemy.pop();

                        enemy.setStance(static_cast<Stance>(stance));

                        StanceDetails stanceDetails;

                        FX::seekData(Constants::StanceDetails + (static_cast<uint16_t>(stance) * 4));
                        FX::readObject(stanceDetails);
                        FX::readEnd();

                        #ifdef DEBUG_POP
                        DEBUG_PRINT("Pop ");
                        DEBUG_PRINT(stanceDetails.stanceY);
                        DEBUG_PRINT(", ");
                        DEBUG_PRINTLN(stanceDetails.foreground);
                        #endif

                        enemy.setY(enemy.getY() + stanceDetails.stanceY);
                        enemy.setX(enemy.getX() + stanceDetails.foreground);

                        uint8_t tileL = getEnemyTile(enemy.getX(), -1);
                        uint8_t tile = getEnemyTile(enemy.getX(), 0);
                        uint8_t tileR = getEnemyTile(enemy.getX(), 1);

                        // switch (stance) {

                        // }

                    }

                    break;


                default: break;

            }

            FX::seekData(Constants::SubsititueStance + (static_cast<uint16_t>(stance) * 2));
            uint16_t subsituteStance = FX::readPendingUInt16();
            FX::readEnd();

            if (subsituteStance != 65535) {
                enemy.setStance(static_cast<Stance>(subsituteStance));
            }


        }
        else {

            uint16_t stance = enemy.getStance();
            uint8_t tileL = getEnemyTile(enemy.getX() + 4, -1);
            uint8_t tile = getEnemyTile(enemy.getX() + 4, 0);
            uint8_t tileR = getEnemyTile(enemy.getX() + 4, 1);
            
            switch (enemy.getEntityType()) {

                case EntityType::Barrel:
                    {    

                        switch (stance) {

                            case Stance::Enemy_Fall_1L_06: 

                                if (a.randomLFSR(0, 2) == 0) { //SJH
                                    enemy.pushSequence(Stance::Enemy_Walking_LH_00, Stance::Enemy_Walking_LH_01);
                                }
                                else {
                                    enemy.pushSequence(Stance::Enemy_Walking_RH_00, Stance::Enemy_Walking_RH_01);
                                }
                                
                                //enemy.pushSequence(Stance::Enemy_Walking_RH_00, Stance::Enemy_Walking_RH_01);

                                break;

                            case Stance::Enemy_Walking_LH_01:
                            case Stance::Enemy_Walking_LH_03:
                            case Stance::Enemy_Falling_1L_LH_07:

                                if (world.canWalkLeft(EntityType::Barrel,enemy.getX(), enemy.getY(), tileL, tile)) {

                                    if (enemy.getStance() == Stance::Enemy_Walking_LH_01) {
                                        enemy.pushSequence(Stance::Enemy_Walking_LH_02, Stance::Enemy_Walking_LH_03);
                                    }
                                    else {
                                        enemy.pushSequence(Stance::Enemy_Walking_LH_00, Stance::Enemy_Walking_LH_01);
                                    }

                                }
                                else if (world.canFallLeft(EntityType::Barrel, enemy.getY(), tileL, tile)) {
                                    enemy.pushSequence(Stance::Enemy_Falling_1L_LH_00, Stance::Enemy_Falling_1L_LH_07);

                                }                                

                                break;


                            case Stance::Enemy_Walking_RH_01:
                            case Stance::Enemy_Walking_RH_03:
                            case Stance::Enemy_Falling_1L_RH_07:

                                if (world.canWalkRight(EntityType::Barrel, enemy.getX(), enemy.getY(), tile, tileR)) {

                                    if (enemy.getStance() == Stance::Enemy_Walking_RH_01) {
                                        enemy.pushSequence(Stance::Enemy_Walking_RH_02, Stance::Enemy_Walking_RH_03);
                                    }
                                    else {
                                        enemy.pushSequence(Stance::Enemy_Walking_RH_00, Stance::Enemy_Walking_RH_01);
                                    }

                                }
                                else if (world.canFallRight(EntityType::Barrel, enemy.getY(), tile, tileR)) {

                                    enemy.pushSequence(Stance::Enemy_Falling_1L_RH_00, Stance::Enemy_Falling_1L_RH_07);

                                }                                

                                break;

                        }

                    }

                    break;


                default: break;

            }

        }

    }

}