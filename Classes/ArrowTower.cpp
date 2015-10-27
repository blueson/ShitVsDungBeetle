//
//  ArrowTower.cpp
//  ShitVsDungBeetle
//
//  Created by gjmac-2 on 15/10/26.
//
//

#include "ArrowTower.h"
#include "GameManager.h"

bool ArrowTower::init(){
    setScope(90);
    setLethality(1);
    setRate(2);
    
    auto baseplate = Sprite::createWithSpriteFrameName("baseplate.png");
    addChild(baseplate);
    
    rotateArrow = Sprite::createWithSpriteFrameName("arrow.png");
    rotateArrow->setPosition(Vec2(0,baseplate->getContentSize().height/4));
    addChild(rotateArrow);
    
    schedule(CC_CALLBACK_1(ArrowTower::rotateAndShoot, this),0.5, "shoot");
    
    return true;
}

void ArrowTower::rotateAndShoot(float dt){
    checkNearestEnemy();
    if (nearestEnemy != NULL) {
        auto rotateVector = nearestEnemy->getPosition() - this->getPosition();
        float rotateradians = rotateVector.getAngle();
        float rotateDegrees = CC_RADIANS_TO_DEGREES(-1 * rotateradians);
        float speed = 0.5 / M_PI;
        float rotateDuration = fabs(rotateradians * speed);
        rotateArrow->runAction(Sequence::create(RotateTo::create(rotateDuration, rotateDegrees),
                                                CallFunc::create(CC_CALLBACK_0(ArrowTower::shoot, this)),NULL));
    }
}

Sprite* ArrowTower::ArrowTowerBullet(){
    auto bullet = Sprite::createWithSpriteFrameName("arrowBullet.png");
    bullet->setPosition(rotateArrow->getPosition());
    bullet->setRotation(rotateArrow->getRotation());
    GameManager::getInstance()->bulletVector.pushBack(bullet);
    addChild(bullet);
    return bullet;
}

void ArrowTower::shoot(){
    auto gameManager = GameManager::getInstance();
    auto bulletVector = gameManager->bulletVector;
    
    if (nearestEnemy != NULL && nearestEnemy->getCurrHp() > 0) {
        auto currBullet = ArrowTowerBullet();
        gameManager->bulletVector.pushBack(currBullet);
        
        auto moveDuration = getRate();
        auto shootVector = nearestEnemy->getPosition() - this->getPosition();
        shootVector.normalize();
        shootVector = -shootVector;
        auto farthestDistance = Director::getInstance()->getWinSize().width;
        auto overshotvector = shootVector * farthestDistance;
        auto offscreenPoint = (rotateArrow->getPosition() - overshotvector);
        
        currBullet->runAction(Sequence::create(MoveTo::create(moveDuration, offscreenPoint)
                                               ,CallFuncN::create(CC_CALLBACK_1(ArrowTower::removeBullet, this)), NULL));
        currBullet = NULL;
    }
}

void ArrowTower::removeBullet(Node* pSender){
    auto gameManager = GameManager::getInstance();
    auto bulletVector = gameManager->bulletVector;
    
    auto sprite = (Sprite*)pSender;
    gameManager->bulletVector.eraseObject(sprite);
    sprite->removeFromParent();
}
