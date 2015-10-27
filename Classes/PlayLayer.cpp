//
//  PlayLayer.cpp
//  ShitVsDungBeetle
//
//  Created by gjmac-2 on 15/10/26.
//
//

#include "PlayLayer.h"
#include "Thief.h"
#include "GameManager.h"
#include "ArrowTower.h"

#define MAP_WIDTH (16)
#define MAP_HEIGHT (9)

Scene* PlayLayer::createScene(){
    auto scene = Scene::create();
    auto layer = PlayLayer::create();
    scene->addChild(layer);
    return scene;
}

PlayLayer::PlayLayer(){
    chooseTowerpanle = nullptr;
    money = 300;
    groupCounter=0;
}

PlayLayer::~PlayLayer(){
    
}

bool PlayLayer::init(){
    if (!Layer::init()) {
        return false;
    }
    
    auto winSize = Director::getInstance()->getWinSize();
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Play.plist", "Play.png");
    
    map = TMXTiledMap::create("tilemap0.tmx");
    
    bgLayer = map->getLayer("bg");
    bgLayer->setAnchorPoint(Vec2(0.5f,0.5f));
    bgLayer->setPosition(Vec2(winSize.width/2,winSize.height/2));
    
    objects = map->getObjectGroup("obj");
    this->addChild(map,-1);
    offX = (map->getContentSize().width - winSize.width) / 2;
    initPointsVector();
    
    addEnemy();
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(PlayLayer::onTouchBegan,this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    int arraySize = sizeof(TowerBase *) * MAP_WIDTH * MAP_HEIGHT;
    towerMatrix = (TowerBase **)malloc(arraySize);
    memset((void*)towerMatrix, 0, arraySize);
    
    for (int row = 0; row < MAP_HEIGHT; row++) {
        for (int col = 0; col < MAP_WIDTH; col++) {
            towerMatrix[row * MAP_WIDTH + col] = NULL;
        }
    }
    
    scheduleUpdate();
    
    return true;
}

void PlayLayer::initPointsVector(){
    Node *runOfPoint = NULL;
    int count = 0;
    ValueMap point;
    point = objects->getObject(std::to_string(count));
    while (point.begin() != point.end()) {
        float x = point.at("x").asFloat();
        float y = point.at("y").asFloat();
        
        runOfPoint = Node::create();
        runOfPoint->setPosition(Vec2(x- offX, y));
        this->pointsVector.pushBack(runOfPoint);
        count++;
        point = objects->getObject(std::to_string(count));
    }
    runOfPoint = NULL;
}

void PlayLayer::addEnemy(){
    auto thief = Thief::createThief(this->pointsVector);
    GameManager::getInstance()->enemyVector.pushBack(thief);
    this->addChild(thief,10);
}

bool PlayLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event){
    if (chooseTowerpanle != nullptr) {
        chooseTowerpanle->removeFromParent();
        chooseTowerpanle = nullptr;
    }
    auto location = touch->getLocation();
    checkAndAddTowerPanle(location);
    return true;
}

void PlayLayer::checkAndAddTowerPanle(cocos2d::Vec2 position){
    auto towerCoord = convertTotileCoord(position);
    auto matrixCoord = convertToMatrixCoord(position);
    
    int gid = bgLayer->getTileGIDAt(towerCoord);
    auto titleTemp = map->getPropertiesForGID(gid);
    int TouchValue;
    int MatrixIndex = static_cast<int>(matrixCoord.y * MAP_WIDTH + matrixCoord.x);
    if (titleTemp.isNull()) {
        TouchValue = 0;
    }else{
        TouchValue = titleTemp.asValueMap().at("canTouch").asInt();
    }
    auto tileWidth = map->getContentSize().width/ map->getMapSize().width;
    auto tileHeight = map->getContentSize().height/map->getMapSize().height;
    
    towerPos = Vec2((towerCoord.x * tileWidth)+tileWidth/2 - offX,map->getContentSize().height - (towerCoord.y * tileHeight) - tileHeight/2);
    
    if (1 == TouchValue && towerMatrix[MatrixIndex] == NULL) {
        addTowerChoosePanle(towerPos);
    }else{
        auto tips = Sprite::createWithSpriteFrameName("no.png");
        tips->setPosition(towerPos);
        this->addChild(tips);
        tips->runAction(Sequence::create(DelayTime::create(0.8f),
                                         CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, tips)), NULL));
    }
}

void PlayLayer::addTowerChoosePanle(cocos2d::Vec2 position){
    chooseTowerpanle = TowerPanleLayer::create();
    chooseTowerpanle->setPosition(position);
    this->addChild(chooseTowerpanle);
}

