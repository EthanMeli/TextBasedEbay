/**
 * Ethan Meli
 * Homework 3
 * User Implementation in C++
*/
#include "User.h"
#include <string>

// Constructor
User::User(std::string username, double accountBalance, std::string address, std::string phoneNumber)
    : username(username), accountBalance(accountBalance), address(address), phoneNumber(phoneNumber) {}

User::~User() {}

// Getters
std::string User::getUsername() const {
    return username;
}

double User::getAccountBalance() const {
    return accountBalance;
}

std::string User::getAddress() const {
    return address;
}

std::string User::getPhoneNumber() const {
    return phoneNumber;
}

// Setters
void User::setUsername(const std::string& username) {
    this->username = username;
}

void User::setAccountBalance(double balance) {
    this->accountBalance = balance;
}

void User::setAddress(const std::string& address) {
    this->address = address;
}

void User::setPhoneNumber(const std::string& phoneNumber) {
    this->phoneNumber = phoneNumber;
}

/**
 * Update user information
 * @param username - the username to update
 * @param address - the address to update
 * @param phoneNumber - the phone number to update
 */
void User::updateUserInfo(const std::string& username, const std::string& address, const std::string& phoneNumber) {
    if (!username.empty()) this->username = username;
    if (!address.empty()) this->address = address;
    if (!phoneNumber.empty()) this->phoneNumber = phoneNumber;
}

/**
 * Check account balance
 * @return the account balance
 */
double User::checkAccountBalance() const {
    return accountBalance;
}
