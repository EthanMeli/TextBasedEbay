/**
 * Ethan Meli
 * Homework 3
 * Bid Header in C++
 */
#ifndef BID_H
#define BID_H

#include <string>

class Bid {
private:
    std::string buyerUsername;
    int productId;
    double bidAmount;
    std::string timestamp;
    bool winningBid;
    
public:
    Bid(std::string buyerUsername, int productId, double bidAmount);
    ~Bid();
    
    // Getters
    std::string getBuyerUsername() const;
    int getProductId() const;
    double getBidAmount() const;
    std::string getTimestamp() const;
    bool isWinningBid() const;
    
    // Setters
    void setBuyerUsername(const std::string& buyerUsername);
    void setProductId(int productId);
    void setBidAmount(double bidAmount);
    void setWinningBid(bool winning);
    
    // Convert to CSV string
    std::string toCSV() const;
};

#endif // BID_H
