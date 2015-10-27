//
//  Thief.cpp
//  ShitVsDungBeetle
//
//  Created by gjmac-2 on 15/10/26.
//
//

#include "Thief.h"

bool Thief::init(){
    if (!EnemyBase::init()) {
        return false;
    }
    
    setRunSpeed(6);
    setCurrHp(10);
    setMaxHp(10);
    animationRight = createAnimation("enemyRight1", 4, 0.1f);
    AnimationCache::getInstance()->addAnimation(animationRight, "runright");
    animationLeft = createAnimation("enemyLeft1", 4, 0.1f);
    AnimationCache::getInstance()->addAnimation(animationLeft, "runleft");
    
    auto animationExplode = createAnimation("explode1", 4, 0.1f);
    AnimationCache::getInstance()->addAnimation(animationExplode, "explode1");
    
    schedule(schedule_selector(Thief::changeDirection), 0.4f);
    createAndSetHpBar();
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

void Thief::enemyExpload(){
    hpBgSprite->setVisible(false);
    stopAllActions();
    unschedule(schedule_selector(Thief::changeDirection));
    // 修整爆炸动画的位置，因为它比其他状态都要大
    setAnchorPoint(Point(0.5f, 0.25f));
    runAction(Sequence::create(Animate::create(AnimationCache::getInstance()->getAnimation("explode1"))
                                       ,CallFuncN::create(CC_CALLBACK_0(EnemyBase::removeFromParent, this))
                                       , NULL));
}