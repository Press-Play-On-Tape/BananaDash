#pragma once

#include "../utils/Constants.h"
#include "Player.h"


struct World {

    public:

        
    private:
        
        GameState gameState = GameState::SplashScreen_Start;
        Player player;

        uint16_t frameCount;
        int16_t background = 0;
        int16_t middleground = 0;
        int16_t foreground = 0;
        int16_t palm[8];

    public:

        GameState getGameState()                        { return this->gameState; }
        Player &getPlayer()                             { return this->player; }
        uint16_t getFrameCount()                        { return this->frameCount; }
        int16_t getBackground()                         { return this->background; }
        int16_t getMiddleground()                       { return this->middleground; }
        int16_t getForeground()                         { return this->foreground; }

        void setGameState(GameState val)                { this->gameState = val; }
        void setFrameCount(uint16_t val)                { this->frameCount = val; }
        void setBackground(int16_t val)                 { this->background = val; }
        void setMiddleground(int16_t val)               { this->middleground = val; }
        void setForeground(int16_t val)                 { this->foreground = val; }


        int16_t getPalm(uint8_t idx) { return this->palm[idx]; }

        void setPalm(uint8_t idx, int16_t val) { this->palm[idx] = val; }

        void incFrameCount() {

            this->frameCount++;

        }

        void incForeground(int8_t val) {
            
            this->foreground = this->foreground + val;
            // for (uint8_t i = 0; i <= 3; i++) {
            //     this->incPalm(i, val);
            // }
            
        }
        
        void incBackground(int8_t val) {

            for (uint8_t i = 4; i <= 7; i++) {
                this->incPalm(i, val);
            }

            this->background += val;

            // if (this->background == 128 || this->background == -128) {
            //     this->background = 0;
            // }
            if (this->background >= 256 || this->background <= -256) {
                this->background = 0;
            }

        }

        void incPalm(uint8_t idx, int8_t val) {

            this->palm[idx] = this->palm[idx] + val;

            if (idx < 4) {

                if (this->palm[idx] <= -64) {
                    this->palm[idx] = this->palm[idx] + 128 + 64;
                }

            }
            else {

                if (this->palm[idx] <= -43) {
                    this->palm[idx] = this->palm[idx] + 128 + 43;
                }
            
            }

        }

        bool incMiddleground(int8_t val) {

            // if (this->middleground + val <= -496) {
            //     this->middleground = -496;
            //     return false;
            // }

            for (uint8_t i = 0; i <= 3; i++) {
                this->incPalm(i, val);
            }
            
            this->middleground = this->middleground + val;
            return true;

        }

};