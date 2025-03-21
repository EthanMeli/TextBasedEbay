/**
 * Ethan Meli
 * Homework 3
 * FileManager Header in C++
*/
#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <string>
#include <vector>
#include <memory>
#include "Buyer.h"
#include "Seller.h"
#include "Product.h"
#include "Bid.h"

class FileManager {
private:
  std::string usersFileName;
  std::string productsFileName;
  std::string bidsFileName;

public:
  FileManager(std::string usersFileName = "UserInformation.csv", 
              std::string productsFileName = "ProductBids.csv",
              std::string bidsFileName = "bids.csv");
  ~FileManager();

  // Load data from CSV files
  std::vector<std::shared_ptr<User>> loadUsers();
  std::vector<std::shared_ptr<Product>> loadProducts(const std::vector<std::shared_ptr<User>>& users);
  void loadBids(const std::vector<std::shared_ptr<User>>& users, 
                const std::vector<std::shared_ptr<Product>>& products);

  // Save data to CSV files
  void saveUsers(const std::vector<std::shared_ptr<User>>& users);
  void saveProducts(const std::vector<std::shared_ptr<Product>>& products);
  void saveBids(const std::vector<std::shared_ptr<User>>& users);
};

#endif // FILE_MANAGER_H
