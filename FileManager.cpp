/**
 * Ethan Meli
 * Homework 3
 * FileManager Implementation in C++
*/
#include "FileManager.h"
#include "ProductFactory.h"
#include <fstream>
#include <iostream>
#include <sstream>

// Constructor
FileManager::FileManager(std::string usersFileName, std::string productsFileName, std::string bidsFileName)
    : usersFileName(usersFileName), productsFileName(productsFileName), bidsFileName(bidsFileName) {}

FileManager::~FileManager() {}

// Load users from CSV file
std::vector<std::shared_ptr<User>> FileManager::loadUsers() {
  std::vector<std::shared_ptr<User>> users;
  std::ifstream file(usersFileName);
  
  if (!file.is_open()) {
    std::cout << "Users file not found. Starting with empty users list." << std::endl;
    return users;
  }
  
  std::string line;
  // Skip header if exists
  std::getline(file, line);
  
  while (std::getline(file, line)) {
    std::stringstream ss(line);
    std::string username, role, phoneNumber, address, balanceStr;
    
    std::getline(ss, username, ',');
    std::getline(ss, role, ',');
    std::getline(ss, phoneNumber, ',');
    std::getline(ss, address, ',');
    std::getline(ss, balanceStr, ',');
    
    double balance = std::stod(balanceStr);
    
    if (role == "Buyer") {
      users.push_back(std::make_shared<Buyer>(username, balance, address, phoneNumber));
    } else if (role == "Seller") {
      users.push_back(std::make_shared<Seller>(username, balance, address, phoneNumber));
    }
  }
  
  file.close();
  return users;
}

// Load products from CSV file
std::vector<std::shared_ptr<Product>> FileManager::loadProducts(const std::vector<std::shared_ptr<User>>& users) {
  std::vector<std::shared_ptr<Product>> products;
  std::ifstream file(productsFileName);
  
  // Get the ProductFactory instance
  auto& factory = ProductFactory::getInstance();
  
  if (!file.is_open()) {
    std::cout << "Products file not found. Starting with empty products list." << std::endl;
    return products;
  }
  
  std::string line;
  // Skip header if exists
  std::getline(file, line);
  
  while (std::getline(file, line)) {
    std::stringstream ss(line);
    std::string productIdStr, name, productType, subCategory, quality, startingBidStr, seller, highestBidStr, buyer;
    
    std::getline(ss, productIdStr, ',');
    std::getline(ss, name, ',');
    std::getline(ss, productType, ',');
    std::getline(ss, subCategory, ',');
    std::getline(ss, quality, ',');
    std::getline(ss, startingBidStr, ',');
    std::getline(ss, seller, ',');
    std::getline(ss, highestBidStr, ',');
    std::getline(ss, buyer, ',');
    
    int productId = std::stoi(productIdStr);
    double startingBid = std::stod(startingBidStr);
    double highestBid = std::stod(highestBidStr);
    bool sold = !buyer.empty();
    
    // Update the maximum product ID in the factory
    factory.updateMaxProductId(productId);
    
    // Create description with subCategory and quality
    std::string description = name + " (" + subCategory + ", " + quality + ")";
    
    // Create the appropriate product type
    std::shared_ptr<Product> product;
    
    if (productType == "Electronics") {
      product = std::make_shared<Electronics>(productId, name, description, startingBid, seller, quality);
    }
    else if (productType == "Clothing") {
      product = std::make_shared<Clothing>(productId, name, description, startingBid, seller, quality);
    }
    else if (productType == "Furniture") {
      product = std::make_shared<Furniture>(productId, name, description, startingBid, seller, quality);
    }
    else if (productType == "Books") {
      product = std::make_shared<Books>(productId, name, description, startingBid, seller, quality);
    }
    else if (productType == "Vehicles") {
      product = std::make_shared<Vehicles>(productId, name, description, startingBid, seller, quality);
    }
    
    if (product) {
      product->setBuyerUsername(buyer);
      product->setBidActive(!sold);
      product->setSold(sold);
      product->setFinalSalePrice(sold ? highestBid : 0.0);
      products.push_back(product);
      
      // Add product to seller
      for (const auto& user : users) {
        auto seller_ptr = std::dynamic_pointer_cast<Seller>(user);
        if (seller_ptr && seller_ptr->getUsername() == seller) {
          seller_ptr->addProduct(product);
          break;
        }
      }
      
      // Add product to buyer if sold
      if (sold && !buyer.empty()) {
        for (const auto& user : users) {
          auto buyer_ptr = std::dynamic_pointer_cast<Buyer>(user);
          if (buyer_ptr && buyer_ptr->getUsername() == buyer) {
            buyer_ptr->addPurchasedProduct(product);
            break;
          }
        }
      }
    }
  }
  
  file.close();
  return products;
}

