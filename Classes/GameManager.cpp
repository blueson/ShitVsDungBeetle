//
//  GameManager.cpp
//  ShitVsDungBeetle
//
//  Created by gjmac-2 on 15/10/27.
//
//

#include "GameManager.h"

GameManager* GameManager::instance;

GameManager* GameManager::getInstance(){
    if (instance == NULL) {
        instance = new GameManager();
    }
    return instance;
}