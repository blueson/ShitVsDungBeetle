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

USING_NS_CC;

class PlayLayer : public Layer{
public:
    PlayLayer();
    ~PlayLayer();
    virtual bool init() override;
    static Scene* createScene();
    CREATE_FUNC(PlayLayer);
private:
    SpriteBatchNode *spriteSheet;
    TMXTiledMap* map;
    TMXObjectGroup* objects;
    Vector<Node*> pointsVector;
    void initPointsVector(float offX);
    void addEnemy();
};

#endif /* PlayLayer_h */
