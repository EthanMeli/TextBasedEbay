/**
 * Ethan Meli
 * Homework 3
 * Main program implementation in C++
*/
#include "Driver.h"
#include <iostream>

int main() {
    std::cout << "=== Online Bidding System ===" << std::endl;
    
    // Get the singleton instance of Driver
    auto driver = Driver::getInstance();
    
    // Initialize the application
    driver->initialize();
    
    // Run the main program loop
    driver->run();
    
    return 0;
}