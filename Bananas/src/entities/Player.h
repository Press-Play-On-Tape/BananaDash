#pragma once

#include <Arduboy2.h>
#include "../utils/Constants.h"
#include "../Utils/Enums.h"
#include "../utils/Stack.h"

class Player {

    public:

        Stack <Stance, Constants::StackSize_Player> stack;
        Stance stance = Stance::Player_Idle_RH;
        Stance fromStance = Stance::None;
        Stance toStance = Stance::None;
        uint8_t y;
        uint8_t imageIdx;
        int8_t velocityX;

    public:

        Stance getStance()                                  { return this->stance; }
        uint8_t getImageIdx()                               { return this->imageIdx; }
        uint8_t getY()                                      { return this->y; }
        int8_t getVelocityX()                               { return this->velocityX; }
      
        void setStance(Stance val)                          { this->stance = val; }
        void setImageIdx(uint8_t val)                       { this->imageIdx = val; }
        void setY(uint8_t val)                              { this->y = val; }
        void setVelocityX(int8_t val)                       { this->velocityX = val; }

        void reset() {

            this->y = 46;
            this->velocityX = 0;
            // this->setPosition(0);
            // this->setJumpPosition(0);
            // this->dead = false;
            // this->falling = false;
            // this->prevXPosition = -1;
            // this->runMovement = Movements::Right;

        }

        void update(){
        }


        Direction getDirection() {
        
            switch (this->stance) {
            
                case Stance::Player_Start_RH ... Stance::Player_End_RH:
                    return Direction::Right;
            
                case Stance::Player_Start_LH ... Stance::Player_End_LH:
                    return Direction::Left;

                default: 
                    return Direction::Right;
                    
            }

        }

        // Stack Methods ---------------------------------------
        
        bool isEmpty(void) {
            return this->stack.isEmpty();
        }

        Stance pop(void) {
            return this->stack.pop();
        }

      	uint8_t getCount(void) {
            return this->stack.getCount();
        }

        Stance & peek(void) {
            return this->stack.peek();
        }

        const Stance & peek(void) const {
            return this->stack.peek();
        }

        bool insert(const Stance & item) {
            return this->stack.insert(item);
        }

        void clear(void) {
            this->stack.clear();
        }

        bool push(Stance item) {
            return this->stack.push(static_cast<Stance>(item));
        }

        void insertSequence(Stance fromStance, Stance toStance) {

            for (uint16_t x = toStance; x >= fromStance; x--) {

                this->stack.insert(static_cast<Stance>(x));

            }

        }

        void pushSequence(Stance fromStance, Stance toStance) {

            this->pushSequence(fromStance, toStance, false);

        }

        void stageSequence(Stance fromStance, Stance toStance) {

            this->fromStance = fromStance;
            this->toStance = toStance;

        }

        bool commitSequence() {

            if (this->fromStance != Stance::None && this->toStance != Stance::None) {

                this->pushSequence(this->fromStance, this->toStance, false);
                this->fromStance = Stance::None;
                this->toStance = Stance::None;
                return true;

            }

            return false;

        }

        bool hasStagedSequence() {

            return this->fromStance != Stance::None && this->toStance != Stance::None;

        }

        void pushSequence(Stance fromStance, Stance toStance, bool clear) {

            if (clear) {

                this->stack.clear();
            }

            for (uint16_t x = static_cast<uint16_t>(toStance); x >= static_cast<uint16_t>(fromStance); x--) {

                this->stack.push(static_cast<Stance>(x));

            }

        }

};
