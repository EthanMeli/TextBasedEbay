#ifndef AUCTIONDRIVER_H
#define AUCTIONDRIVER_H
#include <map>
#include "User.h"
#include "ProductFactory.h"

class AuctionDriver {
public:
    static AuctionDriver& getInstance();
    void loadUsersFromCSV();
    void loadProductsFromCSV();
    void saveDataToCSV();
    void registerUser(User* user);
    User* loginUser(std::string username);
    void addProduct(Product* product);
    void processBid(int productID, std::string buyerUsername, double bidAmount);
    void closeAuction(int productID);
private:
    AuctionDriver();
    std::map<std::string, User*> users_;
    std::map<int, Product*> products_;
    std::map<int, std::vector<Bid*>> bidHistory_;
};
#endif  