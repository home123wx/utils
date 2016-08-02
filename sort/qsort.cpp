#include <stdio.h>
#include <vector>

using std::vector;

void show(const vector<int>& arr);
void quick_sort(vector<int>& arr, int left, int right);


int main()
{
    vector<int> arr;
    arr.push_back(3);
    arr.push_back(1);
    arr.push_back(8);
    arr.push_back(0);
    arr.push_back(2);

    show(arr);
    quick_sort(arr, 0, arr.size()-1 );
    show(arr);
}

void quick_sort(vector<int>& arr, int left, int right)
{
    if (left >= right) {
        return;
    }

    int beg = left;
    int end = right;
    int key = arr[beg];

    while (beg < end) {
        while (beg < end && arr[end] >= key) {
            --end;
        }
        if (beg < end) {
            arr[beg++] = arr[end];
        }

        while (beg < end && arr[beg] < key) {
            ++beg;
        }
        if (beg < end) {
            arr[end--] = arr[beg];
        }
    }
    arr[beg] = key;

    quick_sort(arr, left, beg - 1);
    quick_sort(arr, beg + 1, right);
}

void show(const vector<int>& arr)
{
    for (size_t i = 0; i < arr.size(); ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}
