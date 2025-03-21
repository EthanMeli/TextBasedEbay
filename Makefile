CXX = g++
CXXFLAGS	= -std=c++17 -Wall -Werror -Wpedantic

all: main

clean:
	rm -f main.o User.o Buyer.o Seller.o Product.o Bid.o FileManager.o Driver.o main ProductFactory.o

main: User.o Buyer.o Seller.o Product.o Bid.o FileManager.o ProductFactory.o Driver.o main.o
	$(CXX) $(CXXFLAGS) User.o Buyer.o Seller.o Product.o Bid.o FileManager.o ProductFactory.o Driver.o main.o -o main

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

Driver.o: Driver.cpp
	$(CXX) $(CXXFLAGS) -c Driver.cpp

User.o: User.cpp
	$(CXX) $(CXXFLAGS) -c User.cpp

Buyer.o: Buyer.cpp
	$(CXX) $(CXXFLAGS) -c Buyer.cpp

Seller.o: Seller.cpp
	$(CXX) $(CXXFLAGS) -c Seller.cpp

Product.o: Product.cpp
	$(CXX) $(CXXFLAGS) -c Product.cpp

Bid.o: Bid.cpp
	$(CXX) $(CXXFLAGS) -c Bid.cpp

FileManager.o: FileManager.cpp
	$(CXX) $(CXXFLAGS) -c FileManager.cpp

ProductFactory.o: ProductFactory.cpp
	$(CXX) $(CXXFLAGS) -c ProductFactory.cpp