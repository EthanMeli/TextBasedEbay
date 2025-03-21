/**
 * Ethan Meli
 * Homework 3
 * ProductFactory Implementation in C++
*/
#include "ProductFactory.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <string>

// Private constructor for singleton
ProductFactory& ProductFactory::getInstance() {
    static ProductFactory instance;
    return instance;
}

/**
 * Get available categories
 * @return a vector of available categories
 */
std::vector<std::string> ProductFactory::getCategories() const {
    std::vector<std::string> categories;
    for (const auto& category : productTemplates) {
        categories.push_back(category.first);
    }
    return categories;
}

// Return map of product templates
std::map<std::string, std::vector<ProductTemplate>> ProductFactory::getProductTemplates() const {
    return productTemplates;
}

/**
 * Get products for a specific category
 * @param category - the category to search for
 * @return a vector of product templates for the category
 */
std::vector<ProductTemplate> ProductFactory::getProductsByCategory(const std::string& category) const {
    auto it = productTemplates.find(category);
    if (it != productTemplates.end()) {
        return it->second;
    }
    return {};
}

/**
 * Generate the next product ID
 * @return the next product ID
 */
int ProductFactory::getNextProductId() const {
    return maxProductId + 1;
}

/**
 * Update the maximum product ID
 * @param id - the ID to compare with the current maximum
 */
void ProductFactory::updateMaxProductId(int id) {
    if (id > maxProductId) {
        maxProductId = id;
    }
}

/**
 * Create a product based on category and type
 * @param category - the category of the product
 * @param productTemplate - the template for the product
 * @param startingBid - the starting bid amount
 * @param quality - the quality of the product
 * @param sellerUsername - the username of the seller
 * @return a shared pointer to the created product
 */
std::shared_ptr<Product> ProductFactory::createProduct(const std::string& category,
                                                     const ProductTemplate& productTemplate,
                                                     double startingBid,
                                                     const std::string& quality,
                                                     const std::string& sellerUsername) {
    // Generate product ID
    int productId = getNextProductId();
    updateMaxProductId(productId);
    
    // Create description with quality and type
    std::string description = " (" + productTemplate.type + ", " + quality + ")";
    
    // Create the appropriate product type
    std::shared_ptr<Product> product;
    
    if (category == "Electronics") {
        product = std::make_shared<Electronics>(productId, productTemplate.name, description, 
                                             startingBid, sellerUsername, quality);
    }
    else if (category == "Clothing") {
        product = std::make_shared<Clothing>(productId, productTemplate.name, description, 
                                          startingBid, sellerUsername, quality);
    }
    else if (category == "Furniture") {
        product = std::make_shared<Furniture>(productId, productTemplate.name, description, 
                                           startingBid, sellerUsername, quality);
    }
    else if (category == "Books") {
        product = std::make_shared<Books>(productId, productTemplate.name, description, 
                                       startingBid, sellerUsername, quality);
    }
    else if (category == "Vehicles") {
        product = std::make_shared<Vehicles>(productId, productTemplate.name, description, 
                                          startingBid, sellerUsername, quality);
    }
    
    return product;
}

/**
 * Initialize the product catalog with predefined templates
 */
void ProductFactory::initialize() {
    // Clear existing templates
    productTemplates.clear();

    // Initialize with predefined product hierarchy
    productTemplates["Electronics"] = {
        {"Laptop", "Laptop", 700.00},
        {"Smartphone", "Smartphone", 500.00},
        {"Tablet", "Tablet", 300.00}
    };
    
    productTemplates["Clothing"] = {
        {"Shirt", "Shirt", 30.00},
        {"Pants", "Pants", 50.00},
        {"Shoes", "Shoes", 80.00}
    };
    
    productTemplates["Furniture"] = {
        {"Chair", "Chair", 150.00},
        {"Table", "Table", 250.00},
        {"Bed", "Bed", 500.00}
    };
    
    productTemplates["Books"] = {
        {"Sci-Fi Novel", "Sci-Fi", 20.00},
        {"Non-Fiction Book", "Non-Fiction", 25.00},
        {"Fantasy Novel", "Fantasy", 22.00}
    };
    
    productTemplates["Vehicles"] = {
        {"Car", "Car", 15000.00},
        {"Bike", "Bike", 200.00},
        {"Scooter", "Scooter", 800.00}
    };
}