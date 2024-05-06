#ifndef TV_H
#define TV_H

#include <iostream>
#include <string>
#include <vector>

// Define a struct for television model
struct Television {
    int number;
    std::string brand;
    std::string model;
    double price;
    std::string description;
};

// Function to display main page
void displayMainPage(const std::vector<Television>& televisions, int page, int itemsPerPage);

// Function to display description of selected television
void displayDescription(const Television& tv);

// Function to handle buying process
void buyTelevision(const Television& tv, std::vector<Television>& cart);

// Function to remove item from cart
void removeFromCart(int choice, std::vector<Television>& cart);

// Function to display cart
void displayCart(std::vector<Television>& cart);

// Function to run the television store
void runTelevisionStore();

#endif // TELEVISIONSTORE_H
