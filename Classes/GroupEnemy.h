//
//  GroupEnemy.h
//  ShitVsDungBeetle
//
//  Created by gjmac-2 on 15/10/27.
//
//

#ifndef GroupEnemy_h
#define GroupEnemy_h

#include "cocos2d.h"

USING_NS_CC;

class GroupEnemy : public Node{
public:
    virtual bool init();
    GroupEnemy* initGroupEnemy(int typeTotal,int typeHp);
    CREATE_FUNC(GroupEnemy);
    
    CC_SYNTHESIZE(int, typeTotal, TypeTotal);
    CC_SYNTHESIZE(int, typeHp, TypeHp);
    CC_SYNTHESIZE(int, enemyTotal, EnemyTotal);
    CC_SYNTHESIZE(bool, isFinishedAddGroup, IsFinishedAddGroup);
};

#endif /* GroupEnemy_h */
