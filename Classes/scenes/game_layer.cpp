#include "scenes/game_layer.h"

#include <functional>
#include "../cocos2d/external/flatbuffers/util.h"
#include "audio/include/SimpleAudioEngine.h"

#include "scenes/game_over_scene.h"
#include "scenes/pause_scene.h"
#include "global_colaboration.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "../cocos2d/cocos/platform/android/jni/Java_org_cocos2dx_lib_Cocos2dxHelper.h"
#endif

GameLayer::GameLayer()
    : _player{ nullptr }
    , _hBar{ nullptr }
    , _awardContainer { nullptr }
    , _isTouching{ false }
    , _touchPosition{ .00f }

    // items
    , _killerItem{ nullptr }
    , _superBonusItem{ nullptr }
    , _bonusItemsPoolIndex{ 0 }
    , _harmfulItemsPoolIndex{ 0 }
    , _itemsListIndex{ 0 }
    , _bonusItemInterval{ C_BONUS_ITEM_INTERVAL }
    , _bonusItemTimer{ .00f }
    , _harmfulItemInterval{ C_HARMFUL_ITEM_INTERVAL }
    , _harmfulItemTimer{ .00f }
    , _killerItemInterval{ C_KILLER_ITEM_INTERVAL }
    , _killerItemTimer{ .00f }
    , _superBonusItemInterval{ C_SUPER_BONUS_ITEM_INTERVAL }
    , _superBonusItemTimer{ .00f }
    , _turboItemTimer {.00f }
    , _horizontalBarInterval{ C_HORIZONTAL_BAR_INTERVAL }
    , _horizontalBarTimer{ .00f }
    , _slowMotionItemInterval { C_BEER_ITEM_INTERVAL }
    , _slowMotionItemTimer { 0 }

    // game...
    , _gameDifficultyTimer{ 0 }
    , _gameSpeed{ C_INITIAL_GAME_SPEED }
    , _visibleSize{ cocos2d::Director::getInstance()->getVisibleSize() }
    , _gameTimer{ .00f }
    , _scoreTextSprite{ nullptr }
    , _healthSprite{ nullptr }
    , _survivalTime { 0 }
    , _origin { cocos2d::Director::getInstance()->getVisibleOrigin() }
    , _freezeItems { false }
    , _gameAcceleration { C_GAME_ACCELERATION }

    // awards
    , _bonusItemsConsecutively{ 0 }
    , _harmfulItemsConsecutively { 0 }
    , _timeWithoutPickingUpHarmfulItems{ 0.00f }
    , _countOfHorizontalBarPassed { 0 }
    , _countAwards { 0 }
{
    _itemsList = cocos2d::Vector<Item*>(C_MAX_COUNT_HARMFUL_ITEM + C_MAX_COUNT_BONUS_ITEM);
    _bonusItemsPool = cocos2d::Vector<Item*>(C_MAX_COUNT_HARMFUL_ITEM);
    _harmfulItemsPool = cocos2d::Vector<Item*>(C_MAX_COUNT_BONUS_ITEM);
    _backgroundSpriteVector = cocos2d::Vector<cocos2d::Sprite*>(2);
    _turboItemsPool = cocos2d::Vector<Item*>(10);
}

cocos2d::Scene* GameLayer::createScene()
{
    cocos2d::Scene *scene = cocos2d::Scene::create();
    auto *layer = GameLayer::create();
    scene->addChild(layer);

    return scene;
}

bool GameLayer::init() 
{
    if ( !Layer::init() ) {
        return false;
    }

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    setKeepScreenOnJni(true);
    #endif

    this->initAudio();
    this->initGameScreen();
    this->initEventListener();

    this->schedule(schedule_selector(GameLayer::update));

    return true;
}


bool GameLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event * event)
{
    _isTouching = true;
    _touchPosition = touch->getLocation().x;
    return true;
}

void GameLayer::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event * event)
{
    _isTouching = false;

    if(touch) {
        cocos2d::Point tap = touch->getLocation();
        cocos2d::Point playerNextPosition = _player->getNextPosition();

        if (!_player->getBoundingBox().containsPoint(tap)) {
            if ( tap.x != playerNextPosition.x || tap.y != playerNextPosition.y) {

                float distanceToMove = tap.getDistance(_player->getPosition());
                float movementTime = distanceToMove / _player->getSpeed();

                //_player->stopAllActions();
                cocos2d::Action *movement = cocos2d::MoveTo::create(movementTime, tap); // making sure the player is moving at constant velocity
                _player->runAction(movement);
                _player->setNextPosition(tap);
            }
        }
    }
}

