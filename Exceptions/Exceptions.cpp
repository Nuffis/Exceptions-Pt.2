//Landon Dunkerly
//CIS 1202
//12/3/23

#include <iostream>
#include <stdexcept>

// Custom exception classes
class InvalidCharacterException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Invalid start character";
    }
};

class InvalidRangeException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Invalid offset range";
    }
};

// Function to calculate character offsets
char character(char start, int offset) {
    // Check if start is a letter
    if (!isalpha(start)) {
        throw InvalidCharacterException();
    }

    // Check if target is a letter
    if (!isalpha(start + offset)) {
        throw InvalidRangeException();
    }

    // Check for upper- and lower-case transitions
    if ((islower(start) && isupper(start + offset)) || (isupper(start) && islower(start + offset))) {
        throw InvalidRangeException();
    }

    return start + offset;
}

int main() {
    try {
        std::cout << "character('a', 1): " << character('a', 1) << std::endl;
        std::cout << "character('a', -1): ";
        character('a', -1);
    }
    catch (const InvalidRangeException& e) {
        std::cerr << e.what() << std::endl;
    }
    catch (const InvalidCharacterException& e) {
        std::cerr << e.what() << std::endl;
    }

    try {
        std::cout << "character('Z', -1): " << character('Z', -1) << std::endl;
        std::cout << "character('?', 5): ";
        character('?', 5);
    }
    catch (const InvalidRangeException& e) {
        std::cerr << e.what() << std::endl;
    }
    catch (const InvalidCharacterException& e) {
        std::cerr << e.what() << std::endl;
    }

    try {
        // Test upper- and lower-case transition
        std::cout << "character('A', 32): ";
        character('A', 32);
    }
    catch (const InvalidRangeException& e) {
        std::cerr << e.what() << std::endl;
    }
    catch (const InvalidCharacterException& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}