#include <iostream>
#include <fstream>
#include <bit>

int main() {
    std::ifstream input_file("rev_simpleencryptor/flag.enc");

    // First four bytes of the data is a seed for libc srand() function
    unsigned int seed;
    input_file.read(reinterpret_cast<char *>(&seed), sizeof(seed));
    std::cout << "Seed: " << seed << '\n';

    // Seed the C random generator with required seed value
    std::srand(seed);

    std::string encrypted_data;
    input_file >> encrypted_data;

    std::string flag;
    // During encrypt, each byte of plain data:
    // * XORed with rand() value;
    // * next rand() value is ANDed with 7;
    // * XORed plain byte is cyclically rotated to left by this
    //   (rand() & 7) and the result is actual encrypted byte.
    //
    // We have to perform these actions in reverse, keeping in mind
    // that we have to use rand() in the same order as for encryption
    // in order to get the right rand() values.
    for (unsigned char encrypted_byte: encrypted_data) {
        int rnd_value_to_xor_plain_byte = std::rand();
        int rnd_value_rotate = std::rand() & 7;

        encrypted_byte = std::rotr(encrypted_byte, rnd_value_rotate);
        encrypted_byte ^= rnd_value_to_xor_plain_byte;

        flag.push_back(encrypted_byte);
    }

    std::cout << "Flag: " << flag << '\n';
}
