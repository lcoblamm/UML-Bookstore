#include <iostream>
#include <string>
#include "Good.h"
#include "Supplier.h"
#include "Retailer.h"
#include "Customer.h"
#include "Enums.h"

void createSupplierGoods(Supplier& warehouse);
void createRetailerGoods(Retailer& toystore);

int main(int argc, char* argv[])
{
  // create a supplier
  Supplier warehouse(1);

  // give supplier list of goods
  createSupplierGoods(warehouse);

  // create a retailer
  Retailer toystore("Toy Chest", "785-555-5555", "customerservice@toychest.com", &warehouse);

  // give retailer list of goods
  createRetailerGoods(toystore);

  // create a customer
  Customer shopper(1, "Jane Shopper", "American Express");

  // display welcome message
  std::cout << "\nWelcome to the Toy Chest!" << std::endl;
  std::cout << "\nWould you like to see the items we have for sale? (Y/N): ";

  // get user's input
  char selection = 'y';
  do {
    std::cin >> selection;
    if (selection == 'n' || selection == 'N') {
      std::cout << "Thank you for coming by! Have a nice day!" << std::endl;
      return 0;
    }
    else if (selection == 'y' || selection == 'Y') {
      break;
    }
    std::cout << "Invalid selection. Please input Y or N: ";
  } while (true);
  
  char orderMore = 'y';
  do { 
    // display goods
    std::cout << std::endl;
    shopper.viewGoods(toystore);
    
    // ask if customer wants to place order
    std::cout << "\nWould you like to place an order? (Y/N): ";
    do {
      std::cin >> selection;
      if (selection == 'n' || selection == 'N') {
	std::cout << "\nThank you for coming by! Have a nice day!" << std::endl;
	return 0;
      }
      else if (selection == 'y' || selection == 'Y') {
	break;
      }
      std::cout << "\nInvalid selection. Please input Y or N: ";
    } while (true);
    
    // prompt user for order
    std::string item;
    int quantity;
    std::cout << "\nPlease enter the name of the item you'd like to order: ";
    std::cin >> item;
    std::cout << "\nPlease enter the quantity you'd like to order: ";
    std::cin >> quantity;
    
    // submit order & ask user if they agree to pay the required amount
    double price = 0;
    returnCode orderOutcome = shopper.selectOrder(item, quantity, toystore, price);
    switch (orderOutcome) {
    case ITEM_NOT_FOUND: {
      std::cout << "\nThe item you selected was not found in the inventory." << std::endl;
      continue;
    }
    case ITEM_NOT_AVAILABLE: {
      std::cout << "\nI'm sorry but we cannot get the quantity you requested." << std::endl;
      continue;
    }
    case SUCCESS: {
      std::cout << "\nWe'd be happy to fulfill your order!\n"
		<< "Do you agree to pay $" << price << "? (Y/N): ";
      break;
    }
    }
   
    // get user's response
    do {
      std::cin >> selection;
      if (selection == 'n' || selection == 'N') {
	std::cout << "\nYou're order has been cancelled." << std::endl;
	return 0;
      }
      else if (selection == 'y' || selection == 'Y') {
	break;
      }
      std::cout << "\nInvalid selection. Please input Y or N: ";
    } while (true);
    
    // process payment and place order
    if (shopper.makePayment(price, toystore, item, quantity)) {
      std::cout << "\nYou're order has been successfully processed. Thank you!" << std::endl;
    }
    else {
      std::cout << "\nYou're payment was not successfully processed.\n"
		<< "The order was cancelled." << std::endl;
    }
  
    // ask user if they would like to order another item
    std::cout << "\nWould you like to place another order? (Y/N): ";
    std::cin >> orderMore;
  } while (orderMore != 'N' && orderMore != 'n');

  std::cout << "\nThank you for shopping at Toy Chest!" << std::endl;
    
  return 0;
}

void createSupplierGoods(Supplier& warehouse)
{
  Good legos(1, "Legos", 100, 54.99);
  Good scienceKit(2, "Science Kit", 100, 24.99);
  Good playdoh(3, "Playdoh", 100, 5.99);
  Good stickers(4, "Stickers", 100, 3.99);
  Good stuffedAnimal(5, "Stuffed Animal", 100, 19.99);
  warehouse.addGood(legos);
  warehouse.addGood(scienceKit);
  warehouse.addGood(playdoh);
  warehouse.addGood(stickers);
  warehouse.addGood(stuffedAnimal);
}

void createRetailerGoods(Retailer& toystore)
{
  Good legos(1, "Legos", 20, 54.99);
  Good scienceKit(2, "Science Kit", 10, 24.99);
  Good playdoh(3, "Playdoh", 30, 5.99);
  Good stickers(4, "Stickers", 40, 3.99);
  Good stuffedAnimal(5, "Stuffed Animal", 20, 19.99);
  toystore.addGood(legos);
  toystore.addGood(scienceKit);
  toystore.addGood(playdoh);
  toystore.addGood(stickers);
  toystore.addGood(stuffedAnimal);
}
