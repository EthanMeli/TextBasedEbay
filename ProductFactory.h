#ifndef PRODUCTFACTORY_H
#define PRODUCTFACTORY_H
#include <string>
#include <vector>
#include "Product.h"

class ProductFactory {
public:
    static Product* createProduct(const std::string& category, const std::string& name, double basePrice, const std::string& quality);
};

#endif