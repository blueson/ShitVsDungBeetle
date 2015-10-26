//
//  TowerBase.cpp
//  ShitVsDungBeetle
//
//  Created by gjmac-2 on 15/10/26.
//
//

#include "TowerBase.h"

TowerBase::TowerBase(){
    
}

bool TowerBase::init(){
    if (!Sprite::init()) {
        return false;
    }
    
    return true;
}

void TowerBase::checkNearestEnemy(){
    
}