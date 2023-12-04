#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// ************ 冒泡排序 ************* //

void bubbleSort(vector<int>& arr) 
{
    for (int i = 0; i < arr.size(); i++) {
        for (int j = 0; j + 1 < arr.size() - i; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// ************ 插入排序 ************* //

void insertSort(vector<int>& arr) {
    for (int i = 1; i < arr.size(); i++) {
        int tmp = arr[i], j = i;
        for (; j > 0 && arr[j - 1] > tmp; j--) {
            arr[j] = arr[j - 1];
        }
        arr[j] =  tmp;
    }
}

// ************ 希尔排序 ************* //

void shellSort(vector<int>& arr) {
    for (int gap = arr.size() / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < arr.size(); i++) {
            int tmp = arr[i];
            int j = i;
            for (; j >= gap && arr[j - gap] > tmp; j--) {
                arr[j] = arr[j - gap];
            }
            arr[j] = tmp;
        }
    }
}

// ************ 归并排序 ************* //

void merge(vector<int>&arr, int l, int m, int r)
{
    vector<int> tmpL(arr.begin() + l, arr.begin() + m);
    vector<int> tmpR(arr.begin() + m, arr.begin() + r + 1);
    int i = 0, j = 0, k = l;
    while(i < tmpL.size() && j < tmpR.size()) {
        if (tmpL[i] <= tmpR[j]) {
            arr[k++] = tmpL[i++];
            continue;
        }
        arr[k++] = tmpR[j++];
    }
    while(i < tmpL.size()) arr[k++] = tmpL[i++];
    while(j < tmpR.size()) arr[k++] = tmpR[j++];
}

void mergeSort(vector<int>& arr, int l, int r)
{
    if (l >= r) return;
    int m = l + (r - l) / 2;
    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);
    merge(arr, l, m + 1, r);
} 

// ************ 快速排序 ************* //

pair<int, int> partion(vector<int>& arr, int l, int r)
{
    int tmp = arr[r];
    int c = l;
    l--, r++;
    while(c < r) {
        if(arr[c] < tmp) swap(arr[++l], arr[c++]);
        else if(arr[c] > tmp) swap(arr[--r], arr[c]); // 注意这里c不用++
        else c++;
    }
    return make_pair(l, r);
}

void quickSort(vector<int>& arr, int l, int r)
{
    if (l >= r) return;
    srand(time(NULL));
    // 注意这里rand() % (r - l) + l + 1值和rand() % ((r - l) + l + 1)不一样
    swap(arr[r], arr[(rand() % (r - l)) + l + 1]); 
    pair<int, int> range = partion(arr, l, r);
    quickSort(arr, l, range.first);
    quickSort(arr, range.second, r);
}

// ************ 堆排序 ************* //
void swap(int &num1, int &num2) {
    int tmp = num1;
    num1 = num2;
    num2 = tmp;
}

// 一次heapify只能保证nodeIdx节点满足堆的性质
void heapify(vector<int> &arr, int len, int nodeIdx) {
    if (nodeIdx >= len) {
        return;
    }
    int lchild = nodeIdx * 2 + 1;
    int rchild = nodeIdx * 2 + 2;
    int maxIdx = nodeIdx;

    if (lchild < len && arr[maxIdx] < arr[lchild]) {
        maxIdx = lchild;
    }
    if (rchild < len && arr[maxIdx] < arr[rchild]) {
        maxIdx = rchild;
    }
    if (maxIdx != nodeIdx) {
        swap(arr[maxIdx], arr[nodeIdx]);
        // 子节点值有更新不能保证子节点值比它的左右节点值大需要继续调整
        heapify(arr, len, maxIdx); 
    }
}

// 保证每个节点满足堆的性质
void build_heap(vector<int> &arr) {
    int len = arr.size();
    for (int i = (len - 1) / 2; i >= 0; i--) {
        heapify(arr, len, i);
    }
}

void heapSort(vector<int> &arr) {
    build_heap(arr);
    for (int i = arr.size() - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0); // 这一这里传的是i不是size，因为最后一个数已经有序
    }
}

int main()
{
    vector<int> arr = {5, 6, 8, 10, 2, 1};
    // vector<int> arr = {1, 2, 3, 4, 5, 6};
    vector<int> arr2 = {6, 5, 4, 3, 2, 1};
    vector<int> arr3 = {1};
    // bubbleSort(arr);
    // insertSort(arr);
    // insertSort(arr2);

    quickSort(arr, 0, arr.size() - 1);
    quickSort(arr2, 0, arr2.size() - 1);
    quickSort(arr3, 0, arr3.size() - 1);

    for (auto x : arr) {
        cout << x << " ";
    }
    cout << endl;
    for (auto x : arr2) {
        cout << x << " ";
    }
    cout << endl;

    for (auto x : arr3) {
        cout << x << " ";
    }
    cout << endl;
    return 0;
}