/**
 * Ethan Meli
 * Homework 3
 * Driver Implementation in C++
 */
#include "Driver.h"
#include "ProductFactory.h"
#include <iostream>
#include <limits>
#include <algorithm>
#include <string>

// Initialize static instance
std::shared_ptr<Driver> Driver::instance = nullptr;

Driver::Driver() : currentUser(nullptr) {}

Driver::~Driver() {
  saveData(); // Destructor saves data
}

// Get singleton instance
std::shared_ptr<Driver> Driver::getInstance() {
  if (!instance) {
      instance = std::shared_ptr<Driver>(new Driver());
  }
  return instance;
}

// Initialize the application
void Driver::initialize() {
  std::cout << "Initializing application..." << std::endl;
  
  // Initialize product factory
  ProductFactory::getInstance().initialize();
  std::cout << "Product catalog initialized." << std::endl;
  
  // Load users from CSV file
  users = fileManager.loadUsers();
  std::cout << "Loaded " << users.size() << " users." << std::endl;
  
  // Load products from CSV file
  products = fileManager.loadProducts(users);
  std::cout << "Loaded " << products.size() << " products." << std::endl;
  
  // Load bids and associate with users and products
  fileManager.loadBids(users, products);
  std::cout << "Loaded bids data." << std::endl;
}

// Handles main program loop
void Driver::run() {
  bool running = true;
  
  while (running) {
    if (!currentUser) {
      displayMainMenu();
    } else if (currentUser->getUserType() == "Buyer") {
      displayBuyerMenu();
    } else if (currentUser->getUserType() == "Seller") {
      displaySellerMenu();
    }
    
    int choice;
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    if (!currentUser) {
      switch (choice) {
        case 1: // Login
          handleLogin();
          break;
        case 2: // Register
          handleRegistration();
          break;
        case 3: // Exit
          running = false;
          break;
        default:
          std::cout << "Invalid choice. Please try again." << std::endl;
      }
    } else if (currentUser->getUserType() == "Buyer") {
      if (choice == 7) {
        currentUser = nullptr;
        std::cout << "Logged out successfully." << std::endl;
      } else {
        handleBuyerActions(choice);
      }
    } else if (currentUser->getUserType() == "Seller") {
      if (choice == 8) {
        currentUser = nullptr;
        std::cout << "Logged out successfully." << std::endl;
      } else {
        handleSellerActions(choice);
      }
    }
  }
  
  saveData();
  std::cout << "Thank you for using the bidding system. Goodbye!" << std::endl;
}

// Main menu display
void Driver::displayMainMenu() {
  std::cout << "\n===== Online Bidding System =====" << std::endl;
  std::cout << "1. Login" << std::endl;
  std::cout << "2. Register" << std::endl;
  std::cout << "3. Exit" << std::endl;
  std::cout << "Choose an option: ";
}

// Buyer menu display
void Driver::displayBuyerMenu() {
  auto buyer = std::dynamic_pointer_cast<Buyer>(currentUser);
  
  std::cout << "\n===== Buyer Menu =====" << std::endl;
  std::cout << "Welcome, " << buyer->getUsername() << "!" << std::endl;
  std::cout << "1. View Products for Sale" << std::endl;
  std::cout << "2. Place a Bid" << std::endl;
  std::cout << "3. Check Account Balance" << std::endl;
  std::cout << "4. Update User Information" << std::endl;
  std::cout << "5. View My Bids" << std::endl;
  std::cout << "6. View Purchase History" << std::endl;
  std::cout << "7. Logout" << std::endl;
  std::cout << "Choose an option: ";
}

// Seller menu display
void Driver::displaySellerMenu() {
  auto seller = std::dynamic_pointer_cast<Seller>(currentUser);
  
  std::cout << "\n===== Seller Menu =====" << std::endl;
  std::cout << "Welcome, " << seller->getUsername() << "!" << std::endl;
  std::cout << "1. Post a Product for Sale" << std::endl;
  std::cout << "2. View Similar Product Prices" << std::endl;
  std::cout << "3. Check Account Balance" << std::endl;
  std::cout << "4. Update User Information" << std::endl;
  std::cout << "5. View Products Overview" << std::endl;
  std::cout << "6. Open/Close Bids" << std::endl;
  std::cout << "7. View Bid History" << std::endl;
  std::cout << "8. Logout" << std::endl;
  std::cout << "Choose an option: ";
}

