//
//  Snake.cpp
//  Snake
//
//  Created by 陶 然景 on 13-4-11.
//
//

#include "Snake.h"

Snake::Snake()
:m_pSnakeBody(NULL)
{
    
}

Snake::~Snake()
{
    CC_SAFE_RELEASE_NULL(m_pSnakeBody);
}


bool Snake::init()
{
    if (!CCLayer::init())
    {
        return false;
    }
    
    this->setContentSize(CCSizeMake(640, 960));
    
    this->setSnakeBody(CCArray::create());
    
    
    m_pSnakeBody->addObject(new CCPoint(7, 8));
    m_pSnakeBody->addObject(new CCPoint(7, 9));
    m_pSnakeBody->addObject(new CCPoint(7, 10));
    m_pSnakeBody->addObject(new CCPoint(7, 11));
    m_pSnakeBody->addObject(new CCPoint(7, 12));
    this->refreshSnake();
    return true;
}

void Snake::refreshSnake()
{
    this->removeAllChildrenWithCleanup(true);
    
    CCObject *obj = NULL;
    CCARRAY_FOREACH(m_pSnakeBody, obj)
    {
        CCPoint *point = (CCPoint*)obj;
        CCSprite* pSprite = CCSprite::create("Icon-Small-50.png");
        float gapX = pSprite->getContentSize().width;
        float gapY = pSprite->getContentSize().height;
        pSprite->setPosition(ccp(point->x * gapX, point->y * gapY));
        this->addChild(pSprite);
    }
}

void Snake::moveToTarget(int nextMoveX, int nextMoveY, int targetX, int targetY)
{
    CCPoint *p = new CCPoint(nextMoveX, nextMoveY);
    m_pSnakeBody->insertObject(p, 0);
    
    if (nextMoveX == targetX && nextMoveY == targetY) // Hit the target!
    {
        //Do nothing.
        CCLog ("NEW");
    }
    else
    {
        // Remove Tail.
        m_pSnakeBody->removeLastObject();
    }
    
    this->refreshSnake();
}