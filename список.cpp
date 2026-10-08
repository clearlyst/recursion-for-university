#include <iostream>
#include <vector>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;

    ListNode(int x) : val(x), next(nullptr) {}
};

ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
    ListNode dummy(0);
    ListNode* current = &dummy;

    while (list1 && list2) {
        if (list1->val <= list2->val) {
            current->next = list1;
            list1 = list1->next;
        } else {
            current->next = list2;
            list2 = list2->next;
        }
        current = current->next;
    }

    current->next = list1 ? list1 : list2;
    return dummy.next;
}

ListNode* deleteDuplicates(ListNode* head) {
    ListNode* current = head;

    while (current && current->next) {
        if (current->val == current->next->val)
            current->next = current->next->next;
        else
            current = current->next;
    }

    return head;
}

bool hasCycle(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast)
            return true;
    }

    return false;
}

void reorderList(ListNode* head) {
    if (!head || !head->next)
        return;

    ListNode* slow = head;
    ListNode* fast = head;

    while (fast->next && fast->next->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    ListNode* second = slow->next;
    slow->next = nullptr;

    ListNode* prev = nullptr;

    while (second) {
        ListNode* next = second->next;
        second->next = prev;
        prev = second;
        second = next;
    }

    second = prev;

    while (second) {
        ListNode* firstNext = head->next;
        ListNode* secondNext = second->next;

        head->next = second;
        second->next = firstNext;

        head = firstNext;
        second = secondNext;
    }
}

void deleteNode(ListNode* node) {
    node->val = node->next->val;
    node->next = node->next->next;
}

ListNode* doubleIt(ListNode* head) {
    ListNode* prev = nullptr;
    ListNode* current = head;

    while (current) {
        ListNode* next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    head = prev;

    int carry = 0;
    current = head;
    prev = nullptr;

    while (current) {
        int value = current->val * 2 + carry;
        current->val = value % 10;
        carry = value / 10;

        prev = current;
        current = current->next;
    }

    if (carry) {
        prev->next = new ListNode(carry);
    }

    prev = nullptr;
    current = head;

    while (current) {
        ListNode* next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    return prev;
}

ListNode* mergeKLists(vector<ListNode*>& lists) {
    if (lists.empty())
        return nullptr;

    while (lists.size() > 1) {
        vector<ListNode*> merged;

        for (int i = 0; i < lists.size(); i += 2) {
            ListNode* list1 = lists[i];
            ListNode* list2 = i + 1 < lists.size() ? lists[i + 1] : nullptr;

            merged.push_back(mergeTwoLists(list1, list2));
        }

        lists = merged;
    }

    return lists[0];
}

ListNode* reverseKGroup(ListNode* head, int k) {
    ListNode* current = head;
    int count = 0;

    while (current && count < k) {
        current = current->next;
        count++;
    }

    if (count < k)
        return head;

    ListNode* prev = nullptr;
    current = head;

    for (int i = 0; i < k; i++) {
        ListNode* next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    head->next = reverseKGroup(current, k);

    return prev;
}

ListNode* partition(ListNode* head, int x) {
    ListNode before(0);
    ListNode after(0);

    ListNode* beforeCurrent = &before;
    ListNode* afterCurrent = &after;

    while (head) {
        if (head->val < x) {
            beforeCurrent->next = head;
            beforeCurrent = beforeCurrent->next;
        } else {
            afterCurrent->next = head;
            afterCurrent = afterCurrent->next;
        }

        head = head->next;
    }

    afterCurrent->next = nullptr;
    beforeCurrent->next = after.next;

    return before.next;
}

ListNode* createList(const vector<int>& values) {
    ListNode dummy(0);
    ListNode* current = &dummy;

    for (int value : values) {
        current->next = new ListNode(value);
        current = current->next;
    }

    return dummy.next;
}

void printList(ListNode* head) {
    cout << "[ ";

    while (head) {
        cout << head->val;
        if (head->next)
            cout << ", ";
        head = head->next;
    }

    cout << " ]" << endl;
}

void deleteList(ListNode* head) {
    while (head) {
        ListNode* next = head->next;
        delete head;
        head = next;
    }
}

int main() {
    ListNode* list1 = createList({1, 2, 4});
    ListNode* list2 = createList({1, 3, 4});
    ListNode* result1 = mergeTwoLists(list1, list2);
    printList(result1);
    deleteList(result1);

    ListNode* list3 = createList({1, 1, 2, 3, 3});
    list3 = deleteDuplicates(list3);
    printList(list3);
    deleteList(list3);

    ListNode* list4 = createList({3, 2, 0, -4});
    list4->next->next->next->next = list4->next;
    cout << (hasCycle(list4) ? "true" : "false") << endl;

    ListNode* list5 = createList({1, 2, 3, 4, 5});
    reorderList(list5);
    printList(list5);
    deleteList(list5);

    ListNode* list6 = createList({4, 5, 1, 9});
    deleteNode(list6->next);
    printList(list6);
    deleteList(list6);

    ListNode* list7 = createList({1, 8, 9});
    list7 = doubleIt(list7);
    printList(list7);
    deleteList(list7);

    vector<ListNode*> lists;
    lists.push_back(createList({1, 4, 5}));
    lists.push_back(createList({1, 3, 4}));
    lists.push_back(createList({2, 6}));

    ListNode* list8 = mergeKLists(lists);
    printList(list8);
    deleteList(list8);

    ListNode* list9 = createList({1, 2, 3, 4, 5});
    list9 = reverseKGroup(list9, 2);
    printList(list9);
    deleteList(list9);

    ListNode* list10 = createList({1, 4, 3, 2, 5, 2});
    list10 = partition(list10, 3);
    printList(list10);
    deleteList(list10);

    return 0;
}
