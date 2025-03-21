/**
 * Ethan Meli
 * Homework 3
 * ProductFactory Header in C++
*/
#ifndef PRODUCTFACTORY_H
#define PRODUCTFACTORY_H

#include <string>
#include <vector>
#include <map>
#include <memory>
#include "Product.h"

// Product template structure
struct ProductTemplate {
    std::string name;
    std::string type; // Subcategory (e.g. "Laptop" in "Electronics")
    double basePrice;
};

class ProductFactory {
public:
    static ProductFactory& getInstance();

    // Get available categories
    std::vector<std::string> getCategories() const;

    // Get products for a specific category
    std::map<std::string, std::vector<ProductTemplate>> getProductTemplates() const;
    std::vector<ProductTemplate> getProductsByCategory(const std::string& category) const;

    // Create a product based on category and type
    std::shared_ptr<Product> createProduct(const std::string& category, 
                                            const ProductTemplate& productTemplate,
                                            double startingBid, 
                                            const std::string& quality, 
                                            const std::string& sellerUsername);

    // Generate next product ID
    int getNextProductId() const;
    void updateMaxProductId(int id);

    // Initialize product catalog
    void initialize();
    
private:
    ProductFactory() : maxProductId(100) {} // Private constructor for singleton
    
    // Product templates organized by category and subcategory
    std::map<std::string, std::vector<ProductTemplate>> productTemplates;
    
    // Keep track of the highest product ID
    int maxProductId;
};

#endif