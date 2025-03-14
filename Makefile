CXX = g++
CXXFLAGS	= -std=c++17 -Wall -Werror -Wpedantic

all: main

clean:
	rm main.o AuctionDriver.o ProductFactory.o main

main: AuctionDriver.o ProductFactory.o main.o
	$(CXX) $(CXXFLAGS) AuctionDriver.o ProductFactory.o main.o -o main

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

AuctionDriver.o: AuctionDriver.cpp
	$(CXX) $(CXXFLAGS) -c AuctionDriver.cpp

ProductFactory.o: ProductFactory.cpp
	$(CXX) $(CXXFLAGS) -c ProductFactory.cpp