void GameLayer::onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event * event)
{
    onTouchEnded(touch, event);
}

void GameLayer::onAcceleration(cocos2d::Acceleration *acc, cocos2d::Event *event)
{
    cocos2d::Director* director = cocos2d::Director::getInstance();

    cocos2d::Point ptNow  = _player->getPosition();
    cocos2d::Point ptTemp = director->convertToUI(ptNow);

    ptTemp.x += acc->x * _gameAcceleration;
    ptTemp.y -= acc->y * _gameAcceleration;

    float playerRadius = _player->getRadius();

    cocos2d::Point ptNext = director->convertToGL(ptTemp);
    ptNext.x = MIN(MAX(ptNext.x, playerRadius), _visibleSize.width - playerRadius);
    ptNext.y = MIN(MAX(ptNext.y, playerRadius), _visibleSize.height - playerRadius);
    _player->setPosition(ptNext);
}

// menu callbacks

void GameLayer::goToPauseScene(Ref *pSender)
{
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    setKeepScreenOnJni(false);
    #endif

    CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();

    auto scene = PauseScene::createScene();
    cocos2d::Director::getInstance()->pushScene(scene);
}

void GameLayer::goToGameOverScene()
{
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    setKeepScreenOnJni(false);
    #endif

    C_GLOBAL_COLABORATION_->setMaxBonusItem(_bonusItemsConsecutively);
    C_GLOBAL_COLABORATION_->setMaxTimeWithoutPickingHarmfulItems(_timeWithoutPickingUpHarmfulItems);

    int finalScore = _player->getScore();
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();

    saveScore(); // saving the player's score
    resetGame(); // reseting the game's settings

    auto scene = GameOverScene::createScene(finalScore);
    cocos2d::Director::getInstance()->replaceScene(scene);
}

// main loop

void GameLayer::update(float dt)
{
    checkForPlayerCollisions();
    checkForPickingUps();

    updateGameLabels();
    updateTimers(dt);

    scrollBackground(dt);

    checkForGameOver();
}

// init methods

void GameLayer::initGameScreen()
{
    initMenu();
    initBackGround();
    initPlayer();
    initHorizontalBar();
    initLabels();
    initItems();
    initAwardMessages();
}

void GameLayer::initMenu()
{
    auto pauseItem =
            cocos2d::MenuItemImage::create("buttons/pause_button.png", "buttons/pause_button_pressed.png", CC_CALLBACK_1(GameLayer::goToPauseScene, this));
    pauseItem->setPosition(cocos2d::Point(_visibleSize.width - pauseItem->getContentSize().width / 2,
                                 _visibleSize.height - pauseItem->getContentSize().height / 2));

    auto menu = cocos2d::Menu::create(pauseItem, NULL);
    menu->setPosition(cocos2d::Point::ZERO);
    this->addChild(menu, kForeground);
}

void GameLayer::initAudio()
{
    C_AUDIO_->preloadEffect("audio/gameover.ogg");
    C_AUDIO_->preloadEffect("audio/pick_harmful.ogg");
    C_AUDIO_->preloadEffect("audio/pick_bonus.ogg");

    if (C_AUDIO_->isBackgroundMusicPlaying() == false)
    {
        C_AUDIO_->preloadBackgroundMusic("audio/background.ogg");
        C_AUDIO_->playBackgroundMusic("audio/background.ogg", true);
    }

    C_AUDIO_->setBackgroundMusicVolume(C_GLOBAL_COLABORATION_->getBgMusicVolume());
    C_AUDIO_->setEffectsVolume(C_GLOBAL_COLABORATION_->getEffectsMusicVolume());
}

void GameLayer::initBackGround()
{
    for (int i = 0; i < 2; ++i)
    {
        cocos2d::Sprite* sprite = cocos2d::Sprite::create("background_game.png");
        sprite->setAnchorPoint(cocos2d::Point(.5f, .0f));
        sprite->setPosition(cocos2d::Point(_visibleSize.width / 2, sprite->getBoundingBox().size.height * i));

        this->addChild(sprite, kBackground);
        _backgroundSpriteVector.pushBack(sprite);
    }
}

