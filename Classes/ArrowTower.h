//
//  ArrowTower.hpp
//  ShitVsDungBeetle
//
//  Created by gjmac-2 on 15/10/26.
//
//

#ifndef ArrowTower_h
#define ArrowTower_h

#include "TowerBase.h"

class ArrowTower : public TowerBase{
public:
    virtual bool init();
    CREATE_FUNC(ArrowTower)
    
    void rotateAndShoot(float dt);
    Sprite* ArrowTowerBullet();
    void shoot();
    void removeBullet(Node* pSender);
    
private:
    Sprite* rotateArrow;
};

#endif /* ArrowTower_h */
