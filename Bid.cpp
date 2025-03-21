/**
 * Ethan Meli
 * Homework 3
 * Bid Implementation in C++
 */
#include "Bid.h"
#include <ctime>
#include <sstream>
#include <iomanip>
#include <string>

/**
 * Bid constructor
 * @param buyerUsername - the username of the buyer
 * @param productId - the ID of the product being bid on
 * @param bidAmount - the amount of the bid
 */
Bid::Bid(std::string buyerUsername, int productId, double bidAmount)
    : buyerUsername(buyerUsername), productId(productId), bidAmount(bidAmount), winningBid(false) {
    // Generate timestamp
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    std::stringstream ss;
    ss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S"); // Formats time stamp for bid
    timestamp = ss.str();
}

Bid::~Bid() {} // Bid destructor

std::string Bid::getBuyerUsername() const {
  return buyerUsername; // Returns the buyer's username
}

int Bid::getProductId() const {
  return productId; // Returns the product ID
}

double Bid::getBidAmount() const {
  return bidAmount; // Returns the bid amount
}

std::string Bid::getTimestamp() const {
  return timestamp; // Returns the timestamp
}

bool Bid::isWinningBid() const {
  return winningBid; // Returns if the bid is the winning bid
}

/**
 * Set the buyer's username
 * @param buyerUsername - the username of the buyer
 */
void Bid::setBuyerUsername(const std::string& buyerUsername) {
  this->buyerUsername = buyerUsername;
}

/**
 * Set the product ID
 * @param productId - the ID of the product being bid on
 */
void Bid::setProductId(int productId) {
  this->productId = productId; 
}

/**
 * Set the bid amount
 * @param bidAmount - the amount of the bid
 */
void Bid::setBidAmount(double bidAmount) {
  this->bidAmount = bidAmount;
}

/**
 * Set the winning bid flag
 * @param winning - true if the bid is the winning bid
 */
void Bid::setWinningBid(bool winning) {
  this->winningBid = winning;
}

/**
 * Convert the bid to a CSV string
 * @return the bid as a CSV string
 */
std::string Bid::toCSV() const {
  std::stringstream ss;
  ss << buyerUsername << "," << productId << "," 
      << bidAmount << "," << timestamp << "," << winningBid;
  return ss.str();
}
