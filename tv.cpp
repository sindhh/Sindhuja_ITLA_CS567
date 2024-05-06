#include "tv.h"
#include <limits>
#include <iomanip>
#include <algorithm>
#include <cctype>

// Function to display main page
void displayMainPage(const std::vector<Television>& televisions, int page, int itemsPerPage) {
    std::cout << "Welcome to our Television Store!\n";
    std::cout << "Main Page:\n";

    int startIdx = (page - 1) * itemsPerPage;
    int endIdx = std::min(startIdx + itemsPerPage, static_cast<int>(televisions.size()));
    for (int i = startIdx; i < endIdx; ++i) {
        std::cout << std::setw(2) << televisions[i].number << ". " << std::setw(10) << televisions[i].brand << " "
             << std::setw(15) << televisions[i].model << " - $" << televisions[i].price << std::endl;
    }

    std::cout << "\n";
    if (page > 1)
        std::cout << "p. Previous Page\n";
    if (endIdx < televisions.size())
        std::cout << "n. Next Page\n";

    std::cout << "0. Exit\n";
    std::cout << "v. View Cart\n";

    std::cout << "\nPage " << page << " of " << (televisions.size() + itemsPerPage - 1) / itemsPerPage << std::endl;
}

// Function to display description of selected television
void displayDescription(const Television& tv) {
    std::cout << "Description:\n";
    std::cout << "Brand: " << tv.brand << std::endl;
    std::cout << "Model: " << tv.model << std::endl;
    std::cout << "Price: $" << tv.price << std::endl;
    std::cout << "Description: " << tv.description << std::endl;
}

// Function to validate phone number
bool isValidPhoneNumber(const std::string& phone) {
    if (phone.length() != 10)
        return false;
    return std::all_of(phone.begin(), phone.end(), ::isdigit);
}

// Function to validate pincode
bool isValidPincode(const std::string& pincode) {
    if (pincode.length() != 5)
        return false;
    return std::all_of(pincode.begin(), pincode.end(), ::isdigit);
}

// Function to validate email
bool isValidEmail(const std::string& email) {
    size_t atPos = email.find('@');
    size_t dotPos = email.find(".com");
    return atPos != std::string::npos && dotPos != std::string::npos && atPos < dotPos && dotPos == email.length() - 4;
}

// Function to handle buying process
void buyTelevision(const Television& tv, std::vector<Television>& cart) {
    std::cout << "Options:\n";
    std::cout << "1. Buy directly\n";
    std::cout << "2. Add to cart\n";
    std::cout << "Enter your choice (1/2): ";
    int choice;
    std::cin >> choice;
    if (choice == 1) {
        std::cout << "Please enter your details to buy the television:\n";
        std::string firstName, lastName, address, city, state, pincode, phone, email;
        std::cout << "First Name: ";
        std::cin >> firstName;
        std::cout << "Last Name: ";
        std::cin >> lastName;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer
        std::cout << "Address (Street, House No.): ";
        std::getline(std::cin, address);
        std::cout << "City: ";
        std::getline(std::cin, city);
        std::cout << "State: ";
        std::getline(std::cin, state);

        // Loop until a valid pincode is entered
        do {
            std::cout << "Pincode: ";
            std::cin >> pincode;
            if (!isValidPincode(pincode)) {
                std::cout << "Invalid pincode. Please enter a 5-digit pincode.\n";
            }
        } while (!isValidPincode(pincode));

        // Loop until a valid phone number is entered
        do {
            std::cout << "Phone number: ";
            std::cin >> phone;
            if (!isValidPhoneNumber(phone)) {
                std::cout << "Invalid phone number. Please enter a 10-digit number without any special characters.\n";
            }
        } while (!isValidPhoneNumber(phone));

        // Loop until a valid email is entered
        do {
            std::cout << "Email: ";
            std::cin >> email;
            if (!isValidEmail(email)) {
                std::cout << "Invalid email address. Please enter a valid email address in the format 'example@gmail.com'.\n";
            }
        } while (!isValidEmail(email));

        if (firstName.empty() || lastName.empty() || address.empty() || city.empty() ||
            state.empty() || pincode.empty() || phone.empty() || email.empty()) {
            std::cout << "All fields are required.\n";
            return;
        }

        std::cout << "Thank you, " << firstName << " " << lastName << "! Your order for " << tv.brand << " " << tv.model << " has been placed.\n";
    } else if (choice == 2) {
        cart.push_back(tv);
        std::cout << "The " << tv.brand << " " << tv.model << " has been added to your cart.\n";
    } else {
        std::cout << "Invalid choice.\n";
    }
}