void GameLayer::initPlayer()
{
    _player = Player::create(C_PLAYER_MIN_SCALE,  C_PLAYER_MAX_SCALE, _gameSpeed * C_PLAYER_SPEED_FACTOR);
    addChild(_player, kForeground, "player");
}

void GameLayer::initHorizontalBar()
{
    _hBar = HorizontalBar::create();
    addChild(_hBar, kBackground);
}

void GameLayer::initLabels()
{

    cocos2d::Sprite *healthBackground { cocos2d::Sprite::create("animations/health/healt_background.png") };
    healthBackground->setAnchorPoint(cocos2d::Vec2::ANCHOR_TOP_LEFT);
    this->addChild(healthBackground, kBackground);

    // init energy level sprite
    _healthSprite = Health::create();
    _healthSprite->setHealthBackground(healthBackground);

    _healthSprite->initAtTheBeginningOfTheGame();
    _healthSprite->setHealth(_player->getEnergy());
    healthBackground->setPosition(_healthSprite->getPosition());
    this->addChild(_healthSprite, kForeground);

    _scoreTextSprite = cocos2d::Sprite::createWithSpriteFrameName("label_score.png");
    _scoreTextSprite->setPosition(cocos2d::Point(_visibleSize.width * 0.6f, _visibleSize.height * 0.94f));
    this->addChild(_scoreTextSprite, kForeground);

    _playerScore = cocos2d::Label::createWithBMFont("font.fnt", "0", cocos2d::TextHAlignment::LEFT);
    _playerScore->setAnchorPoint(cocos2d::Point(1, 0.5));
    _playerScore->setPosition(cocos2d::Point(_scoreTextSprite->getPositionX() + _scoreTextSprite->getContentSize().width, _visibleSize.height * 0.94f));
    this->addChild(_playerScore, kForeground);
}

void GameLayer::initAwardMessages()
{
    _awardContainer = AwardContainer::createAwardContainer(_visibleSize.height * .075f);
    addChild(_awardContainer, kAboveAll);
}

void GameLayer::initEventListener()
{
    // setting up touch events
    auto touchListener = cocos2d::EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded, this);
    touchListener->onTouchCancelled = CC_CALLBACK_2(GameLayer::onTouchCancelled, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);

    // setting up accelerometer event
    cocos2d::Device::setAccelerometerEnabled(true);
    auto accListener = cocos2d::EventListenerAcceleration::create(CC_CALLBACK_2(GameLayer::onAcceleration, this));
    cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(accListener, this);
}