// Login handler
void Driver::handleLogin() {
  std::string username;
  
  std::cout << "\nEnter your username: ";
  std::getline(std::cin, username);
  
  for (const auto& user : users) {
    if (user->getUsername() == username) {
      currentUser = user;
      std::cout << "Login successful! Welcome, " << user->getUsername() << "!" << std::endl;
      return;
    }
  }
  
  std::cout << "User not found. Please try again or register." << std::endl;
}

// Registration handler
void Driver::handleRegistration() {
  std::string username, address, phoneNumber;
  double initialBalance;
  
  std::cout << "\nRegistration" << std::endl;
  std::cout << "Enter username: ";
  std::getline(std::cin, username);
  
  // Check if username already exists
  for (const auto& user : users) {
    if (user->getUsername() == username) {
      std::cout << "Username already exists. Please choose another." << std::endl;
      return;
    }
  }
  
  std::cout << "Enter your address: ";
  std::getline(std::cin, address);
  
  std::cout << "Enter your phone number: ";
  std::getline(std::cin, phoneNumber);
  
  std::cout << "Enter initial account balance: ";
  std::cin >> initialBalance;
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  
  std::cout << "Are you a Buyer or Seller? (B/S): ";
  char typeChoice;
  std::cin >> typeChoice;
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  
  if (toupper(typeChoice) == 'B') {
    auto newUser = std::make_shared<Buyer>(username, initialBalance, address, phoneNumber);
    users.push_back(newUser);
    currentUser = newUser;
    std::cout << "Registration successful! You are now logged in as a Buyer." << std::endl;
  } else if (toupper(typeChoice) == 'S') {
    auto newUser = std::make_shared<Seller>(username, initialBalance, address, phoneNumber);
    users.push_back(newUser);
    currentUser = newUser;
    std::cout << "Registration successful! You are now logged in as a Seller." << std::endl;
  } else {
    std::cout << "Invalid choice. Registration cancelled." << std::endl;
  }
}

// Buyer action handler
void Driver::handleBuyerActions(int choice) {
  auto buyer = std::dynamic_pointer_cast<Buyer>(currentUser);
  
  switch (choice) {
    case 1: // View Products for Sale
      {
        auto availableProducts = getAvailableProducts();
        buyer->viewProductsForSale(availableProducts);
      }
      break;
    case 2: // Place a Bid
      {
        auto availableProducts = getAvailableProducts();
        buyer->viewProductsForSale(availableProducts);
        
        if (availableProducts.empty()) {
          std::cout << "No products available for bidding." << std::endl;
          break;
        }
        
        std::cout << "Enter the product number you want to bid on: ";
        int productIndex;
        std::cin >> productIndex;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        if (productIndex < 1 || productIndex > static_cast<int>(availableProducts.size())) {
          std::cout << "Invalid product number." << std::endl;
          break;
        }
        
        std::cout << "Enter your bid amount: $";
        double bidAmount;
        std::cin >> bidAmount;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        buyer->placeBid(availableProducts[productIndex - 1], bidAmount);
      }
      break;
    case 3: // Check Account Balance
      std::cout << "Your account balance: $" << buyer->checkAccountBalance() << std::endl;
      break;  
    case 4: // Update User Information
      {
        std::string username, address, phoneNumber;
        
        std::cout << "Enter new username (leave empty to keep current): ";
        std::getline(std::cin, username);
        
        std::cout << "Enter new address (leave empty to keep current): ";
        std::getline(std::cin, address);
        
        std::cout << "Enter new phone number (leave empty to keep current): ";
        std::getline(std::cin, phoneNumber);
        
        buyer->updateUserInfo(username, address, phoneNumber);
        std::cout << "User information updated successfully." << std::endl;
      }
      break;
    case 5: // View My Bids
      buyer->viewBids();
      break; 
    case 6: // View Purchase History
      buyer->viewPurchaseHistory();
      break;
    default:
      std::cout << "Invalid choice. Please try again." << std::endl;
  }
}

