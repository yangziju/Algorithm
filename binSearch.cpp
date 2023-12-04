#include <iostream>
#include <vector>
using namespace std;
    // vector<int> arr = {0, 1, 2, 2, 2, 4}; // {2, 4}
    // vector<int> arr2 = {0, 1, 2, 2, 2, 2, 5}; // {2, 5}
// 找 >= target的第一个数
int equal_left_bound(const vector<int>& arr, int l, int r, int target) {
    if (l > r || target > arr[r]) return -1;
    while (l < r) {
        int m = l + ((r - l) >> 1);
        if (arr[m] >= target) r = m;
        else l = m + 1;
    }
    return r;
}

// 找 > target
int greater_bound(const vector<int>& arr, int l, int r, int target) {
    if (l > r || target >= arr[r]) return -1;
    while (l < r) {
        int m = l + ((r - l) >> 1);
        if (arr[m] > target) r = m;
        else l = m + 1;
    }
    return r;
}

// 找 < target
int less_bound(const vector<int>& arr, int l, int r, int target) {
    if (l > r || target <= arr[l]) return -1;
    while (l < r) {
        int m = l + ((r - l + 1) >> 1);
        if (arr[m] < target) l = m;
        else r = m - 1;
    }
    return l;
}

// 找 <= target的最后一个数位置
int equal_right_bound(const vector<int>& arr, int l, int r, int target) {
    if (l > r || target < arr[l] || target > arr[r]) return -1;
    while (l < r) {
        int m = l + ((r - l + 1) >> 1);
        if (arr[m] <= target) l = m;
        else r = m - 1;
    }
    return l;
}

int main() {
    vector<int> arr = {2, 2, 2, 2, 2, 4}; // {2, 4}
    vector<int> arr2 = {0, 1, 2, 2, 2, 2}; // {2, 5}

    cout << equal_left_bound(arr, 0, arr.size() - 1, 2) << endl;
    cout << equal_left_bound(arr2, 0, arr2.size() - 1, 2) << endl << endl;

    cout << greater_bound(arr, 0, arr.size() - 1, 2) << endl;
    cout << greater_bound(arr2, 0, arr2.size() - 1, 2) << endl << endl;

    cout << less_bound(arr, 0, arr.size() - 1, 2) << endl;
    cout << less_bound(arr2, 0, arr2.size() - 1, 2) << endl << endl;

    cout << equal_right_bound(arr, 0, arr.size() - 1, 2) << endl;
    cout << equal_right_bound(arr2, 0, arr2.size() - 1, 2) << endl;

    return 0;
}