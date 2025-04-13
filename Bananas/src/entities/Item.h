
#pragma once

#include <Arduboy2.h>
#include "../utils/Constants.h"
#include "../utils/Enums.h"

class Item {

    private:

        ItemType itemType;
        int16_t x;
        int8_t y;
        uint8_t frame;
        int16_t data;
        uint16_t counter;

    public:

        int16_t getX()                                  { return this->x; }
        int8_t getY()                                   { return this->y; }
        uint8_t getFrame()                              { return this->frame; }
        int16_t getData()                               { return this->data; }
        uint16_t getCounter()                           { return this->counter; }
        ItemType getItemType()                          { return this->itemType; }

        void setItemType(ItemType val)                  { this->itemType = val; }
        void setX(int16_t val)                          { this->x = val; }
        void setY(int8_t val)                           { this->y = val; }
        void setFrame(uint8_t val)                      { this->frame = val; }
        void setData(int16_t val)                       { this->data = val; }
        void setCounter(uint16_t val)                   { this->counter = val; }


        void update() {

            switch (this->getItemType()) {

                case ItemType::Banana:

                    if (this->counter > 0) {
                    
                        this->counter--;

                        if (this->counter == 0) {
                        
                            this->itemType = ItemType::Banana_Hidden;

                        }

                    }
                        
                    break;


                case ItemType::Puff:

                    if (this->frame < Constants::Puff_Max) this->frame++;
                    break;


                default: break;

            }

        }

        Rect getRect(int16_t worldOffset) {
        
            Rect rect;

            switch (this->getItemType()) {
        
                case ItemType::Banana:

                    rect.x = 55 + worldOffset;
                    rect.y = this->getY();
                    rect.width = 10;
                    rect.height = 10;

                    break;
        
                case ItemType::Heart:

                    rect.x = 60 + worldOffset;
                    rect.y = this->getY() + 1;
                    rect.width = 5;
                    rect.height = 5;

                    break;

            }

            return rect;

        }

};
