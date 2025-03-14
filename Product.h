#ifndef PRODUCT_H
#define PRODUCT_H
#include <string>
#include <vector>

// Bid class
class Bid {
public:
  Bid(int productID, std::string buyerUsername, double bidAmount);
  double getBidAmount();
  std::string getBuyerUsername();
private:
  int productID_;
  std::string buyerUsername_;
  double bidAmount_;
};

class Product {
public:
    virtual void displayProductInfo() = 0;
    void startBidding();
    void closeBidding();
    void updateQuality(std::string quality);
    void addBid(Bid* bid);
    bool isBiddingOpen();
protected:
    int productID_;
    std::string name_;
    std::string category_;
    std::string quality_;
    double basePrice_;
    std::vector<Bid*> bidList_;
    bool biddingOpen_;
};
#endif