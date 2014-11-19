#ifndef GOOD_H
#define GOOD_H

#include <string>

class Good
{
public:
  Good();
  Good(int goodID, std::string goodName, int quantity, double price);
  ~Good();

  void displayGood();
  bool operator<(const Good& otherGood) const;

  int m_goodID;
  std::string m_goodName;
  int m_quantity;
  double m_price;

};

#endif