void GameLayer::initItems()
{
    // init items with its behaviors
    Item *item;
    int i = 0;

    // bonus items ---------------------------------------------------------
    for (i = 0; i < C_MAX_COUNT_BONUS_ITEM; ++  i) {
        // filling bonusItem Vector
        item = Item::create("items/bonus1.png", [this](){
            // bonus item's behavior
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/pick_bonus.ogg");
            _player->setEnergy(_player->getEnergy() + C_BONUS_ENERGY_MODIFICATOR_VALUE);
            _healthSprite->setHealth(_player->getEnergy());
            _player->setScore(_player->getScore() + 3);
            _player->runScaleAction(C_BONUS_SIZE_MODIFICATOR_FACTOR);

            _bonusItemsConsecutively++;
            _harmfulItemsConsecutively = 0;
        });
        item->setVisible(false);
        this->addChild(item, kMiddleground);
        _bonusItemsPool.pushBack(item);
    }

    // harmful items ------------------------------------------------------
    for (i = 0; i < C_MAX_COUNT_HARMFUL_ITEM; i++) {
        // filling harmfulItem Vector
        item = Item::create("items/harmful1.png", [this](){
            // harmfull item's behavior
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/pick_harmful.ogg");
            _player->setEnergy(_player->getEnergy() + C_HARMFUL_ITEM_ENERGY_MODIFICATOR_VALUE);
            _healthSprite->setHealth(_player->getEnergy());
            //_player->setScore(_player->getScore() + 1);
            _player->runScaleAction(C_HARMFUL_ITEM_SIZE_MODIFICATOR_FACTOR);

            _harmfulItemsConsecutively++;
            C_GLOBAL_COLABORATION_->setMaxBonusItem(_bonusItemsConsecutively);
            _bonusItemsConsecutively = 0;

            C_GLOBAL_COLABORATION_->setMaxTimeWithoutPickingHarmfulItems(_timeWithoutPickingUpHarmfulItems);
            _timeWithoutPickingUpHarmfulItems = 0;
        });
        item->setVisible(false);
        this->addChild(item, kMiddleground);

        _harmfulItemsPool.pushBack(item);
    }

    // init super bonus item ------------------------------------------------
    _superBonusItem = Item::create("items/super.png", [this](){
        // super bonus item's behavior
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/special_item.ogg");
        _player->resetEnergy();
        _healthSprite->setHealth(_player->getEnergy());
        _player->setScore(_player->getScore() + 10);
        _player->resetSize();

        _harmfulItemsConsecutively = 0;
    });
    _superBonusItem->setVisible(false);
    this->addChild(_superBonusItem, kMiddleground);

    // init killer item -------------------------------------------------------
    _killerItem = Item::create("items/killer1.png", [this](){
        // killer item's behavior
        _player->setEnergy(0);
        _healthSprite->setHealth(_player->getEnergy());

        _harmfulItemsConsecutively = 0;
    });
    _killerItem->setVisible(false);
    this->addChild(_killerItem, kMiddleground);

    // init turbo item --------------------------------------------------------
    _turboItem = Item::create("items/turbo.png", [this] () {
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/special_item.ogg");
        //turbo item behavior
    _gameAcceleration = C_GAME_ACCELERATION * 2.50f;
        auto seq = cocos2d::Sequence::create(
                   cocos2d::DelayTime::create(6.0f),
                   cocos2d::CallFunc::create([this] () { this->_gameAcceleration = C_GAME_ACCELERATION; }),
                   nullptr
                   );

        runAction(seq);

    _harmfulItemsConsecutively = 0;

    });
    _turboItem->setVisible(false);
    this->addChild(_turboItem, kMiddleground);

    // init slowMotion item ---------------------------------------------------
    _slowMotionItem = Item::create("items/slow.png", [this] () {
        // slow motion item behavior
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/special_item.ogg");
        float currentGameSpeed = _gameSpeed;
        updateGameSpeed(C_INITIAL_GAME_SPEED / 2);

        auto seq = cocos2d::Sequence::create(
                    cocos2d::DelayTime::create(6.0f),
                    cocos2d::CallFunc::create([this, currentGameSpeed] () { this->updateGameSpeed(currentGameSpeed); }),
                    nullptr
                    );

        runAction(seq);

        _harmfulItemsConsecutively = 0;
    });
    _slowMotionItem->setVisible(false);
    this->addChild(_slowMotionItem, kMiddleground);
}

void GameLayer::updateTimers(float dt)
{
    // horizontal bar timer
    _horizontalBarTimer += dt;

    // making sure that no item will placed right after or right before the horizontal bar
    if (!_hBar->isVisible() && !_freezeItems) {
        float leftingTimeForHBar = _horizontalBarInterval - _horizontalBarTimer;
        float freezenTime = _player->getBoundingBox().size.height * 1.5f / _gameSpeed + dt;
        if (leftingTimeForHBar <= freezenTime)
            _freezeItems = true; // no item will be created until the horizontal bar has been shown on the screen
    }

    if (_horizontalBarTimer >= _horizontalBarInterval) {

        _horizontalBarTimer = 0;
        this->showHorizontalBar();

        float freezenTime = (_player->getBoundingBox().size.height + _hBar->getBarHeight()) / _gameSpeed + dt;

        auto seq = cocos2d::Sequence::create(
                    cocos2d::DelayTime::create(freezenTime), // no item will be created until
                    cocos2d::CallFunc::create([this](){ this->_freezeItems = false; }),
                    nullptr
                    );

        this->runAction(seq);

    }

    // item timers
    _gameTimer += dt;

    // avoiding collision with the horizontal bar when it is at the top of the screen
    if (!isHBarAtTop() && !_freezeItems) {

        _bonusItemTimer += dt;
        if (_bonusItemTimer > _bonusItemInterval) {
            _bonusItemTimer = .0f;
            this->createBonusItem();
        }

        _harmfulItemTimer += dt;
        if (_harmfulItemTimer > _harmfulItemInterval) {
            _harmfulItemTimer = .0f;
            this->createHarmfulItem();
        }

        _superBonusItemTimer += dt;
        if (_superBonusItemTimer >= _superBonusItemInterval) {
            _superBonusItemTimer = .0f;
            this->createSuperBonusItem();
        }

        _killerItemTimer += dt;
        if (_killerItemTimer >= _killerItemInterval) {
            _killerItemTimer = .0f;
            this->createKillerItem();
        }

        _slowMotionItemTimer += dt;
        if (_slowMotionItemTimer >= _slowMotionItemInterval) {
            _slowMotionItemTimer = .0f;
            this->createSlowMotionItem();
        }

        _turboItemTimer += dt;
        if (_turboItemTimer >= C_PARTY_ITEM_INTERVAL) {
            _turboItemTimer = .0f;
            createTurboItem();
        }
    }

    // increasing game difficulty
    _gameDifficultyTimer += dt;

    if (_gameDifficultyTimer > C_DIFFICULTY_GAME_INTERVAL) {
        _gameDifficultyTimer = 0;
        increaseDifficulty();
    }

    // updating player every second
    if (_gameTimer > 1.00f) {
        ++_survivalTime;
        _gameTimer -= 1.00f;

        // every second, player's energy will decrease by one and player's score will increase by one
        _player->setEnergy(_player->getEnergy() - 1);
        _healthSprite->setHealth(_player->getEnergy());
        _player->setScore(_player->getScore() + 1);
    }

    updateAwardsTimers(dt);
}

