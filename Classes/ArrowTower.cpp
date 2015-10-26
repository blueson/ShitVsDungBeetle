//
//  ArrowTower.cpp
//  ShitVsDungBeetle
//
//  Created by gjmac-2 on 15/10/26.
//
//

#include "ArrowTower.h"

bool ArrowTower::init(){
    setScope(90);
    setLethality(1);
    setRate(2);
    
    auto baseplate = Sprite::createWithSpriteFrameName("baseplate.png");
    addChild(baseplate);
    
    rotateArrow = Sprite::createWithSpriteFrameName("arrow.png");
    rotateArrow->setPosition(Vec2(0,baseplate->getContentSize().height/4));
    addChild(rotateArrow);
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
    
}

void ArrowTower::shoot(){
    
}

void ArrowTower::removeBullet(Node* pSender){
    
}
