/**
 * Ethan Meli
 * Homework 3
 * Driver Header in C++
*/
#ifndef DRIVER_H
#define DRIVER_H

#include <memory>
#include <vector>
#include <map>
#include "User.h"
#include "Buyer.h"
#include "Seller.h"
#include "Product.h"
#include "Bid.h"
#include "FileManager.h"

class Driver {
private:
  // Singleton instance
  static std::shared_ptr<Driver> instance;
  
  // Private constructor for singleton
  Driver();
  
  // User data
  std::vector<std::shared_ptr<User>> users;
  std::vector<std::shared_ptr<Product>> products;
  std::shared_ptr<User> currentUser;
  
  // File manager for persistence
  FileManager fileManager;
  
  // Helper methods
  void displayMainMenu();
  void displayBuyerMenu();
  void displaySellerMenu();
  void handleLogin();
  void handleRegistration();
  void handleBuyerActions(int choice);
  void handleSellerActions(int choice);
  std::shared_ptr<User> findUserByUsername(const std::string& username);
  std::vector<std::shared_ptr<Buyer>> getAllBuyers();
  std::vector<std::shared_ptr<Product>> getAvailableProducts();

public:
  // Delete copy constructor and assignment operator
  Driver(const Driver&) = delete;
  Driver& operator=(const Driver&) = delete;
  
  // Get singleton instance
  static std::shared_ptr<Driver> getInstance();
  
  // Destructor
  ~Driver();
  
  // Initialize the application
  void initialize();
  
  // Run the application
  void run();
  
  // Save data before exit
  void saveData();
};

#endif // DRIVER_H
