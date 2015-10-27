//
//  TowerPanleLayer.cpp
//  ShitVsDungBeetle
//
//  Created by gjmac-2 on 15/10/27.
//
//

#include "TowerPanleLayer.h"

TowerPanleLayer::TowerPanleLayer(){
    chooseTowerType = ANOTHER;
}

bool TowerPanleLayer::init(){
    if (!Layer::init()) {
        return false;
    }
    
    auto sprite = Sprite::createWithSpriteFrameName("towerPos.png");
    sprite->setPosition(Vec2::ZERO);
    this->addChild(sprite);
    
    sprite2 = Sprite::createWithSpriteFrameName("attackTower.png");
    sprite2->setAnchorPoint(Vec2(0.5f,0));
    sprite2->setPosition(Vec2(0,sprite2->getContentSize().height/2));
    this->addChild(sprite2);
    
    sprite1 = Sprite::createWithSpriteFrameName("ArrowTower1.png");
    sprite1->setAnchorPoint(Vec2(0.5f,0));
    sprite1->setPosition(Vec2(-sprite2->getContentSize().width,sprite2->getPositionY()));
    this->addChild(sprite1);
    
    sprite3 = Sprite::createWithSpriteFrameName("multiDirTower.png");
    sprite3->setAnchorPoint(Vec2(0.5f,0));
    sprite3->setPosition(Vec2(sprite2->getContentSize().width,sprite2->getPositionY()));
    this->addChild(sprite3);
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = CC_CALLBACK_2(TowerPanleLayer::onTouchBegan, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(TowerPanleLayer::onTouchEnded, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, sprite1);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener->clone(), sprite2);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener->clone(), sprite3);

    
    return true;
}

bool TowerPanleLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event){
    auto target = static_cast<Sprite*>(event->getCurrentTarget());
    auto locationInNode = target->convertToNodeSpace(touch->getLocation());
    
    auto size = target->getContentSize();
    auto rect = Rect(0, 0, size.width, size.height);
    if (rect.containsPoint(locationInNode)) {
        target->setOpacity(180);
        return true;
    }
    return false;
}

void TowerPanleLayer::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event){
    auto target = static_cast<Sprite*>(event->getCurrentTarget());
    
    if (target == sprite1) {
        chooseTowerType = ATTACK_TOWER;
    }
    else if(target == sprite2){
        chooseTowerType = ATTACK_TOWER;
    }
    else if(target == sprite3){
        chooseTowerType = ATTACK_TOWER;
    }
    else{
        chooseTowerType = ANOTHER;
    }
}