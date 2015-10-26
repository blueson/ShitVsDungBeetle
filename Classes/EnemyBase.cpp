//
//  EnemyBase.cpp
//  ShitVsDungBeetle
//
//  Created by gjmac-2 on 15/10/26.
//
//

#include "EnemyBase.h"

bool EnemyBase::init(){
    if (!Sprite::init()) {
        return false;
    }
    
    return true;
}

Node* EnemyBase::currPoint(){
    return this->pointsVector.at(pointCounter);
}

Node* EnemyBase::nextPoint(){
    int maxCount = this->pointsVector.size();
    pointCounter++;
    if (pointCounter<maxCount) {
        auto node =this->pointsVector.at(pointCounter);
        return node;
    }
    else{
        pointCounter = maxCount - 1;
    }
    
    return NULL;
}

Animation* EnemyBase::createAnimation(std::string prefixName, int framesNum, float delay){
    Vector<SpriteFrame*> animFrames;
    for (int i =1; i<=framesNum; i++) {
        char buffer[20] = { 0 };
        sprintf(buffer, "_%i.png",i);
        std::string str = prefixName + buffer;
        auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
        animFrames.pushBack(frame);
    }
    return Animation::createWithSpriteFrames(animFrames,delay);
}

void EnemyBase::changeDirection(float dt){
    auto curr = currPoint();
    if (curr->getPositionX()> this->getPosition().x) {
        runAction(Animate::create(AnimationCache::getInstance()->getAnimation("runright")));
    }else{
        runAction(Animate::create(AnimationCache::getInstance()->getAnimation("runleft")));
    }
}

void EnemyBase::runFllowPoint(){
    auto point = currPoint();
    setPosition(point->getPosition());
    point= nextPoint();
    if (point!= NULL) {
        runAction(Sequence::create(MoveTo::create(getRunSpeed(), point->getPosition()),
                                   CallFuncN::create(CC_CALLBACK_0(EnemyBase::runFllowPoint, this)), NULL));
    }
}

void EnemyBase::setPointsVector(Vector<cocos2d::Node *> points){
    this->pointsVector = points;
}

