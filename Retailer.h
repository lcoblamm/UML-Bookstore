#ifndef RETAILER_H
#define RETAILER_H

#include <list>
#include <string>
#include "Good.h"
#include "Supplier.h"
#include "Enums.h"

class Retailer
{
public:
  Retailer(std::string retailerName, std::string phone, std::string email, Supplier* supplier);
  ~Retailer();
  
  void addGood(Good item);
  bool acceptPayment(double payment, std::string goodName, int quantity);
  returnCode acceptOrder(std::string goodName, int quantity, double& price);
  returnCode orderGoods(std::string goodName, int quantity, double price);
  returnCode updateGoods(bool bAdding, std::string goodName, int quantityChanged);
  void arrangeGoods();
  bool makePayment(double payment);
    
  std::list<Good> m_inventory;
  std::string m_name;
  std::string m_phoneNumber;
  std::string m_email;
  double m_balance;

private:
  bool checkStock(std::string goodName, int quantityDesired, int& numNeeded);
  double getPrice(std::string goodName);

  Supplier* m_supplier;
};

#endif
