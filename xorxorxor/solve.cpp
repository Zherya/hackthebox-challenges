#include <iostream>
#include <vector>

int main() {
    std::vector<unsigned char> ciphertext({0x13, 0x4a, 0xf6, 0xe1, 0x29, 0x7b, 0xc4, 0xa9,
                                           0x6f, 0x6a, 0x87, 0xfe, 0x04, 0x66, 0x84, 0xe8,
                                           0x04, 0x70, 0x84, 0xee, 0x04, 0x6d, 0x84, 0xc5,
                                           0x28, 0x2d, 0xd7, 0xef, 0x29, 0x2d, 0xc9});
    unsigned char knownPlaintext[4] = {'H', 'T', 'B', '{'};
    std::vector<unsigned char> key;

    while (key.size() != 4) {
        std::cout << "Finding the byte #" << key.size() << " of the key... ";
        std::cout.flush();

        // Iterating over all 256 possible values of the byte
        // until the byte of the key is found
        unsigned char keyByte = 0;
        for (int i = 0; i < 256; ++i, ++keyByte)
            if ((ciphertext[key.size()] ^ keyByte) == knownPlaintext[key.size()]) {
                std::cout << std::hex << "It is 0x" << static_cast<unsigned short>(keyByte) << '\n';
                key.push_back(keyByte);
                break;
            }
    }

    std::cout << "Decrypting the flag...\nFlag is: ";
    for (std::size_t i = 0; i < ciphertext.size(); ++i)
        std::cout << static_cast<unsigned char>(ciphertext[i] ^ key[i % key.size()]);
    std::cout << '\n';
    return 0;
}
