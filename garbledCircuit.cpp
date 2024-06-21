#include <iostream>
#include <vector>
#include <random>
#include <string>

// Simple XOR-based encryption for demonstration
std::string encrypt(char key, char value) {
    return std::string(1, key ^ value);
}

std::string decrypt(char key, const std::string& ciphertext) {
    return std::string(1, key ^ ciphertext[0]);
}

// Function to generate a random key
char generateRandomKey() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, 255);
    return static_cast<char>(dist(mt));
}

// Garbled gate structure
struct GarbledGate {
    char inputKeyA[2];
    char inputKeyB[2];
    std::string outputCiphertext[2][2]; // 2x2 table for AND gate
};

// Function to garble an AND gate
GarbledGate garbleANDGate() {
    GarbledGate gate;

    // Generate random keys for inputs
    gate.inputKeyA[0] = generateRandomKey();
    gate.inputKeyA[1] = generateRandomKey();
    gate.inputKeyB[0] = generateRandomKey();
    gate.inputKeyB[1] = generateRandomKey();

    // Encrypt outputs (AND operation: 0&0=0, 0&1=0, 1&0=0, 1&1=1)
    gate.outputCiphertext[0][0] = encrypt(gate.inputKeyA[0] ^ gate.inputKeyB[0], 0);
    gate.outputCiphertext[0][1] = encrypt(gate.inputKeyA[0] ^ gate.inputKeyB[1], 0);
    gate.outputCiphertext[1][0] = encrypt(gate.inputKeyA[1] ^ gate.inputKeyB[0], 0);
    gate.outputCiphertext[1][1] = encrypt(gate.inputKeyA[1] ^ gate.inputKeyB[1], 1);

    return gate;
}

// Function to evaluate a garbled AND gate
char evaluateANDGate(const GarbledGate& gate, char garbledInputA, char garbledInputB) {
    // Determine indices based on input keys
    int indexA = (garbledInputA == gate.inputKeyA[1]);
    int indexB = (garbledInputB == gate.inputKeyB[1]);

    // Decrypt the appropriate ciphertext
    std::string decryptedOutput = decrypt(gate.inputKeyA[indexA] ^ gate.inputKeyB[indexB], gate.outputCiphertext[indexA][indexB]);
    return decryptedOutput[0];
}

int main() {
    // Alice and Bob's private inputs
    bool inputA = true;  // Alice's input (1)
    bool inputB = false; // Bob's input (0)

    // Garble the AND gate
    GarbledGate garbledGate = garbleANDGate();

    // Alice and Bob encrypt their inputs
    char garbledInputA = garbledGate.inputKeyA[inputA];
    char garbledInputB = garbledGate.inputKeyB[inputB];

    // Evaluate the garbled AND gate
    char garbledOutput = evaluateANDGate(garbledGate, garbledInputA, garbledInputB);

    // Print the result
    std::cout << "Decrypted result: " << static_cast<int>(garbledOutput) << std::endl;

    return 0;
}
