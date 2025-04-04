#pragma once

#include <Arduboy2.h>   
#include "../utils/Constants.h"
#include "../utils/Stack.h"
#include "Item.h"

class Enemy {

    private:

        EntityType entityType;

        int16_t x;
        int8_t y;
        uint8_t counter;
        Stance stance;

        Item item;
        Stack <Stance, Constants::StackSize_Enemy> stack;

    public:

        EntityType getEntityType()                          { return this->entityType; }
        Stance getStance()                                  { return this->stance; }
        Item& getItem()                                     { return this->item; }

        int16_t getX()                                      { return this->x; }
        int8_t getY()                                       { return this->y; }
        uint8_t getCounter()                                { return this->counter; }

        void setEntityType(EntityType val)                  { this->entityType = val; }
        void setStance(Stance val)                          { this->stance = val; }

        void setX(int16_t val)                              { this->x = val; }
        void setY(int8_t val)                               { this->y = val; }
        void setCounter(uint8_t val)                        { this->counter = val; }

        void init() {

        }


        // Other Utils ..

        Direction getDirection() {

            switch (this->getStance()) {

                case Stance::Enemy_Walking_RH_00 ... Stance::Enemy_Walking_RH_03:
                    return Direction::Right;

                default:
                    return Direction::None;           

            }

        }

    	void update() {

            // Housekeeping ..

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

        void pushSequence(Stance fromStance, Stance toStance, bool clear) {

            if (clear) {

                this->stack.clear();
            }

            for (uint16_t x = toStance; x >= fromStance; x--) {

                this->stack.push(static_cast<Stance>(x));

            }

        }

};
