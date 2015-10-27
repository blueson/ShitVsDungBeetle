//
//  GroupEnemy.cpp
//  ShitVsDungBeetle
//
//  Created by gjmac-2 on 15/10/27.
//
//

#include "GroupEnemy.h"

GroupEnemy* GroupEnemy::initGroupEnemy(int typeTotal, int typeHp){
    this->typeTotal = typeTotal;
    this->typeHp = typeHp;
    this->enemyTotal = typeTotal;
    
    this->isFinishedAddGroup = false;
    return this;
}