void GameLayer::updateGameSpeed(float speed)
{
    _gameSpeed = speed;
    float distanceToGetOffTheScreen = 0;

    // updating items' speed
    cocos2d::Vector<Item*>::iterator it1 = _itemsList.begin(), it2 = _itemsList.end();

    for (; it1 != it2; ++it1) {
        if ((static_cast<Item*>(*it1))->isVisible()) {
            (static_cast<Item*>(*it1))->stopAllActions();

            distanceToGetOffTheScreen = (static_cast<Item*>(*it1))->getPositionY() - C_SCREEN_END_POINT_Y;
            (static_cast<Item*>(*it1))->runAction(createItemMovement(distanceToGetOffTheScreen / _gameSpeed, (static_cast<Item*>(*it1))->getPositionX()));
        }
    }

    // updating the speed of horizontal bar
    if (_hBar->isVisible()) {
        _hBar->stopAllActions();
        distanceToGetOffTheScreen = _hBar->getPositionY() - C_SCREEN_END_POINT_Y;
        _hBar->runAction(createHorizontalBarMovement(distanceToGetOffTheScreen / _gameSpeed));
    }
}

void GameLayer::updateGameLabels()
{
    std::string score = flatbuffers::NumToString(_player->getScore());
    _playerScore->setString(score);
}

void GameLayer::updateAwardsTimers(float dt)
{
    // bonus
    if (_bonusItemsConsecutively >= 5) {
        _bonusItemsConsecutively = 0;

        _awardContainer->createAwardAnimation("awards/bonus.png");
        _player->setScore(_player->getScore() + 5);
    }

    _timeWithoutPickingUpHarmfulItems += dt;

    if (_countOfHorizontalBarPassed >= 5) {
        _countOfHorizontalBarPassed = 0;

        _awardContainer->createAwardAnimation("awards/hbar.png");
        _player->setScore(_player->getScore() + 5);
    }

    // punishment
    if (_harmfulItemsConsecutively >= 2) {
        _harmfulItemsConsecutively = 0;

        _awardContainer->createAwardAnimation("awards/harmful.png");
        _player->setScore(_player->getScore() - 5);
    }
}

