/**
 * Ethan Meli
 * Homework 3
 * Seller Implementation in C++
*/
#include "Seller.h"
#include "Product.h"
#include "Buyer.h"
#include "Bid.h"
#include "ProductFactory.h"
#include <iostream>
#include <algorithm>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <limits>

// Constructor
Seller::Seller(std::string username, double accountBalance, std::string address, std::string phoneNumber)
    : User(username, accountBalance, address, phoneNumber) {}

Seller::~Seller() {}

// Override the getUserType function
std::string Seller::getUserType() const {
    return "Seller";
}

/**
 * Post a product for sale using product factory
 */
std::shared_ptr<Product> Seller::postProduct() {
    auto& factory = ProductFactory::getInstance();
    
    // Get categories
    auto categories = factory.getCategories();
    
    // Display categories
    std::cout << "\nAvailable Product Categories:" << std::endl;
    std::cout << "-------------------------" << std::endl;
    for (size_t i = 0; i < categories.size(); i++) {
        std::cout << (i + 1) << ". " << categories[i] << std::endl;
    }
    
    // Select category
    std::cout << "Select a category (1-" << categories.size() << "): ";
    int categoryChoice;
    std::cin >> categoryChoice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    if (categoryChoice < 1 || categoryChoice > static_cast<int>(categories.size())) {
        std::cout << "Invalid category selection." << std::endl;
        return nullptr;
    }
    
    std::string selectedCategory = categories[categoryChoice - 1];
    
    // Get products for selected category
    auto productTemplates = factory.getProductsByCategory(selectedCategory);
    
    // Display products
    std::cout << "\nAvailable Products in " << selectedCategory << ":" << std::endl;
    std::cout << "-------------------------" << std::endl;
    for (size_t i = 0; i < productTemplates.size(); i++) {
        std::cout << (i + 1) << ". " << productTemplates[i].name 
                  << " (Base Price: $" << productTemplates[i].basePrice << ")" << std::endl;
    }
    
    // Select product
    std::cout << "Select a product (1-" << productTemplates.size() << "): ";
    int productChoice;
    std::cin >> productChoice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    if (productChoice < 1 || productChoice > static_cast<int>(productTemplates.size())) {
        std::cout << "Invalid product selection." << std::endl;
        return nullptr;
    }
    
    auto selectedTemplate = productTemplates[productChoice - 1];
    
    // Prompt for quality
    std::cout << "\nAvailable Quality Options:" << std::endl;
    std::cout << "1. New" << std::endl;
    std::cout << "2. Used-VeryGood" << std::endl;
    std::cout << "3. Used-Good" << std::endl;
    std::cout << "4. Used-Okay" << std::endl;
    std::cout << "Select quality (1-4): ";
    
    int qualityChoice;
    std::cin >> qualityChoice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    std::string quality;
    switch (qualityChoice) {
        case 1: quality = "New"; break;
        case 2: quality = "Used-VeryGood"; break;
        case 3: quality = "Used-Good"; break;
        case 4: quality = "Used-Okay"; break;
        default:
            std::cout << "Invalid quality selection. Using 'New' as default." << std::endl;
            quality = "New";
    }
    
    // Prompt for starting price
    std::cout << "Enter starting bid price (suggested: $" << selectedTemplate.basePrice << "): $";
    double startingBid;
    std::cin >> startingBid;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    // Create the product using the factory
    auto product = factory.createProduct(selectedCategory, selectedTemplate, startingBid, quality, username);
    
    // Add the product to seller's list
    addProduct(product);
    
    std::cout << "Product posted successfully. ID: " << product->getProductId() << std::endl;
    return product;
}

/**
 * View similar product prices
 * @param allProducts - a vector of shared pointers to all products
 */
void Seller::viewSimilarProductPrices(const std::vector<std::shared_ptr<Product>>& allProducts) const {
    // Get categories from product factory
    auto& factory = ProductFactory::getInstance();
    auto categories = factory.getCategories();
    
    // Display categories
    std::cout << "\nSelect a category to view similar products:" << std::endl;
    std::cout << "-------------------------" << std::endl;
    for (size_t i = 0; i < categories.size(); i++) {
        std::cout << (i + 1) << ". " << categories[i] << std::endl;
    }
    
    // Select category
    std::cout << "Select a category (1-" << categories.size() << "): ";
    int categoryChoice;
    std::cin >> categoryChoice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    if (categoryChoice < 1 || categoryChoice > static_cast<int>(categories.size())) {
        std::cout << "Invalid category selection." << std::endl;
        return;
    }
    
    std::string selectedCategory = categories[categoryChoice - 1];
    
    // Filter products by the selected category and show sold products
    std::cout << "\nProducts and Their Prices in " << selectedCategory << ":" << std::endl;
    std::cout << "--------------------------------" << std::endl;
    
    bool found = false;
    for (const auto& product : allProducts) {
        if (product->getCategory() == selectedCategory && product->isSold()) {
            std::cout << "Product: " << product->getName() << std::endl;
            std::cout << "Description: " << product->getDescription() << std::endl;
            std::cout << "Final Sale Price: $" << product->getFinalSalePrice() << std::endl;
            std::cout << "--------------------------------" << std::endl;
            found = true;
        }
    }
    
    if (!found) {
        std::cout << "No sold products found in this category." << std::endl;
    }
}

