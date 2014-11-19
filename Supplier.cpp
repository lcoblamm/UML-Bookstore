#include "Supplier.h"

// Constructor
Supplier::Supplier()
{
  m_supplierID = 0;
  m_balance = 0;
}

// Constructor
// @param supplierID: ID for supplier
Supplier::Supplier(int supplierID)
{
  m_supplierID = supplierID;
  m_balance = 0;
}

// Destructor
Supplier::~Supplier()
{
}

// Accepts payment from retailer and adds payment to balance
// @param payment: Amount being paid
// @return bool: True if payment was accepted
bool Supplier::acceptPayment(double payment)
{
  m_balance += payment;
  return true;
}

// Adds good to supplier's inventory
// @param item: Good to add to inventory
void Supplier::addGood(Good item)
{
  m_inventory.push_back(item);
}

// Removes good from supplier's inventory
// @param goodName: Name of good to remove
// @return returnCode: Enum to describe outcome of removal
returnCode Supplier::removeGood(std::string goodName)
{
  std::list<Good>::iterator iter = m_inventory.begin();
  for (; iter != m_inventory.end(); ++iter) {
    if ((*iter).m_goodName == goodName) {
      m_inventory.erase(iter);
      return SUCCESS;
    }
  }
  // not found
  return ITEM_NOT_FOUND;
}

// Updates quantity of item in inventory
// @param bAdding: True if you want to add items to inventory, false to remove
// @param goodName: Name of good to update
// @param quantity: Number to add/remove
// @return returnCode: Enum to describe outcome of update
returnCode Supplier::updateGood(bool bAdding, std::string goodName, int quantity)
{
  std::list<Good>::iterator iter = m_inventory.begin();
  for (; iter != m_inventory.end(); ++iter) {
    if ((*iter).m_goodName == goodName) {
      // update quantity
      if (bAdding) {
        (*iter).m_quantity += quantity;
      }
      else {
        (*iter).m_quantity -= quantity;
      }

      // exit list
      return SUCCESS;
    }
  }
  // item not found in list
  return ITEM_NOT_FOUND;
}

// Checks stock and updates inventory if stock has enough
// @param goodName: Name of good being ordered
// @param quantity: Number being ordered
// @return returnCode: Enum describing outcome of orcer
returnCode Supplier::acceptOrder(std::string goodName, int quantity)
{
  // check if there are enough and decide whether to accept order
  returnCode stockStatus = checkStock(goodName, quantity);
  if (stockStatus == SUCCESS) {
    return updateGood(false, goodName, quantity);
  }
  // not enough
  return stockStatus;    
}

// Checks supplier's inventory to see if desired number of items are in stock
// @param goodName: Name of good to check for
// @param quantityDesired: Quantity to check for
// @return returnCode: Enum describing outcome of inventory check
returnCode Supplier::checkStock(std::string goodName, int quantityDesired)
{
  std::list<Good>::iterator iter = m_inventory.begin();
  for (; iter != m_inventory.end(); ++iter) {
    if ((*iter).m_goodName == goodName) {
      // check if there's enough
      if ((*iter).m_quantity >= quantityDesired) {
        return SUCCESS;
      }
      // if there's not enough
      return ITEM_NOT_AVAILABLE;
    }
  }
  // if the item wasn't found
  return ITEM_NOT_FOUND;
} 
