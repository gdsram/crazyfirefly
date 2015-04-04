#ifndef CRAZYFIREFLY_SCENE_GAMELAYER_H_
#define CRAZYFIREFLY_SCENE_GAMELAYER_H_

#include <vector>
#include "cocos2d.h"

#include "app_macros.h"
#include "award_container.h"
#include "items/horizontal_bar.h"
#include "items/item.h"
#include "items/player.h"
#include "items/health.h"

enum awardImagePath{
    kAwardTimeWithoutPickingUpHarmfulItems,
    kAwardBonusItemConsecutively,
    kAwardCountOfHorizontalBarPassed,
    kAwardCountAwards,
    kAwardSurvivalTime
};

// gamelayer's constants
const float C_GAME_ACCELERATION = 9.81f;
const float C_BONUS_ITEM_INTERVAL = 1.25f;
const float C_MAX_BONUS_ITEM_INTERVAL = 3.5f;
const float C_BONUS_ITEM_INTERVAL_VARYING_FACTOR = .10f;

const float C_HARMFUL_ITEM_INTERVAL = 2.5f;
const float C_MIN_HARMFUL_ITEM_INTERVAL = 1.5f;
const float C_HARMFUL_ITEM_INTERVAL_VARYING_FACTOR = .15f;

const float C_KILLER_ITEM_INTERVAL = 20.0f;
const float C_MIN_KILLER_ITEM_INTERVAL = 10.0f;
const float C_KILLER_ITEM_INTERVAL_VARYING_FACTOR = .05f;

const float C_SUPER_BONUS_ITEM_INTERVAL = 15.0f;
const float C_MAX_SUPER_BONUS_CALL_ITEM_INTERVAL = 20.0f;
const float C_SUPER_BONUS_ITEM_INTERVAL_VARYING_FACTOR = .05f;

const float C_BEER_ITEM_INTERVAL = 15.00f;

const float C_DIFFICULTY_GAME_INTERVAL = 5.0f;

const float C_PLAYER_SPEED_FACTOR = 1.50f;

const short int C_MAX_COUNT_HARMFUL_ITEM = 7; // max number of harmful item that can appear in the screen at the same time
const short int C_MAX_COUNT_BONUS_ITEM = 3; // max number of bonus item that can appear in the screen at the same time

// constants of horizontal bar
const float C_HORIZONTAL_BAR_INTERVAL = 3.0f;
const float C_MIN_HORIZONTAL_BAR_INTERVAL = 8.0f;
const float C_HORIZONTAL_BAR_INTERVAL_VARYING_FACTOR = .05f;
const float C_GAP_REDUCTION_FACTOR = .98f;

// items' constants
const float C_BONUS_SIZE_MODIFICATOR_FACTOR = 0.707106781f;
const short int C_BONUS_ENERGY_MODIFICATOR_VALUE = 3;
const short int C_FOOTBALL_ITEM_PLUS_SCORE = 3;

const float C_HARMFUL_ITEM_SIZE_MODIFICATOR_FACTOR = 1.41421356237f;
const short int C_HARMFUL_ITEM_ENERGY_MODIFICATOR_VALUE = -5;
const short int C_BOSS_ITEM_PLUS_SCORE = 1;

const float C_PARTY_ITEM_INTERVAL = 8.0f;//MAX(C_KILLER_ITEM_INTERVAL, C_SUPER_BONUS_ITEM_INTERVAL);

const short int C_FACEBOOK_ITEM_STRESS_MODIFICATOR_VALUE = -10;

const short int C_TWITTER_ITEM_STRESS_MODIFICATOR_VALUE = 10;

//player's constants
const float C_PLAYER_MIN_SCALE = 1.00f;
const float C_PLAYER_MAX_SCALE = 2.00f;

class GameLayer : public cocos2d::Layer
{
public:
    GameLayer();
    ~GameLayer() = default;

    static cocos2d::Scene* createScene();
    virtual bool init();

    // setting up touch events
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event * event);
    void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event * event);
    void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event * event);

    // setting up accelerometer
    void onAcceleration(cocos2d::Acceleration *acc, cocos2d::Event *event);

    void goToPauseScene(Ref *pSender);
    void goToGameOverScene();

    void update (float dt);

    CREATE_FUNC(GameLayer)

