// sha512.h
#ifndef SHA512_H
#define SHA512_H

#include <string>
#include <cstdint>

class SHA512 {
public:
    static std::string hash(const std::string& input);

private:
    static const uint64_t K[80];

    uint64_t H[8];

    void processBlock(const uint8_t* block);
    void padMessage(const uint8_t* message, size_t length,
                    uint8_t** paddedMessage, size_t* paddedLength);
    std::string digestToHex();

public:
    SHA512();
    std::string compute(const std::string& input);
};

#endif