// Seller action handler
void Driver::handleSellerActions(int choice) {
  auto seller = std::dynamic_pointer_cast<Seller>(currentUser);
  
  switch (choice) {
    case 1: // Post a Product for Sale
      {
        auto newProduct = seller->postProduct();
        if (newProduct) {
          products.push_back(newProduct);
        }
      }
      break; 
    case 2: // View Similar Product Prices
      {
        seller->viewSimilarProductPrices(products);
      }
      break;
    case 3: // Check Account Balance
      std::cout << "Your account balance: $" << seller->checkAccountBalance() << std::endl;
      break;
    case 4: // Update User Information
      {
        std::string username, address, phoneNumber;
        
        std::cout << "Enter new username (leave empty to keep current): ";
        std::getline(std::cin, username);
        
        std::cout << "Enter new address (leave empty to keep current): ";
        std::getline(std::cin, address);
        
        std::cout << "Enter new phone number (leave empty to keep current): ";
        std::getline(std::cin, phoneNumber);
        
        seller->updateUserInfo(username, address, phoneNumber);
        std::cout << "User information updated successfully." << std::endl;
      }
      break;
    case 5: // View Products Overview
      seller->viewProductsOverview();
      break;
    case 6: // Open/Close Bids
      {
        std::cout << "Do you want to (O)pen or (C)lose a bid? ";
        char bidAction;
        std::cin >> bidAction;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        std::cout << "Your Products:" << std::endl;
        std::cout << "----------------" << std::endl;
        
        auto sellerProducts = seller->getProducts();
        
        if (sellerProducts.empty()) {
          std::cout << "You don't have any products yet." << std::endl;
          break;
        }
        
        for (size_t i = 0; i < sellerProducts.size(); i++) {
          std::cout << (i + 1) << ". " << sellerProducts[i]->getName()
                    << " (Bid: " << (sellerProducts[i]->isBidActive() ? "Open" : "Closed")
                    << ", Sold: " << (sellerProducts[i]->isSold() ? "Yes" : "No")
                    << ")" << std::endl;
        }
        
        std::cout << "Enter product number: ";
        int productIndex;
        std::cin >> productIndex;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        if (productIndex < 1 || productIndex > static_cast<int>(sellerProducts.size())) {
          std::cout << "Invalid product number." << std::endl;
          break;
        }
        
        auto selectedProduct = sellerProducts[productIndex - 1];
        
        if (toupper(bidAction) == 'O') {
          seller->openBid(std::to_string(selectedProduct->getProductId()));
        } else if (toupper(bidAction) == 'C') {
          auto buyers = getAllBuyers();
          seller->closeBid(std::to_string(selectedProduct->getProductId()), buyers);
        } else {
          std::cout << "Invalid action." << std::endl;
        }
      }
      break;
    case 7: // View Bid History
      {
        std::cout << "Your Products:" << std::endl;
        std::cout << "----------------" << std::endl;
        
        auto sellerProducts = seller->getProducts();
        
        if (sellerProducts.empty()) {
          std::cout << "You don't have any products yet." << std::endl;
          break;
        }
        
        for (size_t i = 0; i < sellerProducts.size(); i++) {
          std::cout << (i + 1) << ". " << sellerProducts[i]->getName() << std::endl;
        }
        
        std::cout << "Enter product number to view bid history: ";
        int productIndex;
        std::cin >> productIndex;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        if (productIndex < 1 || productIndex > static_cast<int>(sellerProducts.size())) {
          std::cout << "Invalid product number." << std::endl;
          break;
        }
        
        auto selectedProduct = sellerProducts[productIndex - 1];
        seller->viewBidHistory(std::to_string(selectedProduct->getProductId()));
      }
      break;
    default:
      std::cout << "Invalid choice. Please try again." << std::endl;
  }
}

/**
 * Find a user by username
 * @param username - the username to search for
 * @return the user if found, nullptr otherwise
*/
std::shared_ptr<User> Driver::findUserByUsername(const std::string& username) {
  for (const auto& user : users) {
    if (user->getUsername() == username) {
      return user;
    }
  }
  return nullptr;
}

/**
 * Get all buyers from the list of users
 * @return a vector of shared pointers to Buyer objects
*/
std::vector<std::shared_ptr<Buyer>> Driver::getAllBuyers() {
  std::vector<std::shared_ptr<Buyer>> buyers;
  
  for (const auto& user : users) {
    auto buyer = std::dynamic_pointer_cast<Buyer>(user);
    if (buyer) {
      buyers.push_back(buyer);
    }
  }
  
  return buyers;
}

/**
 * Get all available products for bidding
 * @return a vector of shared pointers to Product objects
*/
std::vector<std::shared_ptr<Product>> Driver::getAvailableProducts() {
  std::vector<std::shared_ptr<Product>> availableProducts;
  
  for (const auto& product : products) {
    if (product->isBidActive() && !product->isSold()) {
      availableProducts.push_back(product);
    }
  }
  
  return availableProducts;
}

// Save all data to CSV files
void Driver::saveData() {
  fileManager.saveUsers(users);
  fileManager.saveProducts(products);
  fileManager.saveBids(users);
  std::cout << "All data saved successfully." << std::endl;
}