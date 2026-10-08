#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int findMaxConsecutiveOnes(const vector<int>& nums) {
    int current = 0;
    int maximum = 0;

    for (int x : nums) {
        if (x == 1) {
            current++;
            maximum = max(maximum, current);
        } else {
            current = 0;
        }
    }

    return maximum;
}

int findNumbers(const vector<int>& nums) {
    int count = 0;

    for (int x : nums) {
        int digits = 0;
        int n = x;

        while (n > 0) {
            digits++;
            n /= 10;
        }

        if (digits % 2 == 0)
            count++;
    }

    return count;
}

vector<int> sortedSquares(const vector<int>& nums) {
    vector<int> result(nums.size());
    int left = 0;
    int right = nums.size() - 1;
    int pos = nums.size() - 1;

    while (left <= right) {
        int leftSquare = nums[left] * nums[left];
        int rightSquare = nums[right] * nums[right];

        if (leftSquare > rightSquare) {
            result[pos] = leftSquare;
            left++;
        } else {
            result[pos] = rightSquare;
            right--;
        }

        pos--;
    }

    return result;
}

void duplicateZeros(vector<int>& arr) {
    int n = arr.size();

    for (int i = 0; i < n; i++) {
        if (arr[i] == 0) {
            for (int j = n - 1; j > i; j--)
                arr[j] = arr[j - 1];

            if (i + 1 < n)
                arr[i + 1] = 0;

            i++;
        }
    }
}

void merge(vector<int>& nums1, int m, const vector<int>& nums2, int n) {
    int i = m - 1;
    int j = n - 1;
    int k = m + n - 1;

    while (j >= 0) {
        if (i >= 0 && nums1[i] > nums2[j]) {
            nums1[k] = nums1[i];
            i--;
        } else {
            nums1[k] = nums2[j];
            j--;
        }

        k--;
    }
}

int removeDuplicates(vector<int>& nums) {
    if (nums.empty())
        return 0;

    int k = 1;

    for (int i = 1; i < nums.size(); i++) {
        if (nums[i] != nums[k - 1]) {
            nums[k] = nums[i];
            k++;
        }
    }

    return k;
}

bool containsPair(const vector<int>& arr) {
    for (int i = 0; i < arr.size(); i++) {
        for (int j = 0; j < arr.size(); j++) {
            if (i != j && arr[i] == 2 * arr[j])
                return true;
        }
    }

    return false;
}

bool validMountainArray(const vector<int>& arr) {
    if (arr.size() < 3)
        return false;

    int i = 0;

    while (i + 1 < arr.size() && arr[i] < arr[i + 1])
        i++;

    if (i == 0 || i == arr.size() - 1)
        return false;

    while (i + 1 < arr.size() && arr[i] > arr[i + 1])
        i++;

    return i == arr.size() - 1;
}

void replaceElements(vector<int>& arr) {
    int maximum = -1;

    for (int i = arr.size() - 1; i >= 0; i--) {
        int current = arr[i];
        arr[i] = maximum;

        if (current > maximum)
            maximum = current;
    }
}

vector<int> sortArrayByParity(vector<int>& nums) {
    int left = 0;
    int right = nums.size() - 1;

    while (left < right) {
        if (nums[left] % 2 != 0 && nums[right] % 2 == 0) {
            swap(nums[left], nums[right]);
            left++;
            right--;
        } else {
            if (nums[left] % 2 == 0)
                left++;

            if (nums[right] % 2 != 0)
                right--;
        }
    }

    return nums;
}

void printVector(const vector<int>& nums) {
    cout << "[ ";

    for (int i = 0; i < nums.size(); i++) {
        cout << nums[i];

        if (i + 1 < nums.size())
            cout << ", ";
    }

    cout << " ]" << endl;
}

int main() {
    vector<int> nums1 = {1, 1, 0, 1, 1, 1};
    cout << findMaxConsecutiveOnes(nums1) << endl;

    vector<int> nums2 = {12, 345, 2, 6, 7896};
    cout << findNumbers(nums2) << endl;

    vector<int> nums3 = {-4, -1, 0, 3, 10};
    printVector(sortedSquares(nums3));

    vector<int> nums4 = {1, 0, 2, 3, 0, 4, 5, 0};
    duplicateZeros(nums4);
    printVector(nums4);

    vector<int> nums5 = {1, 2, 3, 0, 0, 0};
    vector<int> nums6 = {2, 5, 6};
    merge(nums5, 3, nums6, 3);
    printVector(nums5);

    vector<int> nums7 = {0, 0, 1, 1, 1, 2, 2, 3, 3, 4};
    int k = removeDuplicates(nums7);
    cout << k << endl;
    printVector(nums7);

    vector<int> nums8 = {10, 2, 5, 3};
    cout << (containsPair(nums8) ? "true" : "false") << endl;

    vector<int> nums9 = {0, 3, 2, 1};
    cout << (validMountainArray(nums9) ? "true" : "false") << endl;

    vector<int> nums10 = {17, 18, 5, 4, 6, 1};
    replaceElements(nums10);
    printVector(nums10);

    vector<int> nums11 = {3, 1, 2, 4};
    sortArrayByParity(nums11);
    printVector(nums11);

    return 0;
}
