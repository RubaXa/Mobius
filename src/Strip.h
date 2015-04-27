//
//  Strip.h
//

#ifndef Mobius_Strip_h
#define Mobius_Strip_h

#include "Arduino.h"
#include "List.h"


namespace Mobius {
    
    // Лента
    class Strip {
    public:
    	// Элемент ленты
        class Item {
        public:
            Item() {
                Strip::getInstance()->add(this);
            }
            
            virtual void tick(long now) {
            }
        }; // Item
        
        
        static Strip * getInstance() {
            static Strip *instance = new Strip();
            return instance;
        }

        
        List <Item> items;
        
        void add(Item *item) {
            this->items.push(item);
        }
        
        
        void tick() {
            long now = millis();
            
            for (int i = 0; i < this->items.size(); i++) {
                this->items.get(i)->tick(now);
            }
        }
    };
}


#endif
