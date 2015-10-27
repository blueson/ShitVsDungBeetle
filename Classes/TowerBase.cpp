//
//  TowerBase.cpp
//  ShitVsDungBeetle
//
//  Created by gjmac-2 on 15/10/26.
//
//

#include "TowerBase.h"
#include "GameManager.h"

TowerBase::TowerBase(){
    
}

bool TowerBase::init(){
    if (!Node::init()) {
        return false;
    }
    
    return true;
}

void TowerBase::checkNearestEnemy(){
    auto gameManager = GameManager::getInstance();
    auto enemyVector = gameManager->enemyVector;
    
    auto currMinDistant = this->scope;
    EnemyBase* enemyTemp = NULL;
    for (int i =0; i<enemyVector.size(); i++) {
        auto enemy = enemyVector.at(i);
        auto distance = this->getPosition().getDistance(enemy->getPosition());
        if (distance < currMinDistant) {
            currMinDistant = distance;
            enemyTemp = enemy;
        }
    }
    nearestEnemy = enemyTemp;
}