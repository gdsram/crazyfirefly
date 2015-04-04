#ifndef CRAZYFIREFLY_ITEMS_ITEM_H_
#define CRAZYFIREFLY_ITEMS_ITEM_H_

#include "cocos2d.h"

class Item : public cocos2d::Sprite{
public:
    Item() = default;

    Item(const Item&) = default;
    Item& operator=(const Item&) = default;

    Item(Item&&) = default;
    Item& operator=(Item&&) = default;

    ~Item() = default;

    inline virtual int left() const {
        return this->getPositionX() - this->getBoundingBox().size.width * getAnchorPoint().x;
    }

    inline virtual int right() const {
            return this->getPositionX() + this->getBoundingBox().size.width * ( 1 - getAnchorPoint().x );
    }

    inline virtual int top() const {
        return this->getPositionY() + this->getBoundingBox().size.height * ( 1 - getAnchorPoint().y );
    }

    inline virtual int bottom() const {
        return this->getPositionY() - this->getBoundingBox().size.height * getAnchorPoint().y;
    }

    static Item* create(const std::string &imgPath, std::function<void()> behavior);
    bool isAtTop() const; // returns true if the item is at the top of the screen
    void runPower() const;

private:
    std::function<void()> _behavior;
};

#endif // CRAZYFIREFLY_ITEMS_ITEM_H_

