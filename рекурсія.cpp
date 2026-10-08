#include <iostream>
#include <string>

using namespace std;

string reverseString(const string& text, int index) {
    if (index < 0) {
        return "";
    }

    return text[index] + reverseString(text, index - 1);
}

class ListNode {
public:
    int value;
    ListNode* next;

    ListNode(int v = 0, ListNode* n = nullptr)
        : value(v), next(n) {
    }
};

ListNode* createList(const int values[], int size, int index = 0) {
    if (index >= size) {
        return nullptr;
    }

    return new ListNode(
        values[index],
        createList(values, size, index + 1)
    );
}

ListNode* swapPairs(ListNode* head) {
    if (head == nullptr || head->next == nullptr) {
        return head;
    }

    ListNode* second = head->next;
    head->next = swapPairs(second->next);
    second->next = head;

    return second;
}

void printList(ListNode* head) {
    if (head == nullptr) {
        cout << endl;
        return;
    }

    cout << head->value;

    if (head->next != nullptr) {
        cout << " -> ";
    }

    printList(head->next);
}

void deleteList(ListNode* head) {
    if (head == nullptr) {
        return;
    }

    deleteList(head->next);
    delete head;
}

long long fibonacci(int n) {
    if (n == 0) {
        return 0;
    }

    if (n == 1) {
        return 1;
    }

    return fibonacci(n - 1) + fibonacci(n - 2);
}

int climbStairs(int n) {
    if (n <= 2) {
        return n;
    }

    return climbStairs(n - 1) + climbStairs(n - 2);
}

double fastPow(double x, long long n) {
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
    cout << "Завдання 1:" << endl;
    string text = "tiger";
    cout << "Вхідний рядок: " << text << endl;
    cout << "Результат: " << reverseString(text, static_cast<int>(text.size()) - 1) << endl;
    cout << endl;

    cout << "Завдання 2:" << endl;
    int values[] = {1, 2, 3, 4};
    ListNode* head = createList(values, 4);
    cout << "Початковий список: ";
    printList(head);
    head = swapPairs(head);
    cout << "Після перестановки: ";
    printList(head);
    deleteList(head);
    cout << endl;

    cout << "Завдання 3:" << endl;
    cout << "F(2) = " << fibonacci(2) << endl;
    cout << "F(3) = " << fibonacci(3) << endl;
    cout << "F(4) = " << fibonacci(4) << endl;
    cout << endl;

    cout << "Завдання 4:" << endl;
    cout << "n = 2: " << climbStairs(2) << endl;
    cout << "n = 3: " << climbStairs(3) << endl;
    cout << endl;

    cout << "Завдання 5:" << endl;
    cout << "2^10 = " << fastPow(2.0, 10) << endl;
    cout << "2.1^3 = " << fastPow(2.1, 3) << endl;
    cout << "2^(-2) = " << fastPow(2.0, -2) << endl;
    cout << endl;

    return 0;
}
