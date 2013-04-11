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
,m_pTarget(NULL)
{
    
}

Map::~Map()
{
    CC_SAFE_RELEASE_NULL(m_pSnake);
    CC_SAFE_RELEASE_NULL(m_pTarget);
}

bool Map::init()
{
    if (!CCLayer::init())
    {
        return false;
    }
    this->setContentSize(CCSizeMake(640, 960));
    
    m_pointTarget = CCPoint(2, 2);
    this->setTarget(CCSprite::create("snake.png"));
    this->getTarget()->setPosition(ccp(m_pointTarget.x * 25, m_pointTarget.y * 25));
    this->addChild(this->getTarget());
    
    this->setSnake(Snake::create());
    this->addChild(this->getSnake());
    this->setWidth(10);
    this->setHeight(10);
    
    this->schedule(schedule_selector(Map::mapUpdate), 0.3f);
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
    
        if (m_pSnake->moveToTarget(nextMove->getcol(), nextMove->getrow(), m_pointTarget.x, m_pointTarget.y))
        {
            genNewTarget();
        }
    }
    
    delete m_pAStar;
}

void Map::genNewTarget()
{
    srand(time(NULL));
    int index = random() % getAvilablePositionCount();
    
    int count = 0;
    for (int x = 0; x < this->getWidth(); x ++)
    {
        for (int y = 0; y < this->getHeight(); y ++)
        {
            if (m_pSnake->isPointInBody(ccp(x, y)))
            {
                continue;
            }
            else
            {
                if (count == index)
                {
                    m_pointTarget.x = x;
                    m_pointTarget.y = y;
                }
            }
            count ++;
        }
    }
    this->getTarget()->setPosition(ccp(m_pointTarget.x * 25, m_pointTarget.y * 25));
}

int Map::getAvilablePositionCount()
{
    return this->getWidth() * this->getHeight() - m_pSnake->getSnakeBody()->count();
}