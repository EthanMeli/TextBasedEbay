/**
 * Ethan Meli
 * Homework 3
 * User Header in C++
*/
#ifndef USER_H
#define USER_H

#include <string>

class User {
protected:
    std::string username;
    double accountBalance;
    std::string address;
    std::string phoneNumber;
    
public:
    User(std::string username, double accountBalance, std::string address, std::string phoneNumber);
    virtual ~User();
    
    // Getters
    std::string getUsername() const;
    double getAccountBalance() const;
    std::string getAddress() const;
    std::string getPhoneNumber() const;
    
    // Setters
    void setUsername(const std::string& username);
    void setAccountBalance(double balance);
    void setAddress(const std::string& address);
    void setPhoneNumber(const std::string& phoneNumber);
    
    // Update user information
    virtual void updateUserInfo(const std::string& username, const std::string& address, const std::string& phoneNumber);
    
    // Check account balance
    virtual double checkAccountBalance() const;
    
    // Pure virtual function to determine the type of user
    virtual std::string getUserType() const = 0;
};

#endif // USER_H