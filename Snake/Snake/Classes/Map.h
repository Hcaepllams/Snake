//
//  Map.h
//  Snake
//
//  Created by 陶 然景 on 13-4-11.
//
//

#ifndef __Snake__Map__
#define __Snake__Map__

#include "cocos-ext.h"
#include "cocos2d.h"

#include "Snake.h"


USING_NS_CC;
USING_NS_CC_EXT;

class Astar;

class Map: public CCLayer {
public:
    Map();
    ~Map();
    
    CREATE_FUNC(Map);
    virtual bool init();
    
    CCSize getMapSize();
    bool checkMap(int x, int y);
    
    void mapUpdate(float dt);
    
    Astar *m_pAStar;
    
    CCPoint m_pointTarget;
    
    void genNewTarget();
    int getAvilablePositionCount();
    
CC_SYNTHESIZE(int, m_iWidth, Width);
CC_SYNTHESIZE(int, m_iHeight, Height);
CC_SYNTHESIZE_RETAIN(Snake*, m_pSnake, Snake);
CC_SYNTHESIZE_RETAIN(CCSprite*, m_pTarget, Target);

};

#endif /* defined(__Snake__Map__) */
