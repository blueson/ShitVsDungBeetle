//
//  PlayLayer.hpp
//  ShitVsDungBeetle
//
//  Created by gjmac-2 on 15/10/26.
//
//

#ifndef PlayLayer_h
#define PlayLayer_h

#include "cocos2d.h"
#include "TowerBase.h"
#include "TowerPanleLayer.h"
#include "GroupEnemy.h"

USING_NS_CC;

class PlayLayer : public Layer{
public:
    PlayLayer();
    ~PlayLayer();
    virtual bool init() override;
    static Scene* createScene();
    CREATE_FUNC(PlayLayer);
private:
    void initPointsVector();
    void addEnemy();
    bool onTouchBegan(Touch* touch,Event *event);
    void checkAndAddTowerPanle(Vec2 position);
    void addTower();
    void addTowerChoosePanle(Vec2 position);
    Vec2 convertTotileCoord(Vec2 position);
    Vec2 convertToMatrixCoord(Vec2 position);
    void update(float dt);
    void CollisionDetection();
    GroupEnemy* currentGroup();
    GroupEnemy* nextGroup();
private:
    SpriteBatchNode *spriteSheet;
    TMXTiledMap* map;
    TMXLayer* bgLayer;
    TMXObjectGroup* objects;
    Vector<Node*> pointsVector;
    TowerPanleLayer* chooseTowerpanle;
    float offX;
    Vec2 towerPos;
    TowerBase **towerMatrix;
    int money;
    int groupCounter;
};

#endif /* PlayLayer_h */