void GameLayer::increaseDifficulty()
{
    // updating timers
    _bonusItemInterval += C_BONUS_ITEM_INTERVAL_VARYING_FACTOR;
    if (_bonusItemInterval > C_MAX_BONUS_ITEM_INTERVAL)
        _bonusItemInterval = C_MAX_BONUS_ITEM_INTERVAL;

    _harmfulItemInterval -= C_HARMFUL_ITEM_INTERVAL_VARYING_FACTOR;
    if (_harmfulItemInterval < C_MIN_HARMFUL_ITEM_INTERVAL)
        _harmfulItemInterval = C_MIN_HARMFUL_ITEM_INTERVAL;

    _horizontalBarInterval -= C_HORIZONTAL_BAR_INTERVAL_VARYING_FACTOR;
    if (_horizontalBarInterval < C_MIN_HORIZONTAL_BAR_INTERVAL)
        _horizontalBarInterval = C_MIN_HORIZONTAL_BAR_INTERVAL;

    _killerItemInterval -= C_KILLER_ITEM_INTERVAL_VARYING_FACTOR;
    if (_killerItemInterval < C_KILLER_ITEM_INTERVAL)
        _killerItemInterval = C_KILLER_ITEM_INTERVAL;

    _superBonusItemInterval += C_SUPER_BONUS_ITEM_INTERVAL_VARYING_FACTOR;
    if (_superBonusItemInterval > C_MAX_SUPER_BONUS_CALL_ITEM_INTERVAL)
        _superBonusItemInterval = C_MAX_SUPER_BONUS_CALL_ITEM_INTERVAL;

    // increasing game difficulty

    // updating game speed
    _gameSpeed += C_GAME_SPEED_VARYING_FACTOR;
    if (_gameSpeed > C_MAX_GAME_SPEED)
        _gameSpeed = C_MAX_GAME_SPEED;
    updateGameSpeed(_gameSpeed);

    // reducing the size of the bar gap
    _hBar->setGapWidth(MAX(_hBar->getGap()->getContentSize().width * C_GAP_REDUCTION_FACTOR, _hBar->getMinGapWidth()));

}

void GameLayer::showHorizontalBar()
{
    _hBar->updateHorizontalBar();
    _hBar->setPosition(cocos2d::Point(_hBar->getAnchorPoint().x * _visibleSize.width, C_SCREEN_START_POINT_Y));
    _hBar->setActiveSide(kBottomSide);
    _hBar->setVisible(true);

    _hBar->runAction(createHorizontalBarMovement( (C_SCREEN_START_POINT_Y - C_SCREEN_END_POINT_Y) / _gameSpeed));
}

void GameLayer::scrollBackground(float dt)
{
    float dy = (0.2 * _visibleSize.height * dt);

    for (int i = 0; i < 2; i++) {
        cocos2d::Sprite* sprite = _backgroundSpriteVector.at(i);

        // chencking if the sprites are off the screen
        if (sprite->getPositionY() <= -1 * sprite->getBoundingBox().size.height)
        {
            cocos2d::Sprite* anotherBackgroundImage = _backgroundSpriteVector.at(!(1 && i));

            sprite->setPosition(cocos2d::Point(sprite->getPositionX(),
                                      anotherBackgroundImage->getPositionY() + anotherBackgroundImage->getContentSize().height));
        }

        // moving the background
        sprite->setPosition(cocos2d::Point(sprite->getPositionX(), sprite->getPosition().y - dy));
    }
}

void GameLayer::checkForPickingUps()
{
    int itemsCount = _itemsList.size();

    for (int i = itemsCount - 1 ; i >= 0 ; --i) {
        Item *item = static_cast<Item*>(_itemsList.at(i));

        if (!item->isVisible()) continue;

        float diffx = _player->getPositionX() - item->getPositionX();
        float diffy = _player->getPositionY() - item->getPositionY();

        if (pow(diffx, 2) + pow(diffy, 2) <= pow(_player->getRadius() + item->getContentSize().width * 0.5, 2))
        {
            item->runPower(); // run item's behavior
            item->stopAllActions();
            item->setVisible(false);

            _itemsList.erase(i);
        }
    }
}

void GameLayer::checkForPlayerCollisions()
{
    float playerRadius = _player->getRadius();

    //collision between player and side bars
    float minimum_x = playerRadius;
    float maximum_x = (_visibleSize.width - playerRadius);

    if (_player->getPositionX() < minimum_x) {
        _player->setPositionX(minimum_x);
    }

    if (_player->getPositionX() > maximum_x) {
        _player->setPositionX(maximum_x);
    }

    // checking for top and down collisions
    float minimum_y = playerRadius;
    float maximum_y = _visibleSize.height - playerRadius;

    if (_player->getPositionY() > maximum_y) {
        _player->setPositionY(maximum_y);
    }

    if (_player->getPositionY() < minimum_y) {
        _player->setPositionY(minimum_y);
    }

    checkForPlayerCollisionsWithHBar(playerRadius);
}

