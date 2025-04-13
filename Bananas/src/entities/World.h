#pragma once

#include "../utils/Constants.h"
#include "../utils/Enums.h"
#include "Player.h"


struct World {

    public:

        
    private:
        
        GameState gameState = GameState::SplashScreen_Start;
        Player player;
        Item items[Constants::Item_Count];
        Enemy enemies[Constants::Enemy_Count];

        uint16_t frameCount;
        int16_t background = 0;
        int16_t middleground = 0;
        int16_t foreground = 0;
        int16_t tree[8];
        int8_t xOffset = 0;
        uint16_t time;
        uint16_t bananas;

    public:

        GameState getGameState()                        { return this->gameState; }
        Player &getPlayer()                             { return this->player; }
        Item &getItem(uint8_t idx)                      { return this->items[idx]; }
        Enemy &getEnemy(uint8_t idx)                    { return this->enemies[idx]; }
        uint16_t getFrameCount()                        { return this->frameCount; }
        uint16_t getTime()                              { return this->time; }
        uint16_t getBananas()                           { return this->bananas; }
        int16_t getBackground()                         { return this->background; }
        int16_t getMiddleground()                       { return this->middleground; }
        int16_t getForeground()                         { return this->foreground; }
        int8_t getXOffset()                             { return 0; } //this->xOffset; }

        void setGameState(GameState val)                { this->gameState = val; }
        void setFrameCount(uint16_t val)                { this->frameCount = val; }
        void setTime(uint16_t val)                      { this->time = val; }
        void setBananas(uint16_t val)                   { this->bananas = val; }
        void setBackground(int16_t val)                 { this->background = val; }
        void setMiddleground(int16_t val)               { this->middleground = val; }
        void setForeground(int16_t val)                 { this->foreground = val; }
        void setXOffset(int16_t val)                    { this->xOffset = val; }


        int16_t getTree(uint8_t idx) { return this->tree[idx]; }

        void setTree(uint8_t idx, int16_t val) { this->tree[idx] = val; }

        void incGameState() {

            this->gameState++;

        }

        void decGameState() {

            this->gameState--;

        }

        void decTime() {

            if (this->time > 0) {
                this->time--;
            }

        }
        
        void incFrameCount() {

            this->frameCount++;

        }

        void incForeground(int8_t val) {
            
            this->foreground = this->foreground + val;
            this->player.setVelocityX(val);
            
        }
        
        void incBackground(int8_t val) {

            for (uint8_t i = 4; i <= 7; i++) {
                this->incTree(i, val);
            }

            this->background += val;


            if (this->background >= 256 || this->background <= -256) {
                this->background = 0;
            }

        }

        void incTime(int8_t val) {
            
            if (this->time + val <= (99 * 16)) {
                this->time = this->time + val;
            }
            else {
                this->time = (99 * 16);
            }
            
        }

        void incTree(uint8_t idx, int8_t val) {

            this->tree[idx] = this->tree[idx] + val;

            if (idx < 4) {

                if (this->tree[idx] <= -64) {
                    this->tree[idx] = this->tree[idx] + 128 + 64;
                }

            }
            else {

                if (this->tree[idx] <= -43) {
                    this->tree[idx] = this->tree[idx] + 128 + 43;
                }
            
            }

        }

        bool incMiddleground(int8_t val) {

            // if (this->middleground + val <= -496) {
            //     this->middleground = -496;
            //     return false;
            // }

            for (uint8_t i = 0; i <= 3; i++) {
                this->incTree(i, val);
            }
            
            this->middleground = this->middleground + val;
            return true;

        }

        void update() {

// Serial.println(this->player.getVelocityX());

            for (uint8_t i = 0; i < Constants::Item_Count; i++) {

                Item &item = this->items[i];
                ItemType itemType = item.getItemType();

                if (itemType == ItemType::None) break;
                
                item.update();

            }

            switch (this->player.getVelocityX()) {

                case -999 ... -1:

                    switch (this->xOffset) {

                        case -31 ... 0:
                            this->xOffset--;
                            break;

                        case 1 ... 31:
                            this->xOffset++;
                            break;

                    }

                    break;

                case 0:

                    switch (this->xOffset) {

                        case -32 ... -1:
                            this->xOffset++;
                            break;

                        case 1 ... 32:
                            this->xOffset--;
                            break;

                    }

                    break;

                case 1 ... 999:

                    switch (this->xOffset) {

                        case -32 ... 0:
                            this->xOffset++;
                            break;

                        case 1 ... 32:
                            this->xOffset--;
                            break;

                    }

                    break;

            }

        }


