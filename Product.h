/**
 * Ethan Meli
 * Homework 3
 * Product Header in C++
*/
#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <vector>
#include <memory>
#include <algorithm>

class Bid;

// Base Product class
class Product {
private:
  int productId;
  std::string name;
  std::string description;
  double startingBid;
  std::string sellerUsername;
  std::string buyerUsername;
  bool bidActive;
  bool sold;
  double finalSalePrice;
  std::vector<std::shared_ptr<Bid>> bids;
  std::string quality;
    
protected:
  // Category is protected so derived classes can set it
  std::string category;
    
public:
  Product(int productId, std::string name, std::string description, 
          double startingBid, std::string sellerUsername,
          std::string quality = "New");
  virtual ~Product();
  
  // Virtual function to get the product type
  virtual std::string getProductType() const = 0;
  
  // Getters
  int getProductId() const;
  std::string getName() const;
  std::string getDescription() const;
  double getStartingBid() const;
  std::string getSellerUsername() const;
  std::string getBuyerUsername() const;
  bool isBidActive() const;
  bool isSold() const;
  double getFinalSalePrice() const;
  std::vector<std::shared_ptr<Bid>> getBids() const;
  std::string getCategory() const;
  std::string getQuality() const;
  
  // Setters
  void setName(const std::string& name);
  void setDescription(const std::string& description);
  void setStartingBid(double startingBid);
  void setBuyerUsername(const std::string& buyerUsername);
  void setBidActive(bool active);
  void setSold(bool sold);
  void setFinalSalePrice(double price);
  void setQuality(const std::string& quality);
  
  // Add a bid
  void addBid(std::shared_ptr<Bid> bid);
  
  // Remove a bid
  void removeBid(const std::string& buyerUsername);
  
  // Get highest bid
  std::shared_ptr<Bid> getHighestBid() const;
  
  // Get highest bid amount
  double getHighestBidAmount() const;
  
  // Convert to CSV string
  std::string toCSV() const;
};

// Electronics category
class Electronics : public Product {
public:
  Electronics(int productId, std::string name, std::string description, 
              double startingBid, std::string sellerUsername, std::string quality = "New");
  
  std::string getProductType() const override;
};

// Clothing category
class Clothing : public Product {
public:
  Clothing(int productId, std::string name, std::string description, 
            double startingBid, std::string sellerUsername, std::string quality = "New");
  
  std::string getProductType() const override;
};

// Furniture category
class Furniture : public Product {
public:
  Furniture(int productId, std::string name, std::string description, 
            double startingBid, std::string sellerUsername, std::string quality = "New");
  
  std::string getProductType() const override;
};

// Books category
class Books : public Product {
public:
  Books(int productId, std::string name, std::string description, 
        double startingBid, std::string sellerUsername, std::string quality = "New");
  
  std::string getProductType() const override;
};

// Vehicles category
class Vehicles : public Product {
public:
  Vehicles(int productId, std::string name, std::string description, 
            double startingBid, std::string sellerUsername, std::string quality = "New");
  
  std::string getProductType() const override;
};

#endif // PRODUCT_H