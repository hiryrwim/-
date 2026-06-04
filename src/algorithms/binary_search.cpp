#include "binary_search.h"

int BinarySearch::search(const std::vector<int>& arr, int target) {
    return searchHelper(arr, target, 0, static_cast<int>(arr.size()) - 1);
}

int BinarySearch::search(const std::vector<std::string>& arr, const std::string& target) {
    return searchHelper(arr, target, 0, static_cast<int>(arr.size()) - 1);
}

int BinarySearch::searchHelper(const std::vector<int>& arr, int target, int left, int right) {
    if (left > right) return -1;
    int mid = left + (right - left) / 2;
    if (arr[mid] == target) return mid;
    if (arr[mid] > target) return searchHelper(arr, target, left, mid - 1);
    return searchHelper(arr, target, mid + 1, right);
}

int BinarySearch::searchHelper(const std::vector<std::string>& arr, const std::string& target, int left, int right) {
    if (left > right) return -1;
    int mid = left + (right - left) / 2;
    if (arr[mid] == target) return mid;
    if (arr[mid] > target) return searchHelper(arr, target, left, mid - 1);
    return searchHelper(arr, target, mid + 1, right);
}