void GameLayer::checkForPlayerCollisionsWithHBar(float playerRadius)
{
    float playerPositionX = _player->getPositionX();
    float playerPositionY = _player->getPositionY();
    float gapPosition = _hBar->getGap()->getPositionX();
    float gapWidth = _hBar->getGap()->getContentSize().width;

    if (_hBar->isVisible()) {
        if ((playerPositionY - playerRadius) > _hBar->top() && _hBar->getActiveSide() != kTopSide) {
            _hBar->setActiveSide(kTopSide);
            C_GLOBAL_COLABORATION_->incrementTimesHBarHasBeenCrossed(1); // incrementing
            _countOfHorizontalBarPassed++;
            _countAwards++;
        }

        if (_hBar->getActiveSide() == kBottomSide) { // player is under the horizontal bar

            // checking for collisions between the player and the bar's bottom
            if ((playerPositionX - playerRadius) < gapPosition || (playerPositionX + playerRadius) > (gapPosition + gapWidth) ) {
                if ((playerPositionY + playerRadius) > _hBar->bottom()) {
                    _player->setPositionY(_hBar->bottom() - playerRadius);
                }
            } else {
                // player is in the gap
                if ((playerPositionY - playerRadius) > _hBar->bottom()) {
                    _hBar->setActiveSide(kGapSides);
                }
            }

        } else if (_hBar->getActiveSide() == kGapSides) {

            // checking collision with player and gap's walls
            if ((playerPositionX - playerRadius) < gapPosition) {
                _player->setPositionX(gapPosition + playerRadius);
            } else {
                if ((playerPositionX + playerRadius) > (gapPosition + gapWidth)) {
                    _player->setPositionX(gapPosition + gapWidth - playerRadius);
                }
            }

        } else if (_hBar->top() > _player->getPositionY() - playerRadius) { // once the player went through the bar, he can't go back
                    _player->setPosition(cocos2d::Point(playerPositionX, _hBar->top() + playerRadius));
        }
    }
}

void GameLayer::checkForGameOver()
{
    float playerRadius = _player->getRadius();

    if (_player->getEnergy() <= 0) {
        goToGameOverScene();
        return;
    }

    if ( (_player->getPositionX() - _player->getRadius()) > _hBar->getGap()->getPositionX() &&
        (_player->getPositionX() + _player->getRadius()) < (_hBar->getGap()->getPositionX() + _hBar->getGap()->getContentSize().width)) {

        return; // player is in the gap

    } else if (_player->getPositionY() <= playerRadius
            // player can  touch the bottom of the screen, but loose only if the horizontal bar is pushing him
            && _hBar->bottom() > 0 && _hBar->bottom() < playerRadius * 2.0f) {

        goToGameOverScene();
        return;
    }
}

cocos2d::FiniteTimeAction* GameLayer::createItemMovement(float duration, float toX)
{
    cocos2d::FiniteTimeAction*  sequence = cocos2d::Sequence::create(
                cocos2d::MoveTo::create(duration, cocos2d::Point(toX, C_SCREEN_END_POINT_Y)),
                nullptr);

    //item.runAction(sequence);
    return sequence;
}

cocos2d::FiniteTimeAction* GameLayer::createHorizontalBarMovement(float duration)
{
    cocos2d::FiniteTimeAction*  movement = cocos2d::Sequence::create(
                cocos2d::MoveTo::create(duration, cocos2d::Point(_hBar->getAnchorPoint().x * _visibleSize.width, C_SCREEN_END_POINT_Y)),
                cocos2d::CallFunc::create([this](){ _hBar->setVisible(false);}),
                nullptr);

    return movement;
}



// checking for collision between items when creating a new one
bool GameLayer::isPositionAvailable(int startingPositionX) const
{
    std::vector<Item*>::const_iterator it1 = _itemsList.begin(), it2 = _itemsList.end();

    for (; it1 != it2; ++it1) {
        if ((*it1)->isVisible() && (*it1)->isAtTop()) {

            float itemWidth = (*it1)->getContentSize().width;

            if (startingPositionX > (*it1)->left() - itemWidth * 0.5f
                    && startingPositionX < (*it1)->right() + itemWidth * 0.5f)
                return false;
        }
    }

    return true;
}

/*
 *  checking for any item at the top of the screen in order to avoid collisions with any
 *  of them when showing the horizontal bar
 */

bool GameLayer::isAnyItemAtTop() const
{

    float topLimit = C_SCREEN_START_POINT_Y - _hBar->getBarHeight() * 0.5f - _player->getBoundingBox().size.height;

    if (!_itemsList.size())
        return false;

    Item* item = _itemsList.back();

    if (item) {
        if ( item->top() > topLimit)
            return true;
    }

    return false;
}