        bool canClimbUp(uint8_t tile) {
        
            switch (this->player.getY()) {

                case Constants::Level_15:
                case Constants::Level_10:

                    switch (tile) {
                    
                        case 10:
                        case 26:
                        case 35:
                        case 36:
                        case 37:
                            return true;

                        default:
                            return false;

                    }

                    break;

                case Constants::Level_25:
                case Constants::Level_20:

                    switch (tile) {
                    
                        case 25:
                        case 26:
                        case 34:
                        case 36:
                        case 37:
                            return true;

                        default:
                            return false;

                    }

                    break;

                default:
                    return false;
            
            }

        }


        bool canClimbDown(uint8_t tile) {
        
            switch (this->player.getY()) {

                case Constants::Level_20:
                case Constants::Level_15:

                    switch (tile) {
                    
                        case 10:
                        case 26:
                        case 35:
                        case 36:
                        case 37:
                            return true;

                        default:
                            return false;

                    }

                    break;

                case Constants::Level_25:
                case Constants::Level_30:

                    switch (tile) {
                    
                        case 25:
                        case 26:
                        case 34:
                        case 36:
                        case 37:
                            return true;

                        default:
                            return false;

                    }

                    break;

                default:
                    return false;
            
            }
            
        }


        bool canWalkLeft(EntityType entityType, int16_t x, uint8_t y, uint8_t tileL, uint8_t tile) {
            
            #ifdef DEBUG_FALLS
            DEBUG_PRINT("CWL "); 
            DEBUG_PRINT(x);
            DEBUG_PRINT(", abs(x%16)=");
            DEBUG_PRINT(abs(x % 16));  
            DEBUG_PRINT(", ");
            DEBUG_PRINT(tileL); 
            DEBUG_PRINT(" "); 
            DEBUG_PRINTLN(tile); 
            #endif

            switch (y) {

                case Constants::Level_10:

                    switch (tileL) {
                    
                        case 11:                // Crate
                        case 12:                // Barrel

                            return false;

                        case 255:

                            switch (entityType) {
                            
                                case EntityType::Player:
                                    return false;
                            
                                case EntityType::Barrel:
                                    return true;

                            }

                            break;

                        default:
                            return true;

                    }

                    break;

                case Constants::Level_20:

                    switch (tile) {
                    
                        case 0:
                            return (abs(x % 16) < 12 ? true : false);
                    
                        case 1:

                            if (entityType == EntityType::Player) { return true; }
                            break;

                        case 26:                // On 2 level Vine
                        case 36:                // On 2 level Ladder
                            return false;
                    
                        case 10:       
                        case 37:       
                            return true;

                        case 3:
                        case 38:

                            if (entityType == EntityType::Player) { return false; }
                            if (entityType == EntityType::Barrel) { return (abs(x % 16) == 8 ? false : true); }
                            break;

                        case 254:
                        case 255:

                            if (entityType == EntityType::Player) { return false; }
                            if (entityType == EntityType::Barrel) { return true; }
                            break;

                        default:
                            break;

                    }

                    switch (tileL) {
                    
                        case 4:
                        case 11:
                        case 23:
                        case 40 ... 59:
                        case 255:

                            return false;

                        case 3:

                            if (entityType == EntityType::Player) { return (abs(x % 16) == 8 ? false : true); }
                            break;

                        default:

                            return true;

                    }

                    break;

                case Constants::Level_30:

                    switch (tile) {

                        case 20:

                            return (abs(x % 16) < 12 ? true : false);

                        case 21:

                            return true;

                        case 24:

                            if (entityType == EntityType::Player) {

                                return (abs(x % 16) == 8 ? false : true);

                            }
                            break;

                        case 33:

                            if (entityType == EntityType::Player) { return abs(x % 16) <= 8; }
                            if (entityType == EntityType::Barrel) { return true; }
                            break;

                    }

                    switch (tileL) {
                    
                        case 0 ... 19:
                        case 24:
                        case 35:
                        case 43:
                        case 44:
                        case 45:
                        case 254:
                        case 255:

                            return false;

                        default:

                            return true;

                    }

                    break;

                default:
                    return false;
            
            }
            
        }

        bool canFallLeft(EntityType entityType, uint8_t y, uint8_t tileL, uint8_t tile) {

            #ifdef DEBUG_FALLS
            DEBUG_PRINT("CFL ");
            DEBUG_PRINT(tileL);
            DEBUG_PRINT(" ");
            DEBUG_PRINTLN(tile);
            #endif

            switch (y) {
            
                case Constants::Level_10:

                    return false;
            
                case Constants::Level_20:

                    switch (tile) {
                                                
                        case 3:
                        case 38:
                        case 254:
                        case 255:
                            return true;

                        default:
                            break;

                    }

                    switch (tileL) {

                        case 10:
                        case 37:
                        case 254:
                        case 255:

                            return true;

                        case 3:

                            if (entityType == EntityType::Player) { return true; }
                            break;

                        default:

                            return false;

                    }

                    break;

                case Constants::Level_30:

                    switch (tileL) {

                        case 24:

                            return true;

                        default:

                            break;

                    }

                    break;

                    switch (tileL) {
                    
                        case 1:
                        case 10: 
                        case 33:

                            return true;

                        default:

                            return false;

                    }

                    break;

                default:

                    return false;
            
            }
            
        }

