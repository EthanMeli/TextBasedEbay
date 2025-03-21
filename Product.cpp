/**
 * Ethan Meli
 * Homework 3
 * Product Implementation in C++
*/
#include "Product.h"
#include "Bid.h"
#include <algorithm>
#include <sstream>
#include <string>

/* Product Base Class */
Product::Product(int productId, std::string name, std::string description, 
                 double startingBid, std::string sellerUsername, std::string quality)
    : productId(productId), name(name), description(description), startingBid(startingBid),
      sellerUsername(sellerUsername), buyerUsername(""), bidActive(false), sold(false),
      finalSalePrice(0.0), quality(quality), category("Unknown") {}

Product::~Product() {}

/**
 * Get the product ID
 * @return the product ID
*/
int Product::getProductId() const {
  return productId;
}

/**
 * Get the product name
 * @return the product name
*/
std::string Product::getName() const {
  return name;
}

/**
 * Get the product description
 * @return the product description
 */
std::string Product::getDescription() const {
  return description;
}

/**
 * Get the starting bid amount
 * @return the starting bid amount
 */
double Product::getStartingBid() const {
  return startingBid;
}

/**
 * Get the seller's username
 * @return the seller's username
 */
std::string Product::getSellerUsername() const {
  return sellerUsername;
}

/**
 * Get the buyer's username
 * @return the buyer's username
 */
std::string Product::getBuyerUsername() const {
  return buyerUsername;
}

/**
 * Check if the bid is active
 * @return true if the bid is active, false otherwise
 */
bool Product::isBidActive() const {
  return bidActive;
}

/**
 * Check if the product is sold
 * @return true if the product is sold, false otherwise
 */
bool Product::isSold() const {
  return sold;
}

/**
 * Get the final sale price
 * @return the final sale price
 */
double Product::getFinalSalePrice() const {
  return finalSalePrice;
}

/**
 * Get the bids for the product
 * @return a vector of shared pointers to Bid objects
 */
std::vector<std::shared_ptr<Bid>> Product::getBids() const {
  return bids;
}

/**
 * Get the product category
 * @return the product category
 */
std::string Product::getCategory() const {
  return category;
}

/**
 * Get the product quality
 * @return the product quality
 */
std::string Product::getQuality() const {
  return quality;
}

/**
 * Set the product name
 * @param name - the product name
 */
void Product::setName(const std::string& name) {
  this->name = name;
}

/**
 * Set the product description
 * @param description - the product description
 */
void Product::setDescription(const std::string& description) {
  this->description = description;
}

/**
 * Set the starting bid amount
 * @param startingBid - the starting bid amount
 */
void Product::setStartingBid(double startingBid) {
  this->startingBid = startingBid;
}

/**
 * Set the Buyer's username
 * @param buyerUsername - the buyer's username
 */
void Product::setBuyerUsername(const std::string& buyerUsername) {
  this->buyerUsername = buyerUsername;
}

/**
 * Set the bid active status
 * @param active - true if the bid is active, false otherwise
 */
void Product::setBidActive(bool active) {
  this->bidActive = active;
}

/**
 * Set the sold status
 * @param sold - true if the product is sold, false otherwise
 */
void Product::setSold(bool sold) {
  this->sold = sold;
}

/**
 * Set the final sale price
 * @param price - the final sale price
 */
void Product::setFinalSalePrice(double price) {
  this->finalSalePrice = price;
}

/**
 * Set the product quality
 * @param quality - the product quality
 */
void Product::setQuality(const std::string& quality) {
  this->quality = quality;
}

/**
 * Add a bid to the product
 * @param bid - the bid to add
 */
void Product::addBid(std::shared_ptr<Bid> bid) {
  bids.push_back(bid);
}

/**
 * Remove a bid from the product
 * @param buyerUsername - the username of the buyer to remove
 */
void Product::removeBid(const std::string& buyerUsername) {
  bids.erase(std::remove_if(bids.begin(), bids.end(),
      [&buyerUsername](const std::shared_ptr<Bid>& bid) {
          return bid->getBuyerUsername() == buyerUsername;
      }), bids.end());
}

/**
 * Get the highest bid for the product
 * @return a shared pointer to the highest bid
 */
std::shared_ptr<Bid> Product::getHighestBid() const {
  if (bids.empty()) {
    return nullptr;
  }
  
  return *std::max_element(bids.begin(), bids.end(),
      [](const std::shared_ptr<Bid>& a, const std::shared_ptr<Bid>& b) {
          return a->getBidAmount() < b->getBidAmount();
      });
}

/**
 * Get the highest bid amount for the product
 * @return the highest bid amount
 */
double Product::getHighestBidAmount() const {
  auto highestBid = getHighestBid();
  if (highestBid) {
    return highestBid->getBidAmount();
  }
  return startingBid;
}

/**
 * Convert the product to a CSV string
 * @return the product as a CSV string
 */
std::string Product::toCSV() const {
  std::stringstream ss;
  ss << productId << ","
      << name << ","
      << getProductType() << "," 
      << category << "," 
      << quality << ","
      << startingBid << ","
      << sellerUsername << ","
      << getHighestBidAmount() << ","
      << buyerUsername;
  return ss.str();
}

/* Electronics Class */
Electronics::Electronics(int productId, std::string name, std::string description, 
                       double startingBid, std::string sellerUsername, std::string quality)
    : Product(productId, name, description, startingBid, sellerUsername, quality) {
    category = "Electronics";
}

std::string Electronics::getProductType() const {
  return "Electronics";
}

/* Clothing Class */
Clothing::Clothing(int productId, std::string name, std::string description, 
                 double startingBid, std::string sellerUsername, std::string quality)
    : Product(productId, name, description, startingBid, sellerUsername, quality) {
    category = "Clothing";
}

std::string Clothing::getProductType() const {
  return "Clothing";
}

/* Furniture Class */
Furniture::Furniture(int productId, std::string name, std::string description, 
                   double startingBid, std::string sellerUsername, std::string quality)
    : Product(productId, name, description, startingBid, sellerUsername, quality) {
    category = "Furniture";
}

std::string Furniture::getProductType() const {
  return "Furniture";
}

/* Books Class */
Books::Books(int productId, std::string name, std::string description, 
           double startingBid, std::string sellerUsername, std::string quality)
    : Product(productId, name, description, startingBid, sellerUsername, quality) {
    category = "Books";
}

std::string Books::getProductType() const {
  return "Books";
}

/* Vehicles Class */
Vehicles::Vehicles(int productId, std::string name, std::string description, 
                 double startingBid, std::string sellerUsername, std::string quality)
    : Product(productId, name, description, startingBid, sellerUsername, quality) {
    category = "Vehicles";
}

std::string Vehicles::getProductType() const {
  return "Vehicles";
}
