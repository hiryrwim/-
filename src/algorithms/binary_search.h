#ifndef BINARY_SEARCH_H
#define BINARY_SEARCH_H

#include <vector>
#include <string>

class BinarySearch {
public:
    static int search(const std::vector<int>& arr, int target);
    static int search(const std::vector<std::string>& arr, const std::string& target);

private:
    static int searchHelper(const std::vector<int>& arr, int target, int left, int right);
    static int searchHelper(const std::vector<std::string>& arr, const std::string& target, int left, int right);
};

#endif