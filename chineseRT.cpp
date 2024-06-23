#include <iostream>
#include <vector>
#include <tuple>

// Function to compute gcd and the coefficients of Bézout's identity
std::tuple<long long, long long, long long> extended_gcd(long long a, long long b) {
    if (b == 0) {
        return {a, 1, 0};
    } else {
        auto [g, x1, y1] = extended_gcd(b, a % b);
        return {g, y1, x1 - (a / b) * y1};
    }
}

// Function to compute the modular multiplicative inverse of a modulo m
long long mod_inverse(long long a, long long m) {
    auto [g, x, y] = extended_gcd(a, m);
    if (g != 1) {
        throw std::invalid_argument("Inverse does not exist");
    } else {
        return (x % m) % m;
    }
}

// Function to solve a system of congruences using the Chinese Remainder Theorem
long long chinese_remainder_theorem(const std::vector<long long>& a, const std::vector<long long>& n) {
    long long N = 1;
    for (auto ni : n) {
        N *= ni;
    }

    long long x = 0;
    for (size_t i = 0; i < a.size(); ++i) {
        long long ai = a[i];
        long long ni = n[i];
        long long Ni = N / ni;
        long long Mi = mod_inverse(Ni, ni);
        std::cout << "The inverse of "<< Ni<< " Modulo "<<ni<<" is: " << Mi << std::endl;
        x = (x + ai * Ni * Mi) % N;
    }

    return (x % N +N)%N;
}

int main() {
    
    int m,ai,ni;
    std::cout<<"Enter the number of equations: ";
    std::cin>>m;
    
    std::vector<long long> a;// Remainders
    std::vector<long long> n; // Moduli
    
    std::cout<<"Suppose each equation is represented as x=a(mod n). Enter a and n as a pair separated by space. Then press enter to enter the pair for the next equation\n";
    for(int i=0;i<m;i++)
    {std::cout<<"a_"<<i+1<<":";
        std::cin>>ai;
        std::cout<<"n_"<<i+1<<":";
        std::cin>>ni;
        a.push_back(ai);
        n.push_back(ni);
    }
    
    
    try {
        long long result = chinese_remainder_theorem(a, n);
        std::cout << "The solution is: " << result << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
