#ifndef USER_H
#define USER_H
#include <string>
#include <vector>
#include "Product.h"

class User {
public:
    virtual void updateUserInfo();
    double getAccountBalance();
    void updateBalance(double amount);
    virtual void displayUserInfo() = 0;
protected:
    long phone_no_;
    std::string username_;
    std::string address_;
    double account_balance_;
};

class Seller : public User {
public:
    void addProductForSale();
    void viewHistoricalData();
    void checkAccountBalance();
    void viewActiveAndSoldProducts();
    void openOrCloseBid(int productID);
    void viewBidHistory();
private:
    std::vector<Product*> productsForSale_;
};

class Buyer : public User {
public:
    void viewProductsForSale();
    void placeBid(int productID, double bidAmount);
    void checkAccountBalance();
    void viewPlacedBids();
    void viewPurchaseHistory();
private:
    std::vector<Bid*> bidsPlaced_;
}; 
#endif