/**
 * Get overview of products
 */
void Seller::viewProductsOverview() const {
    std::cout << "Your Products Overview:" << std::endl;
    std::cout << "----------------------" << std::endl;
    
    std::cout << "Products for Sale (Not Sold):" << std::endl;
    bool hasUnsoldProducts = false;
    for (const auto& product : products) {
        if (!product->isSold()) {
            std::cout << "ID: " << product->getProductId() << std::endl;
            std::cout << "Name: " << product->getName() << std::endl;
            std::cout << "Description: " << product->getDescription() << std::endl;
            std::cout << "Starting Bid: $" << product->getStartingBid() << std::endl;
            std::cout << "Current Highest Bid: $" << product->getHighestBidAmount() << std::endl;
            std::cout << "Bid Status: " << (product->isBidActive() ? "Open" : "Closed") << std::endl;
            std::cout << "----------------------" << std::endl;
            hasUnsoldProducts = true;
        }
    }
    
    if (!hasUnsoldProducts) {
        std::cout << "No products currently for sale." << std::endl;
    }
    
    std::cout << "\nSold Products:" << std::endl;
    bool hasSoldProducts = false;
    for (const auto& product : products) {
        if (product->isSold()) {
            std::cout << "ID: " << product->getProductId() << std::endl;
            std::cout << "Name: " << product->getName() << std::endl;
            std::cout << "Description: " << product->getDescription() << std::endl;
            std::cout << "Sale Price: $" << product->getFinalSalePrice() << std::endl;
            std::cout << "Buyer: " << product->getBuyerUsername() << std::endl;
            std::cout << "----------------------" << std::endl;
            hasSoldProducts = true;
        }
    }
    
    if (!hasSoldProducts) {
        std::cout << "No products have been sold yet." << std::endl;
    }
}

/**
 * Open a bid on a product
 * @param productIdStr - the product ID as a string
 * @return true if the bid was opened successfully, false otherwise
 */
bool Seller::openBid(const std::string& productIdStr) {
    // Convert string ID to int if needed
    int productId;
    try {
        productId = std::stoi(productIdStr);
    } catch (const std::exception& e) {
        std::cout << "Invalid product ID format." << std::endl;
        return false;
    }
    
    auto product = findProductById(productId);
    
    if (!product) {
        std::cout << "Product not found." << std::endl;
        return false;
    }
    
    if (product->isSold()) {
        std::cout << "Cannot open bid on a sold product." << std::endl;
        return false;
    }
    
    if (product->isBidActive()) {
        std::cout << "Bid is already open for this product." << std::endl;
        return false;
    }
    
    product->setBidActive(true);
    std::cout << "Bid opened successfully for product: " << product->getName() << std::endl;
    return true;
}

/**
 * Close a bid on a product
 * @param productIdStr - the product ID as a string
 * @param buyers - a vector of shared pointers to all buyers
 * @return true if the bid was closed successfully, false otherwise
 */
