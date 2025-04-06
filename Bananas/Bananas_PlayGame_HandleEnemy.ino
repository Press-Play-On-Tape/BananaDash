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

                case EntityType::Bird:
                    {    

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

                        if (enemy.isEmpty()) {

                            switch (stance) {

                                case Stance::Enemy_Flying_LH_19:

                                    // Serial.print(world.getForeground());
                                    // Serial.print(" ");
                                    // Serial.print( enemy.getX());
                                    // Serial.print(" ");
                                    // Serial.println(-world.getForeground() - enemy.getX());

                                    // Serial.println(-world.getForeground() + enemy.getX());
                                    if (-world.getForeground() - enemy.getX() > 100) {

                                        enemy.setX(-world.getForeground() + 160 + (a.randomLFSR(0, 10) * 16));
                                    
                                    }
                                    
                                    enemy.pushSequence(Stance::Enemy_Flying_LH_00, Stance::Enemy_Flying_LH_19);
                                    break;

                                case Stance::Enemy_Flying_RH_19:

                                    // Serial.print(world.getForeground());
                                    // Serial.print(" ");
                                    // Serial.print( enemy.getX());
                                    // Serial.print(" ");
                                    // Serial.println(-world.getForeground() - enemy.getX());

                                    // Serial.println(-world.getForeground() + enemy.getX());
                                    if (-world.getForeground() - enemy.getX() > 100) {

                                        enemy.setX(-world.getForeground() + 160 + (a.randomLFSR(0, 10) * 16));
                                    
                                    }
                                    
                                    enemy.pushSequence(Stance::Enemy_Flying_RH_00, Stance::Enemy_Flying_RH_19);
                                    break;


                            }

                        }

                    }

                    break;

                case EntityType::Spider:
                    {    

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

                        if (enemy.isEmpty()) {

                            switch (stance) {

                                case Stance::Enemy_Spider_R1_15:
                                case Stance::Enemy_Spider_L1_15:
                                case Stance::Enemy_Spider_Idle_15:
// if (-world.getForeground() < enemy.getX()) {
// Serial.println("lll");
// }
// else {
// Serial.println("rrr");
// }

                                    if (-world.getForeground() - enemy.getX() > 90) {
// Serial.print("Move R ");
// Serial.println(enemy.getX());

                                        enemy.pushSequence(Stance::Enemy_Spider_R1_00, Stance::Enemy_Spider_R1_15);

                                    }
                                    else if (-world.getForeground() - enemy.getX() < -90) {
// Serial.print("Move L ");
// Serial.println(enemy.getX());

                                        enemy.pushSequence(Stance::Enemy_Spider_L1_00, Stance::Enemy_Spider_L1_15);

                                    }
                                    else {

                                        switch (a.randomLFSR(0, 10)) {
                                        
                                            case 0:
                                                enemy.pushSequence(Stance::Enemy_Spider_L1_00, Stance::Enemy_Spider_L1_15);
                                                break;

                                            case 1:
                                                enemy.pushSequence(Stance::Enemy_Spider_L1_07, Stance::Enemy_Spider_L1_15);
                                                break;
                                        
                                            case 2:
                                                enemy.pushSequence(Stance::Enemy_Spider_R1_00, Stance::Enemy_Spider_R1_15);
                                                break;

                                            case 3:
                                                enemy.pushSequence(Stance::Enemy_Spider_R1_07, Stance::Enemy_Spider_R1_15);
                                                break;

                                            case 4 ... 5:

                                                if (-world.getForeground() < enemy.getX()) {

                                                    enemy.pushSequence(Stance::Enemy_Spider_L1_00, Stance::Enemy_Spider_L1_15);
                                                }
                                                else {

                                                    enemy.pushSequence(Stance::Enemy_Spider_R1_00, Stance::Enemy_Spider_R1_15);

                                                }

                                                break;

                                            default:
                                                {
                                                    uint8_t r = a.randomLFSR(2, 16);
                                                    enemy.pushSequence(static_cast<Stance>(static_cast<uint16_t>(Stance::Enemy_Spider_Idle_00) + r), Stance::Enemy_Spider_Idle_15);
                                                }
                                                break;

                                        }

                                    }
                                    
                                    enemy.pushSequence(Stance::Enemy_Spider_R1_00, Stance::Enemy_Spider_R1_15);
                                    break;

                            }

                        }

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
                                    enemy.pushSequence(Stance::Enemy_Rolling_LH_00, Stance::Enemy_Rolling_LH_01);
                                }
                                else {
                                    enemy.pushSequence(Stance::Enemy_Rolling_RH_00, Stance::Enemy_Rolling_RH_01);
                                }
                                
                                //enemy.pushSequence(Stance::Enemy_Rolling_RH_00, Stance::Enemy_Rolling_RH_01);

                                break;

                            case Stance::Enemy_Rolling_LH_01:
                            case Stance::Enemy_Rolling_LH_03:
                            case Stance::Enemy_Falling_1L_LH_07:

                                if (world.canWalkLeft(EntityType::Barrel,enemy.getX(), enemy.getY(), tileL, tile)) {

                                    if (enemy.getStance() == Stance::Enemy_Rolling_LH_01) {
                                        enemy.pushSequence(Stance::Enemy_Rolling_LH_02, Stance::Enemy_Rolling_LH_03);
                                    }
                                    else {
                                        enemy.pushSequence(Stance::Enemy_Rolling_LH_00, Stance::Enemy_Rolling_LH_01);
                                    }

                                }
                                else if (world.canFallLeft(EntityType::Barrel, enemy.getY(), tileL, tile)) {
                                    enemy.pushSequence(Stance::Enemy_Falling_1L_LH_00, Stance::Enemy_Falling_1L_LH_07);

                                }                                

                                break;


                            case Stance::Enemy_Rolling_RH_01:
                            case Stance::Enemy_Rolling_RH_03:
                            case Stance::Enemy_Falling_1L_RH_07:

                                if (world.canWalkRight(EntityType::Barrel, enemy.getX(), enemy.getY(), tile, tileR)) {

                                    if (enemy.getStance() == Stance::Enemy_Rolling_RH_01) {
                                        enemy.pushSequence(Stance::Enemy_Rolling_RH_02, Stance::Enemy_Rolling_RH_03);
                                    }
                                    else {
                                        enemy.pushSequence(Stance::Enemy_Rolling_RH_00, Stance::Enemy_Rolling_RH_01);
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