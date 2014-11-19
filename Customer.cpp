#include "Customer.h"
#include <iostream>

// Constructor
Customer::Customer()
{
}

// Constructor
// @param customerID: ID for customer
// @param customerName: Name of customer
// @param paymentMethod: Customer's payment method
Customer::Customer(int customerID, std::string customerName, std::string paymentMethod)
{
  m_customerID = customerID;
  m_name = customerName;
  m_paymentMethod = paymentMethod;
}

// Destructor
Customer::~Customer()
{
}

// Sends order to retailer
// @param itemName: Name of item being ordered
// @param quantity: Quantity desired
// @param shop: Retailer to order from
// @param price: [out] Total price for items
// @return returnCode: Enum describing outcome of order
returnCode Customer::selectOrder(std::string itemName, int quantity, Retailer& shop, double& price)
{
  return(shop.acceptOrder(itemName, quantity, price));
}

// Send payment to retailer
// @param payment: Amount being paid
// @param shop: Retailer to send payment to
// @param itemName: Item being paid for
// @param quantity: Number being paid for
// @return bool: True if payment was accepted, false otherwise
bool Customer::makePayment(double payment, Retailer& shop, std::string itemName, int quantity)
{
  return(shop.acceptPayment(payment, itemName, quantity)); 
}

// Display retailers contact info
// @param shop: Retailer to display info for
void Customer::contactRetailer(Retailer& shop)
{
  std::cout << shop.m_name << std::endl;
  std::cout << "Phone: " << shop.m_phoneNumber << std::endl;
  std::cout << "Email: " << shop.m_email << std::endl;
}

// Display goods that retailer is selling
// @param shop: Retailer to view goods from
void Customer::viewGoods(Retailer& shop)
{
  std::list<Good>::iterator iter = shop.m_inventory.begin();
  for (; iter != shop.m_inventory.end(); iter++) {
    (*iter).displayGood();
    std::cout << std::endl;
  }
}
