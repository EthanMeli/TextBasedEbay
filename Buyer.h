/**
 * Ethan Meli
 * Homework 3
 * Buyer Header in C++
 */

#ifndef BUYER_H
#define BUYER_H

#include "User.h"
#include <vector>
#include <map>
#include <memory>
#include <string>

class Product;
class Bid;

class Buyer : public User {
private:
    std::vector<std::shared_ptr<Bid>> bids;
    std::vector<std::shared_ptr<Product>> purchasedProducts;
    
public:
    // Constructor
    Buyer(std::string username, double accountBalance, std::string address, std::string phoneNumber);
    ~Buyer() override;
    
    // Override the getUserType function
    std::string getUserType() const override;
    
    // View products for sale
    void viewProductsForSale(const std::vector<std::shared_ptr<Product>>& products) const;
    
    // Place a bid
    bool placeBid(std::shared_ptr<Product> product, double bidAmount);
    
    // View bid history
    void viewBids() const;
    
    // View purchase history
    void viewPurchaseHistory() const;
    
    // Add a bid to the buyer's history
    void addBid(std::shared_ptr<Bid> bid);
    
    // Add a purchased product
    void addPurchasedProduct(std::shared_ptr<Product> product);
    
    // Get bids
    std::vector<std::shared_ptr<Bid>> getBids() const;
    
    // Get purchased products
    std::vector<std::shared_ptr<Product>> getPurchasedProducts() const;
};

#endif // BUYER_H
