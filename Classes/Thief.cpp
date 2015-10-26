//
//  Thief.cpp
//  ShitVsDungBeetle
//
//  Created by gjmac-2 on 15/10/26.
//
//

#include "Thief.h"

bool Thief::init(){
    if (!Sprite::init()) {
        return false;
    }
    
    setRunSpeed(6);
    animationRight = createAnimation("enemyRight1", 4, 0.1f);
    AnimationCache::getInstance()->addAnimation(animationRight, "runright");
    animationLeft = createAnimation("enemyLeft1", 4, 0.1f);
    AnimationCache::getInstance()->addAnimation(animationLeft, "runleft");
    
    schedule(schedule_selector(EnemyBase::changeDirection), 0.4f);
    
    return true;
}

Thief* Thief::createThief(Vector<cocos2d::Node *> points){
    auto pRet = new Thief();
    
    if (pRet && pRet->init()) {
        pRet->setPointsVector(points);
        pRet->runFllowPoint();
        pRet->autorelease();
        return pRet;
    }
    else{
        CC_SAFE_DELETE(pRet);
        pRet = NULL;
        return NULL;
    }
}