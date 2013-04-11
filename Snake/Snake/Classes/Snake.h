//
//  Snake.h
//  Snake
//
//  Created by 陶 然景 on 13-4-11.
//
//

#ifndef __Snake__Snake__
#define __Snake__Snake__

#include "cocos-ext.h"
#include "cocos2d.h"

USING_NS_CC;
USING_NS_CC_EXT;

class Snake: public CCLayer {
public:
    Snake();
    ~Snake();
    
    CREATE_FUNC(Snake);
    virtual bool init();

    CC_SYNTHESIZE_RETAIN(CCArray*, m_pSnakeBody, SnakeBody);
    
    void refreshSnake();
    
    bool moveToTarget(int nextMoveX, int nextMoveY, int targetX, int targetY);
    bool isPointInBody(CCPoint p);
};

#endif /* defined(__Snake__Snake__) */
