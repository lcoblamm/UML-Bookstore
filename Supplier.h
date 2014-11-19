#ifndef SUPPLIER_H
#define SUPPLIER_H

#include <list>
#include <string>
#include "Good.h"
#include "Enums.h"

class Supplier
{
public:
  Supplier();
  Supplier(int supplierID);
  ~Supplier();

  bool acceptPayment(double payment);
  void addGood(Good item);
  returnCode removeGood(std::string goodName);
  returnCode updateGood(bool bAdding, std::string goodName, int quantity);
  returnCode acceptOrder(std::string goodName, int quantity);

  std::list<Good> m_inventory;
  int m_supplierID;

  double m_balance;
private:
  returnCode checkStock(std::string goodName, int quantityDesired);

  //double m_balance;
};

#endif
