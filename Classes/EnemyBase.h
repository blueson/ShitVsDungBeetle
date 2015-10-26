//
//  EnemyBase.hpp
//  ShitVsDungBeetle
//
//  Created by gjmac-2 on 15/10/26.
//
//

#ifndef EnemyBase_h
#define EnemyBase_h

#include "cocos2d.h"

USING_NS_CC;

class EnemyBase : public Sprite{
public:
    virtual bool init() override;
    CREATE_FUNC(EnemyBase);
    Animation* createAnimation(std::string prefixName,int framesNum,float delay);
    void changeDirection(float dt);
    Node* currPoint();
    Node* nextPoint();
    void runFllowPoint();
    void setPointsVector(Vector<Node*> points);
private:
    Vector<Node*> pointsVector;
protected:
    int pointCounter;
    Animation *animationRight;
    Animation *animationLeft;
    CC_SYNTHESIZE(float, runSpeed, RunSpeed);
};

#endif /* EnemyBase_h */
