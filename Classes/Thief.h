//
//  Thief.hpp
//  ShitVsDungBeetle
//
//  Created by gjmac-2 on 15/10/26.
//
//

#ifndef Thief_h
#define Thief_h

#include "cocos2d.h"
#include "EnemyBase.h"


USING_NS_CC;

class Thief : public EnemyBase{
public:
    virtual bool init() override;
    static Thief* createThief(Vector<Node*> points);
};

#endif /* Thief_h */