bool Seller::closeBid(const std::string& productIdStr, std::vector<std::shared_ptr<Buyer>>& buyers) {
    // Convert string ID to int if needed
    int productId;
    try {
        productId = std::stoi(productIdStr);
    } catch (const std::exception& e) {
        std::cout << "Invalid product ID format." << std::endl;
        return false;
    }
    
    auto product = findProductById(productId);
    
    if (!product) {
        std::cout << "Product not found." << std::endl;
        return false;
    }
    
    if (!product->isBidActive()) {
        std::cout << "Bid is already closed for this product." << std::endl;
        return false;
    }
    
    if (product->isSold()) {
        std::cout << "This product has already been sold." << std::endl;
        return false;
    }
    
    // Get the highest bid
    auto highestBid = product->getHighestBid();
    
    if (!highestBid) {
        std::cout << "No bids were placed on this product. Closing the bid without selling." << std::endl;
        product->setBidActive(false);
        return true;
    }
    
    // Find the buyer with the highest bid
    std::shared_ptr<Buyer> winningBuyer = nullptr;
    for (auto& buyer : buyers) {
        if (buyer->getUsername() == highestBid->getBuyerUsername()) {
            winningBuyer = buyer;
            break;
        }
    }
    
    if (!winningBuyer) {
        std::cout << "Winning buyer not found. This is unexpected." << std::endl;
        product->setBidActive(false);
        return false;
    }
    
    // Check if the buyer has enough balance
    double bidAmount = highestBid->getBidAmount();
    if (winningBuyer->getAccountBalance() < bidAmount) {
        std::cout << "The winning buyer does not have enough balance. Finding next highest bidder..." << std::endl;
        
        // Remove this bid and find next highest bidder
        product->removeBid(highestBid->getBuyerUsername());
        
        // Recursively try to close the bid again
        return closeBid(productIdStr, buyers);
    }
    
    // Update the product as sold
    product->setSold(true);
    product->setBidActive(false);
    product->setFinalSalePrice(bidAmount);
    product->setBuyerUsername(winningBuyer->getUsername());
    
    // Update balances
    winningBuyer->setAccountBalance(winningBuyer->getAccountBalance() - bidAmount);
    this->setAccountBalance(this->getAccountBalance() + bidAmount);
    
    // Add to buyer's purchased products
    winningBuyer->addPurchasedProduct(product);
    
    // Set winning bid flag
    highestBid->setWinningBid(true);
    
    std::cout << "Bid closed successfully. Product sold to " << winningBuyer->getUsername()
              << " for $" << bidAmount << std::endl;
    
    // Notify all bidders
    for (auto& buyer : buyers) {
        for (auto& bid : buyer->getBids()) {
            if (bid->getProductId() == product->getProductId()) {
                if (bid->getBuyerUsername() == winningBuyer->getUsername()) {
                    std::cout << "Message to " << bid->getBuyerUsername() 
                              << ": Congratulations! You won the bid for " 
                              << product->getName() << "." << std::endl;
                } else {
                    std::cout << "Message to " << bid->getBuyerUsername() 
                              << ": Sorry, you lost the bid for " 
                              << product->getName() << "." << std::endl;
                }
            }
        }
    }
    
    return true;
}

/**
 * View bid history for a product
 * @param productIdStr - the product ID as a string
 */
void Seller::viewBidHistory(const std::string& productIdStr) const {
    // Convert string ID to int if needed
    int productId;
    try {
        productId = std::stoi(productIdStr);
    } catch (const std::exception& e) {
        std::cout << "Invalid product ID format." << std::endl;
        return;
    }
    
    auto product = findProductById(productId);
    
    if (!product) {
        std::cout << "Product not found." << std::endl;
        return;
    }
    
    std::cout << "Bid History for Product: " << product->getName() << " (ID: " << productId << ")" << std::endl;
    std::cout << "--------------------------------" << std::endl;
    
    const auto& bids = product->getBids();
    
    if (bids.empty()) {
        std::cout << "No bids placed on this product yet." << std::endl;
        return;
    }
    
    for (const auto& bid : bids) {
        std::cout << "Buyer: " << bid->getBuyerUsername() << std::endl;
        std::cout << "Bid Amount: $" << bid->getBidAmount() << std::endl;
        std::cout << "Time: " << bid->getTimestamp() << std::endl;
        std::cout << "Status: " << (bid->isWinningBid() ? "Winning Bid" : "Regular Bid") << std::endl;
        std::cout << "--------------------------------" << std::endl;
    }
}

/**
 * Add a product to the seller's list
 * @param product - the product to add
 */
void Seller::addProduct(std::shared_ptr<Product> product) {
    products.push_back(product);
}

/**
 * Get products
 * @return a vector of shared pointers to products
 */
std::vector<std::shared_ptr<Product>> Seller::getProducts() const {
    return products;
}

/**
 * Find product by ID
 * @param productId - the product ID an as int
 * @return a shared pointer to the product if found, nullptr otherwise
 */
std::shared_ptr<Product> Seller::findProductById(int productId) const {
    for (const auto& product : products) {
        if (product->getProductId() == productId) {
            return product;
        }
    }
    return nullptr;
}

/**
 * Find product by ID - overloaded to support both string and int IDs
 * @param productIdStr - the product ID as a string
 * @return a shared pointer to the product if found, nullptr otherwise
 */
std::shared_ptr<Product> Seller::findProductById(const std::string& productIdStr) const {
    // Try to convert string to int
    try {
        int productId = std::stoi(productIdStr);
        return findProductById(productId);
    } catch (const std::exception& e) {
        // If conversion fails, search by string comparison (legacy support)
        for (const auto& product : products) {
            if (std::to_string(product->getProductId()) == productIdStr) {
                return product;
            }
        }
        return nullptr;
    }
}