void PlayLayer::addTower(){
    if (chooseTowerpanle != nullptr) {
        auto type = chooseTowerpanle->getChooseTowerType();
        if (type == TowerType::ANOTHER) {
            return;
        }

        auto matrixCoord = convertToMatrixCoord(towerPos);
        int MatrixIndex = static_cast<int>(matrixCoord.y * MAP_WIDTH + matrixCoord.x);
        bool noMoneyTips = false;
        TowerBase* tower = NULL;
        if (type == TowerType::ARROW_TOWER) {
            if (money >= 200) {
                tower = ArrowTower::create();
                money -= 200;
            }else{
                noMoneyTips = true;
            }
        }else if(type == TowerType::ATTACK_TOWER){
            if (money >= 200) {
                tower = ArrowTower::create();
                money -= 200;
            }else{
                noMoneyTips = true;
            }

        }else if(type == TowerType::MULTIDIR_TOWER){
            if (money >= 200) {
                tower = ArrowTower::create();
                money -= 200;
            }else{
                noMoneyTips = true;
            }
            
        }

        if (tower != NULL) {
            tower->setPosition(towerPos);
            tower->runAction(Sequence::create(FadeIn::create(1.0f), NULL));
            this->addChild(tower);
            GameManager::getInstance()->towerVector.pushBack(tower);
            towerMatrix[MatrixIndex] = tower;
        }

        type = TowerType::ANOTHER;
        chooseTowerpanle->setChooseTowerType(type);
        this->removeChild(chooseTowerpanle);
        chooseTowerpanle = nullptr;
        if (noMoneyTips == true) {
            auto tips = Sprite::createWithSpriteFrameName("nomoney_mark.png");
            tips->setPosition(towerPos);
            this->addChild(tips);
            tips->runAction(Sequence::create(DelayTime::create(0.5f),
                                             CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, tips)), NULL));
        }
    }
}

void PlayLayer::update(float dt){
    if (chooseTowerpanle != nullptr) {
        addTower();
    }
    CollisionDetection();
}

void PlayLayer::CollisionDetection(){
    auto gameManager = GameManager::getInstance();
    auto bulletVector = gameManager->bulletVector;
    auto enemyVector = gameManager->enemyVector;
    if (bulletVector.empty() || enemyVector.empty()) {
        return;
    }
    
    Vector<EnemyBase*> enemyNeedToDelete;
    Vector<Sprite*> bulletNeedToDelete;
    
    for (int i = 0; i < bulletVector.size(); i++)
    {
        auto  bullet = bulletVector.at(i);
        auto  bulletRect = Rect(bullet->getPositionX()+bullet->getParent()->getPositionX()-bullet->getContentSize().width/2,
                                bullet->getPositionY()+bullet->getParent()->getPositionY()-bullet->getContentSize().height/2,
                                bullet->getContentSize().width,
                                bullet->getContentSize().height );
        for (int j = 0; j < enemyVector.size(); j++)
        {
            auto enemy = enemyVector.at(j);
            auto enemyRect = enemy->getBoundingBox();
            if (bulletRect.intersectsRect(enemyRect))
            {
                auto currHp = enemy->getCurrHp();
                currHp--;
                enemy->setCurrHp( currHp );
                auto currHpPercentage = enemy->getHpPercentage();
                auto offHp = 100 / enemy->getMaxHp();
                currHpPercentage -= offHp;
                
                if(currHpPercentage < 0){
                    currHpPercentage = 0;
                }
                enemy->setHpPercentage(currHpPercentage);
                enemy->getHpBar()->setPercentage(currHpPercentage);
                if(currHp <= 0)
                {
                    enemyNeedToDelete.pushBack(enemy);
                }
                bulletNeedToDelete.pushBack( bullet);
                break;
            }
        }
        for (EnemyBase* enemyTemp : enemyNeedToDelete)
        {
            enemyTemp->enemyExpload();
            gameManager->enemyVector.eraseObject(enemyTemp);
        }
        enemyNeedToDelete.clear();
    }
    for (const auto& bulletTemp : bulletNeedToDelete)
    {
        gameManager->bulletVector.eraseObject(bulletTemp);
        bulletTemp->removeFromParent();
    }
    bulletNeedToDelete.clear();
}

Vec2 PlayLayer::convertTotileCoord(cocos2d::Vec2 position){
    int x = (position.x + offX) / map->getContentSize().width * map->getMapSize().width;
    int y = map->getMapSize().height - position.y / map->getContentSize().height * map->getMapSize().height;
    
    return Vec2(x,y);
}

Vec2 PlayLayer::convertToMatrixCoord(cocos2d::Vec2 position){
    int x = (position.x + offX)/ map->getContentSize().width * map->getMapSize().width;
    int y = position.y / map->getContentSize().height * map->getMapSize().height;
    return Vec2(x,y);
}

