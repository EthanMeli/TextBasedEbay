#include "AuctionDriver.h"
#include "ProductFactory.h"

int main() {
    // Instantiate Auction Manager (Singleton)
    AuctionDriver& driver = AuctionDriver::getInstance();
    driver.loadUsersFromCSV();
    driver.loadProductsFromCSV();

    // Create dummy bids
    std::map<int, std::vector<Bid*>> dummyBids;
    dummyBids[101].push_back(new Bid(101, "Alice", 600.00));
    dummyBids[102].push_back(new Bid(102, "John", 175.00));

    // Seller adding a new product using Factory Pattern
    Product* newProduct = ProductFactory::createProduct("Electronics", "Gaming Laptop", 1200.00, "New");
    driver.addProduct(newProduct);
    
    return 0;
}