// Function to remove item from cart
void removeFromCart(int choice, std::vector<Television>& cart) {
    auto it = std::find_if(cart.begin(), cart.end(), [choice](const Television& tv) {
        return tv.number == choice;
    });
    if (it != cart.end()) {
        std::cout << "Removed " << it->brand << " " << it->model << " from your cart.\n";
        cart.erase(it);
    } else {
        std::cout << "Item not found in cart.\n";
    }
}

// Function to display cart
void displayCart(std::vector<Television>& cart) {
    if (cart.empty()) {
        std::cout << "Your cart is empty.\n";
    } else {
        std::cout << "Your Cart:\n";
        double total = 0;
        for (const auto& tv : cart) {
            std::cout << std::setw(2) << tv.number << ". " << std::setw(10) << tv.brand << " "
                 << std::setw(15) << tv.model << " - $" << tv.price << std::endl;
            total += tv.price;
        }
        std::cout << "Total: $" << total << std::endl;

        std::cout << "Options:\n";
        std::cout << "1. Buy items in your cart\n";
        std::cout << "2. Remove items from your cart\n";
        std::cout << "Enter your choice (1/2): ";
        int option;
        std::cin >> option;
        if (option == 1) {
            std::vector<Television> tempCart = cart; // Make a copy of cart to avoid modifying the original
            for (const auto& tv : tempCart) {
                buyTelevision(tv, cart); // Buy each television in the cart
            }
        } else if (option == 2) {
            std::cout << "Enter the number of the television you want to remove from your cart (0 to cancel): ";
            int choice;
            std::cin >> choice;
            if (choice != 0) {
                removeFromCart(choice, cart);
            }
        } else {
            std::cout << "Invalid choice.\n";
        }
    }
}

// Function to run the television store
void runTelevisionStore() {
    const int itemsPerPage = 5; // Number of items to display per page
    int page = 1; // Start from the first page
    std::vector<Television> televisions = {
        {1, "Sony", "Bravia 4K HDR", 999.99, "A stunning 4K HDR TV with vivid colors and exceptional clarity."},
        {2, "Samsung", "QLED Q80R", 1299.99, "Experience breathtaking color and detail with this QLED TV."},
        {3, "LG", "OLED C9", 1499.99, "This OLED TV delivers perfect black and infinite contrast."},
        {4, "TCL", "6-Series", 799.99, "Get stunning 4K picture quality with Dolby Vision HDR."},
        {5, "Vizio", "P-Series Quantum X", 1799.99, "This TV offers quantum dot technology for ultra-vivid colors."},
        {6, "Hisense", "H8G Quantum Series", 699.99, "Enjoy impressive picture quality and great value."},
        {7, "Panasonic", "HDX900", 1199.99, "Experience the latest in LED technology with this Panasonic TV."},
        {8, "Sharp", "Aquos 4K", 899.99, "This Aquos TV features a sleek design and excellent picture quality."},
        {9, "Philips", "The One", 999.99, "Immerse yourself in stunning 4K Ultra HD picture quality."},
        {10, "Toshiba", "Fire TV Edition", 549.99, "Enjoy thousands of channels, apps, and Alexa skills with this smart TV."}
    };
    std::vector<Television> cart;

    while (true) {
        displayMainPage(televisions, page, itemsPerPage);
        std::cout << "Enter the number of the television to view details (0 to cancel, p for previous page, n for next page): ";
        char choice;
        std::cin >> choice;
        if (choice == '0') {
            break;
        } else if (choice == 'p') {
            if (page > 1) {
                page--;
            } else {
                std::cout << "You are already on the first page.\n";
            }
        } else if (choice == 'n') {
            if (page < (televisions.size() + itemsPerPage - 1) / itemsPerPage) {
                page++;
            } else {
                std::cout << "You are already on the last page.\n";
            }
        } else if (isdigit(choice)) {
            int tvNumber = choice - '0' + (page - 1) * itemsPerPage;
            if (tvNumber >= 1 && tvNumber <= televisions.size()) {
                displayDescription(televisions[tvNumber - 1]);
                buyTelevision(televisions[tvNumber - 1], cart);
            } else {
                std::cout << "Invalid television number.\n";
            }
        } else if (tolower(choice) == 'v') {
            displayCart(cart);
        } else {
            std::cout << "Invalid choice.\n";
        }
    }
}
