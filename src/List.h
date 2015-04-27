//
//  List.h
//


#ifndef __Mobius__List__
#define __Mobius__List__


template <typename T> class List {
  public:
    // Деструктор
    ~List() {
        if (this->items) {
            delete []this->items;
            
            this->items = 0;
            this->length = 0;
            this->availableSize = 0;
        }
    }
    
    
    // Получить элемент по индексу
    T & at(int index) const {
        return *this->items[index];
    }
    

    // Получить элемент по индексу
    T * get(int index) const {
        return this->items[index];
    }
    

    
    // Добавить элемент
    int push(T *item) {
        this->resize();
        this->items[this->length++] = item;

        return this->length;
    }
    
    
    // Получить размер списка
    int size() const {
        return this->length;
    }

    
    // Получить зарезервированный размер списка
    int reservedSize() const {
        return this->availableSize;
    }
    
    
  private:
    T **items;
    
    int length = 0;
    int availableSize = 0;
    
    
    void resize() {
        if (this->availableSize == 0) { // Инициализируем
            this->availableSize = 2;
            this->items = new T*[2];
        }
        else if (this->length == this->availableSize) { // Расширяем в два раза
            this->availableSize = this->availableSize * 2;

            T **_items = this->items;
            this->items = new T*[this->availableSize];
            
            for (int i = 0; i < this->length; i++) {
                this->items[i] = _items[i];
            }
        }
    }
};



#endif /* defined(__Mobius__List__) */
