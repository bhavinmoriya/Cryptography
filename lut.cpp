#include <iostream>
#include <cmath>
#include <vector>

const int LUT_SIZE = 360; // Size of the lookup table
std::vector<double> sineLUT(LUT_SIZE);


// Function to initialize the lookup table
void initializeSineLUT() {
    for (int i = 0; i < LUT_SIZE; ++i) {
        sineLUT[i] = std::sin(i * M_PI / 180.0); // Store sine values for degrees 0 to 359
    }
}

// Function to get the sine value from the lookup table
double getSineFromLUT(int degree) {
    degree %= 360; // Ensure the degree is within 0 to 359
    return sineLUT[degree];
}


int main() {
    initializeSineLUT(); // Initialize the LUT

    int degree;
    std::cout << "Enter an angle in degrees: ";
    std::cin >> degree;

    double sineValue = getSineFromLUT(degree);
    std::cout << "Sine of " << degree << " degrees is: " << sineValue << std::endl;

    return 0;
}
