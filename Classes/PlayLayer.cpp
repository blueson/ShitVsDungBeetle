//
//  PlayLayer.cpp
//  ShitVsDungBeetle
//
//  Created by gjmac-2 on 15/10/26.
//
//

#include "PlayLayer.h"
#include "Thief.h"

Scene* PlayLayer::createScene(){
    auto scene = Scene::create();
    auto layer = PlayLayer::create();
    scene->addChild(layer);
    return scene;
}

PlayLayer::PlayLayer(){
    
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
    
    auto bgLayer = map->getLayer("bg");
    bgLayer->setAnchorPoint(Vec2(0.5f,0.5f));
    bgLayer->setPosition(Vec2(winSize.width/2,winSize.height/2));
    
    objects = map->getObjectGroup("obj");
    this->addChild(map,-1);
    
    initPointsVector((map->getContentSize().width - winSize.width) / 2);
    
    addEnemy();
    
    return true;
}

void PlayLayer::initPointsVector(float offX){
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
    this->addChild(thief);
}

