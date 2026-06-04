// vigenere_cipher.h
#ifndef VIGENERE_CIPHER_H
#define VIGENERE_CIPHER_H

#include <string>

class VigenereCipher {
public:
    static std::string encrypt(const std::string& plaintext, const std::string& key);
    static std::string decrypt(const std::string& ciphertext, const std::string& key);

private:
    static char shiftChar(char c, char keyChar, bool encrypt);
    static std::string generateFullKey(const std::string& text, const std::string& key);
};

#endif