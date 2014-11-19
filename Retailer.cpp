#include "Retailer.h"

// Constructor
// @param retailerName: Name of retailer
// @param phone: Retailer's phone number
// @param email: Retailer's email address
// @param supplier: Supplier retailer orders from
Retailer::Retailer(std::string retailerName, std::string phone, std::string email, Supplier* supplier)
{
  m_name = retailerName;
  m_phoneNumber = phone;
  m_email = email;
  m_balance = 5000;
  m_supplier = supplier;
}

// Destructor
Retailer::~Retailer()
{
}

// Adds a good to the retailer's inventory
// @param item: Good to add
void Retailer::addGood(Good item)
{
  m_inventory.push_back(item);
}

// Accepts payment from customer & updates the inventory to reflect the number ordered
// @param payment: amount customer is paying
// @param good: Name of good customer ordered
// @param quantity: Number ordered
// @return bool: True if inventory was updated & payment was accepted, false otherwise
bool Retailer::acceptPayment(double payment, std::string good, int quantity)
{
  // try to update inventory
  returnCode updateStatus = updateGoods(false, good, quantity);
  if (updateStatus != SUCCESS) {
    return false;
  }
  // add payment to balance
  m_balance += payment;
  return true;
}

// Checks stock to see if order can be fulfilled & orders more items if needed
// @param goodName: Name of good being ordered
// @param quantity: Number desired
// @param price: [out] price of desired number of items
// @return returnCode: enum value giving info about outcome of order
returnCode Retailer::acceptOrder(std::string goodName, int quantity, double& price)
{
  // get item price & figure out total price
  double indivPrice = getPrice(goodName);
  price = indivPrice * quantity;

  // check if there are enough in stock
  int numToOrder = 0;
  if (checkStock(goodName, quantity, numToOrder)) {
    return SUCCESS;
  }
  // if not, send order to supplier
  else {
    return(orderGoods(goodName, numToOrder, indivPrice));
  }
}

// Attempt to order goods from supplier
// @param goodName: Name of good being ordered
// @param quantity: Quantity desired
// @param supplier: Supplier to order goods from
// @return returnCode: enum value giving info about outcome of order
returnCode Retailer::orderGoods(std::string goodName, int quantity, double price)
{
  returnCode orderStatus = m_supplier->acceptOrder(goodName, quantity);
  if (orderStatus == SUCCESS) {
    // pay supplier
    if (!makePayment(price * quantity)) {
      return ITEM_NOT_AVAILABLE;
    }

    // add goods to inventory
    return updateGoods(true, goodName, quantity);
  }
  return orderStatus;
}

// Update inventory by adding or removing quantity of a given good
// @param bAdding: True if goods are being added to inventory, false if they're being removed (sold)
// @param goodName: Name of good being updated
// @param quantityChange: Number to add/remove from inventory
// @return returnCode: enum value giving info about outcome of update
returnCode Retailer::updateGoods(bool bAdding, std::string goodName, int quantityChange)
{
  std::list<Good>::iterator iter = m_inventory.begin();
  for (; iter != m_inventory.end(); ++iter) {
    if ((*iter).m_goodName == goodName) {
      // update quantity
      if (bAdding) {
        (*iter).m_quantity += quantityChange;
      }
      else {
        (*iter).m_quantity -= quantityChange;
      }

      // exit list
      return SUCCESS;
    }
  }
  // item not found in list
  return ITEM_NOT_FOUND; 
}

// Arranges inventory in order of price
void Retailer::arrangeGoods()
{
  m_inventory.sort();
}

// Sends payment to supplier & deducts from balance
// @param payment: Amonut to pay supplier
// @param supplier: Supplier to send payment to
// @return bool: True if payment was accepted & processed, false otherwise
bool Retailer::makePayment(double payment)
{
  if (m_balance > payment) {
    if (m_supplier->acceptPayment(payment)) {
      m_balance -= payment;
      return true;
    }
  }
  return false;
}

// Checks inventory to see if the desired quantity is in stock & sets price
// @param goodName: Name of good to check
// @param quantityDesired: Number to check for
// @param numNeeded: [out] Total number needed (for ordering from supplier)
// @return bool: True if desired quantity is in stock, false otherwise
bool Retailer::checkStock(std::string goodName, int quantityDesired, int& numNeeded)
{
  std::list<Good>::iterator iter = m_inventory.begin();
  for (; iter != m_inventory.end(); ++iter) {
    if ((*iter).m_goodName == goodName) {
      // check if there's enough
      if ((*iter).m_quantity >= quantityDesired) {
	numNeeded = 0;
        return true;
      }
      else {
	// if there's not enough
	numNeeded = quantityDesired - (*iter).m_quantity;
	return false;
      }
    }
  }
  // if the item wasn't found
  numNeeded = quantityDesired;
  return false;
} 

// Get price for specified good
// @param goodName: Name of good to get price for
// @return double: price of item
double Retailer::getPrice(std::string goodName) 
{
  std::list<Good>::iterator iter = m_inventory.begin();
  for (; iter != m_inventory.end(); ++iter) {
    if ((*iter).m_goodName == goodName) {
      return (*iter).m_price;
    }
  }
  // item not found
  return 0;
}
