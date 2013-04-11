//
//  Map.cpp
//  Snake
//
//  Created by 陶 然景 on 13-4-11.
//
//

#include "Map.h"
#include "Astar.h"
#include "Astaritem.h"

Map::Map()
:m_pSnake(NULL)
{
    
}

Map::~Map()
{
    CC_SAFE_RELEASE_NULL(m_pSnake);
}

bool Map::init()
{
    if (!CCLayer::init())
    {
        return false;
    }
    this->setContentSize(CCSizeMake(640, 960));
    
    m_pointTarget = CCPoint(2, 2);
    CCSprite *target = CCSprite::create("target.png");
    target->setPosition(ccp(2 * 50, 2 * 50));
    this->addChild(target);
    
    this->setSnake(Snake::create());
    this->addChild(this->getSnake());
    this->setWidth(50);
    this->setHeight(50);
    
    this->schedule(schedule_selector(Map::mapUpdate), 0.5f);
    return true;
}


CCSize Map::getMapSize()
{
    return CCSizeMake(this->getWidth(), this->getHeight());
}

bool Map::checkMap(int x, int y)
{
    CCObject *obj = NULL;
    CCARRAY_FOREACH(m_pSnake->getSnakeBody(), obj)
    {
        CCPoint *p = (CCPoint*)obj;
        if (p->x == x && p->y == y)
        {
            return false;
        }
    }
    if (x >= this->getWidth() || x < 0)
    {
        return false;
    }
    
    if (y >= this->getWidth() || y < 0)
    {
        return false;
    }
    return true;
}

void Map::mapUpdate(float dt)
{
    CCPoint *head = (CCPoint*)m_pSnake->getSnakeBody()->objectAtIndex(0);
        
    m_pAStar = new Astar();
    CCArray *path = m_pAStar->findPath(head->x, head->y, m_pointTarget.x, m_pointTarget.y, this);
    
    if (path != NULL)
    {
        AstarItem *nextMove = (AstarItem*) path->objectAtIndex(1);
    
        m_pSnake->moveToTarget(nextMove->getcol(), nextMove->getrow(), m_pointTarget.x, m_pointTarget.y);
    }
    
    delete m_pAStar;
}