        bool canWalkRight(EntityType entityType, int16_t x, uint8_t y, uint8_t tile, uint8_t tileR) {

            #ifdef DEBUG_FALLS
            DEBUG_PRINT("CWR "); 
            DEBUG_PRINT(x);
            DEBUG_PRINT(", abs(x%16)=");
            DEBUG_PRINT(abs(x % 16));  
            DEBUG_PRINT(", ");
            DEBUG_PRINT(tile); 
            DEBUG_PRINT(" "); 
            DEBUG_PRINTLN(tileR); 
            #endif

            switch (y) {

                case Constants::Level_10:

                    switch (tileR) {
                    
                        case 11:        // Crate
                        case 12:        // Barrel
                        case 255:
                       
                            return false;

                        default:

                            return true;

                    }

                    break;

                case Constants::Level_20:

                    switch (tile) {
                        
                        case 4:
                        case 23:
                        case 26:                // On 2 level Vine
                        case 36:                // On 2 level Ladder
                        case 254:             
                        case 255:             

                            return false;

                        case 2:

                            if (entityType == EntityType::Player) { return true; }
                            if (entityType == EntityType::Barrel) { return (abs(x % 16) != 8 ? true : false); }
                            break;

                        case 39:

                            return true;

                        default:

                            break;

                    }

                    switch (tileR) {
                    
                        case 3:
                        case 4:
                        case 11:
                        case 40 ... 59:
                        case 255:

                            return false;

                        default:

                            return true;

                    }

                    break;

                case Constants::Level_30:

                    switch (tile) {
                    
                        case 0 ... 19:
                        case 254:
                        case 255:

                            return false;

                        case 21:

                            return true;

                        case 22:

                            if (entityType == EntityType::Player) { return true; }
                            if (entityType == EntityType::Barrel) { return (abs(x % 16) != 8 ? true : false); }
                            break;

                        case 39:

                            if (entityType == EntityType::Player) { return (abs(x % 16) <= 8 ? true : false); }
                            if (entityType == EntityType::Barrel) { return false; }
                            break;

                        default:

                            break;

                    }

                    switch (tileR) {
                    
                        case 0 ... 19:
                        case 34:
                        case 35:
                        case 43:
                        case 44:
                        case 45:

                            return false;

                        default:

                            return true;

                    }

                    break;

                default:
                    return false;
            
            }
            
        }

        bool canFallRight(EntityType entityType, uint8_t y, uint8_t tile, uint8_t tileR) {

            #ifdef DEBUG_FALLS
            DEBUG_PRINT("CFR ");
            DEBUG_PRINT(tile);
            DEBUG_PRINT(" ");
            DEBUG_PRINTLN(tileR);
            #endif

            switch (y) {
            
                case Constants::Level_10:

                    return false;
            
                case Constants::Level_20:

                    switch (tile) {
                    
                        case 3:
                        case 254:
                        case 255:
                            return true;

                        case 2:

                            if (entityType == EntityType::Barrel) { return true; }
                            break;

                        case 4:

                            return true;

                        default:

                            break;

                    }

                    switch (tileR) {
                    
                        case 10:
                        case 23:
                        case 37:
                            return true;

                        default:
                            return false;

                    }

                    break;

                case Constants::Level_30:

                    switch (tile) {
                    
                        case 0 ... 19:
                        case 39:

                            return true;

                        case 22:

                            if (entityType == EntityType::Player) { return false; }
                            if (entityType == EntityType::Barrel) { return true; }
                            break;

                        default:

                            break;

                    }

                    switch (tileR) {
                    
                        case 33:
                            return true;

                        default:
                            return false;

                    }

                    break;

                default:
                    return false;
            
            }
            
        }

        bool canGoIdle(uint8_t tile) {

            switch (this->player.getY()) {
            
                case 46:        // Level 1.0

                    return true;
            
                case 38:        // Level 1.5

                    return false;
            
                case 30:        // Level 2.0

                    switch (tile) {
                    
                        case 26:
                        case 36:
                            return false;

                        default:
                            return true;

                    }
            
                case 22:        // Level 2.5

                    return false;
            
                case 14:        // Level 3.0

                    return true;

            }

            return false;
        
        }

};