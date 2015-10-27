//
//  TowerPanleLayer.h
//  ShitVsDungBeetle
//
//  Created by gjmac-2 on 15/10/27.
//
//

#ifndef TowerPanleLayer_h
#define TowerPanleLayer_h

#include "cocos2d.h"

USING_NS_CC;

typedef enum {
    ARROW_TOWER = 0,
    ATTACK_TOWER,
    MULTIDIR_TOWER,
    ANOTHER
} TowerType;

class TowerPanleLayer: public Layer{
public:
    TowerPanleLayer();
    virtual bool init() override;
    CREATE_FUNC(TowerPanleLayer);
    bool onTouchBegan(Touch *touch,Event *event);
    void onTouchEnded(Touch *touch,Event *event);
    
    CC_SYNTHESIZE(TowerType, chooseTowerType, ChooseTowerType);
    
private:
    Sprite* sprite1;
    Sprite* sprite2;
    Sprite* sprite3;
};

#endif /* TowerPanleLayer_h */
