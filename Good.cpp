#include <iostream>
#include "Good.h"

Good::Good()
{
  m_goodID = 0;
  m_goodName = "";
  m_quantity = 0;
  m_price = 0;
}

Good::Good(int goodID, std::string goodName, int quantity, double price)
{
  m_goodID = goodID;
  m_goodName = goodName;
  m_quantity = quantity;
  m_price = price;
}

Good::~Good()
{
}

void Good::displayGood()
{
  std::cout << m_goodID << "  "
            << m_goodName << "  "
            << "$" << m_price << "  " 
	    << "Quantity: " << m_quantity << std::endl;
}

bool Good::operator<(const Good& otherGood) const
{
  if (m_price < otherGood.m_price) {
    return true;
  }
  return false;
}