// Save products to CSV file
void FileManager::saveProducts(const std::vector<std::shared_ptr<Product>>& products) {
  std::ofstream file(productsFileName);
  
  if (!file.is_open()) {
    std::cout << "Error: Could not open products file for writing." << std::endl;
    return;
  }
  
  // Write header
  file << "ProductID,Name,Type,Category,Quality,Base Price,Seller,Highest Bid,Buyer" << std::endl;
  
  for (const auto& product : products) {
    file << product->toCSV() << std::endl;
  }
  
  file.close();
}

// Save users to CSV file
void FileManager::saveUsers(const std::vector<std::shared_ptr<User>>& users) {
  std::ofstream file(usersFileName);
  
  if (!file.is_open()) {
    std::cout << "Error: Could not open users file for writing." << std::endl;
    return;
  }
  
  // Write header
  file << "Username,Role,Phone Number,Address,Account Balance" << std::endl;
  
  for (const auto& user : users) {
    file << user->getUsername() << ","
          << user->getUserType() << ","
          << user->getPhoneNumber() << "," // Now using actual phone number
          << user->getAddress() << ","
          << user->getAccountBalance() << std::endl;
  }
  
  file.close();
}

// Load bids from CSV file
void FileManager::loadBids(const std::vector<std::shared_ptr<User>>& users, 
                        const std::vector<std::shared_ptr<Product>>& products) {
  std::ifstream file(bidsFileName);
  
  if (!file.is_open()) {
    std::cout << "Bids file not found. Starting with empty bids list." << std::endl;
    return;
  }
  
  std::string line;
  // Skip header if exists
  std::getline(file, line);
  
  while (std::getline(file, line)) {
    std::stringstream ss(line);
    std::string buyerUsername, productIdStr, bidAmountStr, timestamp, winningBidStr;
    
    std::getline(ss, buyerUsername, ',');
    std::getline(ss, productIdStr, ',');
    std::getline(ss, bidAmountStr, ',');
    std::getline(ss, timestamp, ',');
    std::getline(ss, winningBidStr);
    
    // Convert string values to appropriate types
    int productId;
    double bidAmount;
    
    try {
      productId = std::stoi(productIdStr);
      bidAmount = std::stod(bidAmountStr);
    } catch (const std::exception& e) {
      std::cerr << "Error parsing bid data: " << e.what() << std::endl;
      continue;
    }
    
    bool winningBid = (winningBidStr == "1");
    
    auto bid = std::make_shared<Bid>(buyerUsername, productId, bidAmount);
    bid->setWinningBid(winningBid);
    
    // Add bid to product
    for (const auto& product : products) {
      if (product->getProductId() == productId) {
        product->addBid(bid);
        break;
      }
    }
    
    // Add bid to buyer
    for (const auto& user : users) {
      auto buyer = std::dynamic_pointer_cast<Buyer>(user);
      if (buyer && buyer->getUsername() == buyerUsername) {
        buyer->addBid(bid);
        break;
      }
    }
  }
  
  file.close();
}

// Save bids to CSV file
void FileManager::saveBids(const std::vector<std::shared_ptr<User>>& users) {
  std::ofstream file(bidsFileName);
  
  if (!file.is_open()) {
    std::cout << "Error: Could not open bids file for writing." << std::endl;
    return;
  }
  
  // Write header
  file << "BuyerUsername,ProductID,BidAmount,Timestamp,WinningBid" << std::endl;
  
  // Collect all bids from buyers
  for (const auto& user : users) {
    auto buyer = std::dynamic_pointer_cast<Buyer>(user);
    if (buyer) {
      for (const auto& bid : buyer->getBids()) {
        file << bid->toCSV() << std::endl;
      }
    }
  }
  
  file.close();
}