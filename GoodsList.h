#ifndef GOODSLIST_H
#define GOODSLIST_H

#include <list>
#include "Good.h"


class GoodsList
{
public:
  GoodsList();
  ~GoodsList();

  void addGood(Good item);
  void removeGood(Good item);
  void displayGoods();

private:
  std::list<Good> m_goodsList;
};

#endif
