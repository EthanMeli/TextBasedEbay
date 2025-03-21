/**
 * Ethan Meli
 * Homework 3
 * Seller Header in C++
*/
#ifndef SELLER_H
#define SELLER_H

#include "User.h"
#include <vector>
#include <memory>

class Product;
class Buyer; // Forward declaration of Buyer class

class Seller : public User {
private:
    std::vector<std::shared_ptr<Product>> products;
    
public:
    // Constructor
    Seller(std::string username, double accountBalance, std::string address, std::string phoneNumber);
    ~Seller() override;
    
    // Override the getUserType function
    std::string getUserType() const override;
    
    // Post a product for sale using product factory
    std::shared_ptr<Product> postProduct();
    
    // View similar product prices
    void viewSimilarProductPrices(const std::vector<std::shared_ptr<Product>>& allProducts) const;
    
    // Get overview of products (sold or unsold)
    void viewProductsOverview() const;
    
    // Open bid on a product
    bool openBid(const std::string& productIdStr);
    
    // Close bid on a product
    bool closeBid(const std::string& productIdStr, std::vector<std::shared_ptr<Buyer>>& buyers);
    
    // View bid history for a product
    void viewBidHistory(const std::string& productIdStr) const;
    
    // Add a product to the seller's list
    void addProduct(std::shared_ptr<Product> product);
    
    // Get products
    std::vector<std::shared_ptr<Product>> getProducts() const;
    
    // Find product by ID - overloaded to support both string and int IDs
    std::shared_ptr<Product> findProductById(const std::string& productIdStr) const;
    std::shared_ptr<Product> findProductById(int productId) const;
};

#endif // SELLER_H
