/**
 * Ethan Meli
 * Homework 3
 * Buyer Implementation in C++
*/
#include "Buyer.h"
#include "Product.h"
#include "Bid.h"
#include <iostream>
#include <string>
#include <algorithm>

/**
 * Buyer constructor
 * @param username - the username of the buyer
 * @param accountBalance - the account balance of the buyer
 * @param address - the address of the buyer
 * @param phoneNumber - the phone number of the buyer
 */
Buyer::Buyer(std::string username, double accountBalance, std::string address, std::string phoneNumber)
    : User(username, accountBalance, address, phoneNumber) {}

Buyer::~Buyer() {} // Buyer Destructor

std::string Buyer::getUserType() const {
  return "Buyer"; // Returns the user type
}

/**
 * View products for sale
 * @param products - the products available for sale
 * Displays the products available for bidding
*/
void Buyer::viewProductsForSale(const std::vector<std::shared_ptr<Product>>& products) const {
  std::cout << "Products available for bidding:" << std::endl;
  std::cout << "-----------------------------" << std::endl;
  
  for (size_t i = 0; i < products.size(); i++) {
    // Only show products that are open for bidding and not sold
    if (products[i]->isBidActive() && !products[i]->isSold()) {
      std::cout << (i + 1) << ". " << products[i]->getName() << " - " << products[i]->getDescription() << std::endl;
      std::cout << "   Starting Bid: $" << products[i]->getStartingBid() << std::endl;
      std::cout << "   Current Highest Bid: $" << products[i]->getHighestBidAmount() << std::endl;
      std::cout << "   Seller: " << products[i]->getSellerUsername() << std::endl;
      std::cout << "-----------------------------" << std::endl;
    }
  }
}

/**
 * Place a bid on a product
 * @param product - the product to bid on
 * @param bidAmount - the amount to bid on the product
 * @return true if the bid was placed successfully, false otherwise
*/
bool Buyer::placeBid(std::shared_ptr<Product> product, double bidAmount) {
  // Check if the product is open for bidding
  if (!product->isBidActive()) {
    std::cout << "The product is not open for bidding." << std::endl;
    return false;
  }
  
  // Check if the product is sold
  if (product->isSold()) {
    std::cout << "The product has already been sold." << std::endl;
    return false;
  }
  
  // Check if the bid amount is greater than the current highest bid
  if (bidAmount <= product->getHighestBidAmount()) {
    std::cout << "Your bid must be higher than the current highest bid: $" << product->getHighestBidAmount() << std::endl;
    return false;
  }
  
  // Check if the buyer has enough account balance
  if (bidAmount > accountBalance) {
    std::cout << "Insufficient account balance. Your balance: $" << accountBalance << std::endl;
    return false;
  }
  
  // Create a new bid with the product's integer ID
  auto bid = std::make_shared<Bid>(username, product->getProductId(), bidAmount);
  
  // Add the bid to the product
  product->addBid(bid);
  
  // Add the bid to the buyer's history
  addBid(bid);
  
  std::cout << "Bid of $" << bidAmount << " placed successfully on " << product->getName() << std::endl;
  
  return true;
}

/**
 * View bid history
 * Displays the buyer's bid history
*/
void Buyer::viewBids() const {
  std::cout << "Your Bid History:" << std::endl;
  std::cout << "----------------" << std::endl;
  
  for (const auto& bid : bids) {
    std::cout << "Product ID: " << bid->getProductId() << std::endl;
    std::cout << "Bid Amount: $" << bid->getBidAmount() << std::endl;
    std::cout << "Time: " << bid->getTimestamp() << std::endl;
    std::cout << "Status: " << (bid->isWinningBid() ? "Winning" : "Not Winning") << std::endl;
    std::cout << "----------------" << std::endl;
  }
}

/**
 * View purchase history
 * Displays the buyer's purchase history
*/
void Buyer::viewPurchaseHistory() const {
  std::cout << "Your Purchase History:" << std::endl;
  std::cout << "---------------------" << std::endl;
  
  for (const auto& product : purchasedProducts) {
    std::cout << "Product: " << product->getName() << std::endl;
    std::cout << "Description: " << product->getDescription() << std::endl;
    std::cout << "Purchase Price: $" << product->getFinalSalePrice() << std::endl;
    std::cout << "Purchased from: " << product->getSellerUsername() << std::endl;
    std::cout << "---------------------" << std::endl;
  }
}

/**
 * Add a bid to the buyer's history
 * @param bid - the bid to add to the buyer's history
*/
void Buyer::addBid(std::shared_ptr<Bid> bid) {
  bids.push_back(bid);
}

/**
 * Add a purchased product to the buyer's history
 * @param product - the product to add to the buyer's history
*/
void Buyer::addPurchasedProduct(std::shared_ptr<Product> product) {
  purchasedProducts.push_back(product);
}

/**
 * Get the buyer's bids
 * @return the buyer's bids
*/
std::vector<std::shared_ptr<Bid>> Buyer::getBids() const {
  return bids;
}

/**
 * Get the buyer's purchased products
 * @return the buyer's purchased products
*/
std::vector<std::shared_ptr<Product>> Buyer::getPurchasedProducts() const {
  return purchasedProducts;
}
