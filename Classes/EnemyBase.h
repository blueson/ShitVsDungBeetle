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
    virtual void enemyExpload();
    void createAndSetHpBar();
    
    CC_SYNTHESIZE(int, maxHp, MaxHp);
    CC_SYNTHESIZE(int, currHp, CurrHp);
    CC_SYNTHESIZE(float, hpPercentage, HpPercentage);
    CC_SYNTHESIZE_READONLY(ProgressTimer*, hpBar, HpBar);
private:
    Vector<Node*> pointsVector;
protected:
    int pointCounter;
    Animation *animationRight;
    Animation *animationLeft;
    Sprite* hpBgSprite;
    CC_SYNTHESIZE(float, runSpeed, RunSpeed);
};

#endif /* EnemyBase_h */