bool GameLayer::isHBarAtTop() const
{
    // making sure that none item will block the gap
    float topLimit =  _visibleSize.height - _hBar->getBarHeight() - _player->getBoundingBox().size.height;

    if (_hBar->isVisible() && _hBar->getPositionY() > topLimit)
        return true;
    return false;
}

void GameLayer::saveScore()
{
    C_GLOBAL_COLABORATION_->setMaxScore(_player->getScore());
    C_GLOBAL_COLABORATION_->setMaxSurvivalTime(_survivalTime);
    C_GLOBAL_COLABORATION_->setMaxPlayedTime(_survivalTime);
    C_GLOBAL_COLABORATION_->setMaxTimeWithoutPickingHarmfulItems(_timeWithoutPickingUpHarmfulItems);
}

void GameLayer::resetGame()
{
    _player->reset();
    _hBar->reset();

    // resetting initial settings
    _bonusItemInterval = C_BONUS_ITEM_INTERVAL;
    _bonusItemTimer = .00f;
    _harmfulItemInterval = C_HARMFUL_ITEM_INTERVAL;
    _harmfulItemTimer = .00f;
    _bonusItemsPoolIndex = 0;
    _harmfulItemsPoolIndex = 0;
    _itemsListIndex = 0;
    _horizontalBarInterval = C_HORIZONTAL_BAR_INTERVAL;
    _horizontalBarTimer = .00f;
    _killerItemInterval = C_KILLER_ITEM_INTERVAL;
    _killerItemTimer = .00f;
    _superBonusItemInterval = C_SUPER_BONUS_ITEM_INTERVAL;
    _superBonusItemTimer = .00f;
    _gameSpeed = C_INITIAL_GAME_SPEED; // objects will take 6 seconds to traverse the screen
    _survivalTime = 0;
    _playerScore->setString("0");
    _slowMotionItemTimer = .00f;
    _gameAcceleration = C_GAME_ACCELERATION;

    // awards
    _countOfHorizontalBarPassed = 0;
    _bonusItemsConsecutively = 0;
    _harmfulItemsConsecutively = 0;
    _countAwards = 0;
}

void GameLayer::createBonusItem()
{
    Item *item = _bonusItemsPool.at(_bonusItemsPoolIndex);
    _bonusItemsPoolIndex++;
    if (_bonusItemsPoolIndex == _bonusItemsPool.size())
        _bonusItemsPoolIndex = 0;

    placeItemOnTheScreen(*item);
    _itemsList.pushBack(item);
}

void GameLayer::createHarmfulItem()
{
    Item *item = _harmfulItemsPool.at(_harmfulItemsPoolIndex);
    _harmfulItemsPoolIndex++;
    if (_harmfulItemsPoolIndex == _harmfulItemsPool.size())
        _harmfulItemsPoolIndex = 0;

    placeItemOnTheScreen(*item);
    _itemsList.pushBack(item);
}

void GameLayer::createSuperBonusItem()
{
    placeItemOnTheScreen(*_superBonusItem);
    _itemsList.pushBack(_superBonusItem);
}

void GameLayer::createKillerItem()
{
    placeItemOnTheScreen(*_killerItem);
    _itemsList.pushBack(_killerItem);
}

void GameLayer::createSlowMotionItem()
{
    placeItemOnTheScreen(*_slowMotionItem);
    _itemsList.pushBack(_slowMotionItem);
}

void GameLayer::createTurboItem()
{
    placeItemOnTheScreen(*_turboItem);
    _itemsList.pushBack(_turboItem);
}

// returns the X position for the placed item
void GameLayer::placeItemOnTheScreen(Item& item)
{
    int startingPointX = 0;
    bool availablePosition = false;
    float itemWidth = item.getContentSize().width;

    //calculating available point in order to avoid collisions with another items
    while (!availablePosition)
    {
        startingPointX = itemWidth + rand() % (int)(_visibleSize.width - itemWidth - itemWidth * .5f);
        if (isPositionAvailable(startingPointX))
        {
            item.setPosition(cocos2d::Point(startingPointX, C_SCREEN_START_POINT_Y));
            item.setVisible(true);
            availablePosition = true;
        }
    }

    // setting the action for the item
    item.runAction(createItemMovement( (C_SCREEN_START_POINT_Y - C_SCREEN_END_POINT_Y) / _gameSpeed, startingPointX));
}
