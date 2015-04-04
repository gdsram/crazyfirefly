#include "items/item.h"

#include "cocos2d.h"

Item* Item::create(const std::string &imgPath, std::function<void ()> behavior)
{
    Item* sprite = new Item;

    if (sprite && sprite->initWithFile(imgPath)) {
        sprite->autorelease();
        sprite->setScale(.9f);
        sprite->_behavior = behavior;
        return sprite;
    }

    CC_SAFE_DELETE(sprite);
    return nullptr;
}

bool Item::isAtTop() const
{
    if (getPositionY() > cocos2d::Director::getInstance()->getVisibleSize().height - getBoundingBox().size.height * 0.5)
        return true;
    return false;
}

void Item::runPower() const
{
    _behavior();
}
