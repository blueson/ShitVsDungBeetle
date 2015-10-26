//
//  TowerBase.hpp
//  ShitVsDungBeetle
//
//  Created by gjmac-2 on 15/10/26.
//
//

#ifndef TowerBase_h
#define TowerBase_h

#include "cocos2d.h"
#include "EnemyBase.h"

USING_NS_CC;

class TowerBase : public Sprite{
public:
    TowerBase();
    virtual bool init();
    CREATE_FUNC(TowerBase);
    void checkNearestEnemy();
    
    CC_SYNTHESIZE(int, scope, Scope);
    CC_SYNTHESIZE(int, lethality, Lethality);
    CC_SYNTHESIZE(float, rate, Rate);
protected:
    EnemyBase* nearestEnemy;
};

#endif /* TowerBase_h */
