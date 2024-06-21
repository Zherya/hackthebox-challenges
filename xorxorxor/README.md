# Hack The Box [xorxorxor](https://app.hackthebox.com/challenges/191) challenge solution

## Challenge description

Who needs AES when you have XOR?

## Encryption algorithm

The key for the encryption algorithm is 4 random bytes, which are continuously XORed
with the bytes of the `flag`. As key is only 4 bytes long, the key is cyclically
repeated for each 4 bytes of the `flag`.

## Solution

As we know that first 4 bytes of the each `flag` on the Hack The Box is `HTB{` ASCII
symbols and we know the ciphertext, we can brute force the entire key, as it is only
4 bytes long. And as the same key is applied cyclically for the entire `flag`, we can
easily restore the whole `flag`.
