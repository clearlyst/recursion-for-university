#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <string>
#include <unordered_map>
#include <algorithm>
using namespace std;

int firstUniqChar(string s) {
    vector<int> count(26, 0);

    for (char c : s)
        count[c - 'a']++;

    for (int i = 0; i < s.size(); i++) {
        if (count[s[i] - 'a'] == 1)
            return i;
    }

    return -1;
}

class MyStack {
private:
    queue<int> q;

public:
    MyStack() {}

    void push(int x) {
        q.push(x);

        int size = q.size();

        for (int i = 0; i < size - 1; i++) {
            q.push(q.front());
            q.pop();
        }
    }

    int pop() {
        int value = q.front();
        q.pop();
        return value;
    }

    int top() {
        return q.front();
    }

    bool empty() {
        return q.empty();
    }
};

class RecentCounter {
private:
    queue<int> requests;

public:
    RecentCounter() {}

    int ping(int t) {
        requests.push(t);

        while (requests.front() < t - 3000)
            requests.pop();

        return requests.size();
    }
};

class MyCircularDeque {
private:
    vector<int> data;
    int front;
    int rear;
    int size;
    int capacity;

public:
    MyCircularDeque(int k) {
        data.resize(k);
        front = 0;
        rear = 0;
        size = 0;
        capacity = k;
    }

    bool insertFront(int value) {
        if (isFull())
            return false;

        front = (front - 1 + capacity) % capacity;
        data[front] = value;
        size++;

        return true;
    }

    bool insertLast(int value) {
        if (isFull())
            return false;

        data[rear] = value;
        rear = (rear + 1) % capacity;
        size++;

        return true;
    }

    bool deleteFront() {
        if (isEmpty())
            return false;

        front = (front + 1) % capacity;
        size--;

        return true;
    }

    bool deleteLast() {
        if (isEmpty())
            return false;

        rear = (rear - 1 + capacity) % capacity;
        size--;

        return true;
    }

    int getFront() {
        if (isEmpty())
            return -1;

        return data[front];
    }

    int getRear() {
        if (isEmpty())
            return -1;

        return data[(rear - 1 + capacity) % capacity];
    }

    bool isEmpty() {
        return size == 0;
    }

    bool isFull() {
        return size == capacity;
    }
};

class MyCircularQueue {
private:
    vector<int> data;
    int front;
    int rear;
    int size;
    int capacity;

public:
    MyCircularQueue(int k) {
        data.resize(k);
        front = 0;
        rear = 0;
        size = 0;
        capacity = k;
    }

    bool enQueue(int value) {
        if (isFull())
            return false;

        data[rear] = value;
        rear = (rear + 1) % capacity;
        size++;

        return true;
    }

    bool deQueue() {
        if (isEmpty())
            return false;

        front = (front + 1) % capacity;
        size--;

        return true;
    }

    int Front() {
        if (isEmpty())
            return -1;

        return data[front];
    }

    int Rear() {
        if (isEmpty())
            return -1;

        return data[(rear - 1 + capacity) % capacity];
    }

    bool isEmpty() {
        return size == 0;
    }

    bool isFull() {
        return size == capacity;
    }
};

vector<int> movesToStamp(string stamp, string target) {
    int n = target.size();
    int m = stamp.size();

    vector<char> current(target.begin(), target.end());
    vector<bool> changed(n, false);
    vector<int> result;

    int total = 0;

    while (total < n) {
        bool progress = false;

        for (int i = 0; i <= n - m; i++) {
            bool canStamp = false;
            bool valid = true;

            for (int j = 0; j < m; j++) {
                if (current[i + j] == '?')
                    continue;

                if (current[i + j] != stamp[j]) {
                    valid = false;
                    break;
                }

                canStamp = true;
            }

            if (valid && canStamp && !changed[i]) {
                changed[i] = true;
                result.push_back(i);
                progress = true;

                for (int j = 0; j < m; j++) {
                    if (current[i + j] != '?') {
                        current[i + j] = '?';
                        total++;
                    }
                }

                if (total == n)
                    break;
            }
        }

        if (!progress)
            return {};
    }

    reverse(result.begin(), result.end());

    return result;
}

vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    deque<int> dq;
    vector<int> result;

    for (int i = 0; i < nums.size(); i++) {
        while (!dq.empty() && dq.front() <= i - k)
            dq.pop_front();

        while (!dq.empty() && nums[dq.back()] <= nums[i])
            dq.pop_back();

        dq.push_back(i);

        if (i >= k - 1)
            result.push_back(nums[dq.front()]);
    }

    return result;
}

void printVector(const vector<int>& values) {
    cout << "[";

    for (int i = 0; i < values.size(); i++) {
        cout << values[i];

        if (i + 1 < values.size())
            cout << ", ";
    }

    cout << "]" << endl;
}

int main() {
    cout << "1. " << firstUniqChar("loveleopard") << endl;

    MyStack myStack;

    myStack.push(1);
    myStack.push(2);

    cout << "2. Top = " << myStack.top() << endl;
    cout << "   Pop = " << myStack.pop() << endl;
    cout << "   Empty = "
         << (myStack.empty() ? "true" : "false")
         << endl;

    RecentCounter recentCounter;

    cout << "3. "
         << recentCounter.ping(1) << " "
         << recentCounter.ping(100) << " "
         << recentCounter.ping(3001) << " "
         << recentCounter.ping(3002)
         << endl;

    MyCircularDeque circularDeque(3);

    cout << "4. "
         << (circularDeque.insertLast(1) ? "true " : "false ")
         << (circularDeque.insertLast(2) ? "true " : "false ")
         << (circularDeque.insertFront(3) ? "true " : "false ")
         << (circularDeque.insertFront(4) ? "true " : "false ")
         << endl;

    cout << "   Rear = " << circularDeque.getRear() << endl;
    cout << "   Full = "
         << (circularDeque.isFull() ? "true" : "false")
         << endl;

    circularDeque.deleteLast();
    circularDeque.insertFront(4);

    cout << "   Front = " << circularDeque.getFront() << endl;

    MyCircularQueue circularQueue(3);

    cout << "5. "
         << (circularQueue.enQueue(1) ? "true " : "false ")
         << (circularQueue.enQueue(2) ? "true " : "false ")
         << (circularQueue.enQueue(3) ? "true " : "false ")
         << (circularQueue.enQueue(4) ? "true " : "false ")
         << endl;

    cout << "   Rear = " << circularQueue.Rear() << endl;
    cout << "   Full = "
         << (circularQueue.isFull() ? "true" : "false")
         << endl;

    circularQueue.deQueue();
    circularQueue.enQueue(4);

    cout << "   Rear = " << circularQueue.Rear() << endl;

    vector<int> stampResult = movesToStamp("abc", "ababc");

    cout << "6. ";
    printVector(stampResult);

    vector<int> nums = {1, 3, -1, -3, 5, 3, 6, 7};

    cout << "7. ";
    printVector(maxSlidingWindow(nums, 3));

    return 0;
}