private:
    void initGameScreen();

    void initMenu();
    void initAudio();
    void initBackGround();
    void initPlayer();
    void initHorizontalBar();
    void initLabels();
    void initAwardMessages();
    void initEventListener();
    void initItems();

    void updateTimers(float dt);
    void updateGameSpeed(float speed);
    void updateGameLabels();
    void updateAwardsTimers(float dt);
    void increaseDifficulty();

    void showHorizontalBar();
    void scrollBackground(float dt);

    void checkForPickingUps();
    void checkForPlayerCollisions();
    void checkForPlayerCollisionsWithHBar(float playerRadius);
    void checkForGameOver();

    cocos2d::FiniteTimeAction *createItemMovement(float duration, float toX);
    cocos2d::FiniteTimeAction* createHorizontalBarMovement(float duration);

    bool isPositionAvailable(int startingPositionX) const; // returns true if position x is not being used by another item
    bool isAnyItemAtTop() const; // returns true if there is any item at the top of the screen
    bool isHBarAtTop() const; // returns true if the horizontal bar is at the top of the screen

    void saveScore();
    void resetGame();

    void createBonusItem();
    void createHarmfulItem();
    void createSuperBonusItem();
    void createKillerItem();
    void createSlowMotionItem();
    void createTurboItem();
    void placeItemOnTheScreen(Item& item);

    // class members

    const float C_INITIAL_GAME_SPEED = cocos2d::Director::getInstance()->getVisibleSize().height / 3.00f;
    const float C_GAME_SPEED_VARYING_FACTOR = .075f;
    const float C_MAX_GAME_SPEED = cocos2d::Director::getInstance()->getVisibleSize().height / 0.90f;

    // items and horizontal bar will start from this point
    const float C_SCREEN_START_POINT_Y = cocos2d::Director::getInstance()->getVisibleSize().height * 1.1f;
    // items and horizontal bar will stop moving at this point
    const float C_SCREEN_END_POINT_Y = cocos2d::Director::getInstance()->getVisibleSize().height * -0.1f;

    bool _isTouching;
    bool _freezeItems;
    float _touchPosition;

    cocos2d::Size _visibleSize;
    cocos2d::Point _origin;

    // timers
    float _bonusItemInterval;
    float _bonusItemTimer;
    float _harmfulItemInterval;
    float _harmfulItemTimer;
    float _killerItemInterval;
    float _killerItemTimer;
    float _superBonusItemInterval;
    float _superBonusItemTimer;
    float _horizontalBarInterval;
    float _horizontalBarTimer;
    float _gameDifficultyTimer;
    float _gameTimer;
    float _slowMotionItemInterval;
    float _slowMotionItemTimer;
    float _turboItemTimer;
    float _turboItemInterval;
    float _gameSpeed;
    float _gameAcceleration;

    // awards
    float _timeWithoutPickingUpHarmfulItems;
    int _bonusItemsConsecutively; // count of bonus items that have been picked up consecutively
    int _harmfulItemsConsecutively; // count of harmful items that have been picked up consecutively
    int _countOfHorizontalBarPassed;
    int _countAwards;
    int _survivalTime;

    cocos2d::Vector<cocos2d::Sprite*> _backgroundSpriteVector;
    HorizontalBar *_hBar;
    Player *_player;
    AwardContainer* _awardContainer;

    // labels
    cocos2d::Label* _playerScore;
    cocos2d::Sprite* _scoreTextSprite;
    Health* _healthSprite;

    // items
    Item* _killerItem;
    Item* _superBonusItem;
    Item* _turboItem;
    Item* _surpriseItem;
    Item* _slowMotionItem; // slow the game's speed temporaly
    cocos2d::Vector<Item*> _turboItemsPool;

    cocos2d::Vector<Item*> _bonusItemsPool;
    short int _bonusItemsPoolIndex;

    cocos2d::Vector<Item*> _harmfulItemsPool;
    short int _harmfulItemsPoolIndex;

    cocos2d::Vector<Item*> _itemsList;
    short int _itemsListIndex;
};

#endif // CRAZYFIREFLY_SCENE_GAMELAYER_H_
