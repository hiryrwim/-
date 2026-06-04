// vigenere_cipher.cpp
#include "vigenere_cipher.h"

std::string VigenereCipher::generateFullKey(const std::string& text, const std::string& key) {
    std::string fullKey;
    int keyLen = key.length();
    int j = 0;
    for (size_t i = 0; i < text.length(); i++) {
        if (isalpha(text[i])) {
            fullKey += key[j % keyLen];
            j++;
        } else {
            fullKey += text[i];
        }
    }
    return fullKey;
}

char VigenereCipher::shiftChar(char c, char keyChar, bool encrypt) {
    if (!isalpha(c)) return c;

    char base = isupper(c) ? 'A' : 'a';
    int shift = toupper(keyChar) - 'A';

    if (!encrypt) shift = -shift;

    return (c - base + shift + 26) % 26 + base;
}

std::string VigenereCipher::encrypt(const std::string& plaintext, const std::string& key) {
    std::string result;
    std::string fullKey = generateFullKey(plaintext, key);

    for (size_t i = 0; i < plaintext.length(); i++) {
        result += shiftChar(plaintext[i], fullKey[i], true);
    }
    return result;
}

std::string VigenereCipher::decrypt(const std::string& ciphertext, const std::string& key) {
    std::string result;
    std::string fullKey = generateFullKey(ciphertext, key);

    for (size_t i = 0; i < ciphertext.length(); i++) {
        result += shiftChar(ciphertext[i], fullKey[i], false);
    }
    return result;
}