#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

string reverseMain(const string& text) {
    if (text.size() <= 1) {
        return text;
    }

    return reverseMain(text.substr(1)) + text[0];
}

void reverseTailHelper(const string& text, int index, string& result) {
    if (index < 0) {
        return;
    }

    result += text[index];
    reverseTailHelper(text, index - 1, result);
}

string reverseTail(const string& text) {
    string result;
    result.reserve(text.size());

    reverseTailHelper(text, static_cast<int>(text.size()) - 1, result);

    return result;
}

class ListNode {
public:
    int value;
    ListNode* next;

    ListNode(int v = 0, ListNode* n = nullptr)
        : value(v), next(n) {
    }
};

ListNode* swapPairsMain(ListNode* head) {
    if (!head || !head->next) {
        return head;
    }

    ListNode* second = head->next;

    head->next = swapPairsMain(second->next);
    second->next = head;

    return second;
}

ListNode* swapPairsIter(ListNode* head) {
    ListNode dummy(0, head);
    ListNode* prev = &dummy;

    while (head && head->next) {
        ListNode* first = head;
        ListNode* second = head->next;

        prev->next = second;
        first->next = second->next;
        second->next = first;

        prev = first;
        head = first->next;
    }

    return dummy.next;
}

ListNode* createList(const vector<int>& values) {
    ListNode dummy;
    ListNode* current = &dummy;

    for (int value : values) {
        current->next = new ListNode(value);
        current = current->next;
    }

    return dummy.next;
}

void printList(ListNode* head) {
    while (head) {
        cout << head->value;

        if (head->next) {
            cout << " -> ";
        }

        head = head->next;
    }

    cout << endl;
}

void deleteList(ListNode* head) {
    while (head) {
        ListNode* temp = head;
        head = head->next;
        delete temp;
    }
}

unordered_map<int, long long> fibCache;

long long fibMain(int n) {
    if (n < 2) {
        return n;
    }

    if (fibCache.count(n)) {
        return fibCache[n];
    }

    fibCache[n] = fibMain(n - 1) + fibMain(n - 2);

    return fibCache[n];
}

long long fibIter(int n) {
    if (n < 2) {
        return n;
    }

    long long a = 0;
    long long b = 1;

    for (int i = 2; i <= n; ++i) {
        long long next = a + b;
        a = b;
        b = next;
    }

    return b;
}

int climbStairsMain(int n) {
    if (n <= 2) {
        return n;
    }

    return climbStairsMain(n - 1) + climbStairsMain(n - 2);
}

int climbStairsIter(int n) {
    if (n <= 2) {
        return n;
    }

    int a = 1;
    int b = 2;

    for (int i = 3; i <= n; ++i) {
        int next = a + b;
        a = b;
        b = next;
    }

    return b;
}

double fastPow(double x, int n) {
    if (n == 0) {
        return 1.0;
    }

    if (n < 0) {
        return 1.0 / fastPow(x, -n);
    }

    double half = fastPow(x, n / 2);

    if (n % 2 == 0) {
        return half * half;
    }

    return x * half * half;
}

int main() {

    //1st task
    cout << reverseMain("tiger") << endl;
    cout << reverseTail("tiger") << endl;

    cout << endl;

    //2nd task
    ListNode* list1 = createList({ 1, 2, 3, 4 });
    ListNode* swapped1 = swapPairsMain(list1);
    printList(swapped1);

    ListNode* list2 = createList({ 1, 2, 3, 4 });
    ListNode* swapped2 = swapPairsIter(list2);
    printList(swapped2);

    deleteList(swapped1);
    deleteList(swapped2);

    cout << endl;

    //3rd task
    cout << fibMain(2) << endl;
    cout << fibMain(3) << endl;
    cout << fibMain(4) << endl;

    cout << fibIter(2) << endl;
    cout << fibIter(3) << endl;
    cout << fibIter(4) << endl;

    cout << endl;

    //4th task
    cout << climbStairsMain(2) << endl;
    cout << climbStairsMain(3) << endl;

    cout << climbStairsIter(2) << endl;
    cout << climbStairsIter(3) << endl;

    cout << endl;

	//5th task
    cout << fastPow(2.0, 10) << endl;
    cout << fastPow(2.1, 3) << endl;
    cout << fastPow(2.0, -2) << endl;

    return 0;
}