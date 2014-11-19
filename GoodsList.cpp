#include "GoodsList.h"
#include <iostream>
#include <string>

GoodsList::GoodsList()
{
  
}

GoodsList::~GoodsList()
{
  m_goodsList.clear();
}

void GoodsList::addGood(Good item)
{
  m_goodsList.push_front(item);
}

void GoodsList::removeGood(Good item)
{
  m_goodsList.remove(item);
}

void GoodsList::displayGoods()
{
  std::list<Good>::iterator iter;
  for (iter = m_goodsList.begin(); iter != m_goodsList.end(); ++iter)
  {
    std::cout << (*iter).m_goodID << "\t"
              << (*iter).m_goodName << "\t"
              << (*iter).m_quantity << "\t"
              << (*iter).m_price << std::endl;
  }
}
