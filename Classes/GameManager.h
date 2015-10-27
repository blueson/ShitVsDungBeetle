//
//  GameManager.h
//  ShitVsDungBeetle
//
//  Created by gjmac-2 on 15/10/27.
//
//

#ifndef GameManager_h
#define GameManager_h

#include "cocos2d.h"
#include "EnemyBase.h"
#include "TowerBase.h"
#include "GroupEnemy.h"

USING_NS_CC;

class GameManager {
public:
    static GameManager* getInstance();
    Vector<EnemyBase*> enemyVector;
    Vector<TowerBase*> towerVector;
    Vector<Sprite*> bulletVector;
    Vector<GroupEnemy*> groupVector;
private:
    static GameManager* instance;
};

#endif /* GameManager_h */
