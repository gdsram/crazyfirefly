#include "award_container.h"

#include "audio/include/SimpleAudioEngine.h"

AwardContainer::AwardContainer(float paddingY)
    : Sprite()
    , _visibleSize { cocos2d::Director::getInstance()->getVisibleSize() }
    , _positionX { _visibleSize.width * .5f }
    , _positionY { _visibleSize.height * .6f }
    , _paddingY { paddingY }
    , _awardsVector { }
{
}

AwardContainer::AwardContainer(float x, float y, float paddingY)
    : cocos2d::Sprite()
    , _visibleSize { cocos2d::Director::getInstance()->getVisibleSize() }
    , _positionX { x }
    , _positionY { y }
    , _paddingY { paddingY }
    , _awardsVector { }
{
}

void AwardContainer::initContainer()
{
    setTextureRect(cocos2d::Rect(.00f, .00f, _visibleSize.width, _visibleSize.height));
    setOpacity(0);

    setPosition(cocos2d::Point(_positionX, _positionY));
}

AwardContainer* AwardContainer::createAwardContainer(float paddingY)
{
    AwardContainer* container = new AwardContainer(paddingY);

    if (container && container->init())
    {
        container->initContainer();
        container->autorelease();
        return container;
    }

    CC_SAFE_DELETE(container);
    return nullptr;
}

AwardContainer* AwardContainer::createAwardContainer(float x, float y, float paddingY)
{
    AwardContainer* container = new AwardContainer(x, y, paddingY);

    if (container && container->init())
    {
        container->initContainer();
        container->autorelease();
        return container;
    }

    CC_SAFE_DELETE(container);
    return nullptr;
}

void AwardContainer::createAwardAnimation(const std::string& path)
{
    addAward(path);
    showWithHorizonalEase();
}

void AwardContainer::addAward(const std::string &path)
{
    // creating and positioning the sprite
    auto award = Sprite::create(path);
    award->setOpacity(190 );
    award->setVisible(false);
    award->setPosition(cocos2d::Point(-1 * award->getBoundingBox().size.width * 0.5f, _positionY));

    if (!_awardsVector.empty()) {
        float positionY{_positionY};

        // the new sprite is placed above all previos sprites... so and updating awards' position is required
        int count = _awardsVector.size() -1;
        for (int i = count; i >= 0; --i) {
            cocos2d::Sprite* currentAward = _awardsVector.at(i);
            positionY = positionY - currentAward->getBoundingBox().size.height * .5f - award->getBoundingBox().size.height * .5f - _paddingY;

            auto sequence = cocos2d::Sequence::create(
                        cocos2d::MoveTo::create(.1f, cocos2d::Point(_positionX,  positionY)),
                        nullptr
                        );
            currentAward->runAction(sequence);
        }

    }

    _awardsVector.pushBack(award);
    addChild(award);
}

void AwardContainer::showWithHorizonalEase()
{
    setVisible(true);

    // creating an EaseElasticOut sequence
    Sprite* award = static_cast<Sprite*>(_awardsVector.back());
    award->setVisible(true);

    auto move = cocos2d::MoveTo::create(.75f, cocos2d::Point(_visibleSize.width * .5f, award->getPositionY()));
    auto move_ease_inout2 = cocos2d::EaseElasticOut::create(move, 0.25f);

    auto sequence = cocos2d::Sequence::create(
                move_ease_inout2,
                cocos2d::DelayTime::create(2),
                cocos2d::FadeOut::create(1),
                cocos2d::CallFunc::create([this] () { this->_awardsVector.erase(_awardsVector.begin()); }),
                nullptr
                );

    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/award.ogg");
    award->runAction(sequence);
}
