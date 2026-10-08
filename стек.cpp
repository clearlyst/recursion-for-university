#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <algorithm>
using namespace std;

bool isValid(string s) {
    stack<char> st;

    for (char c : s) {
        if (c == '(' || c == '[' || c == '{') {
            st.push(c);
        } else {
            if (st.empty())
                return false;

            char top = st.top();
            st.pop();

            if ((c == ')' && top != '(') ||
                (c == ']' && top != '[') ||
                (c == '}' && top != '{'))
                return false;
        }
    }

    return st.empty();
}

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

vector<int> inorderTraversal(TreeNode* root) {
    vector<int> result;
    stack<TreeNode*> st;

    TreeNode* current = root;

    while (current || !st.empty()) {
        while (current) {
            st.push(current);
            current = current->left;
        }

        current = st.top();
        st.pop();

        result.push_back(current->val);

        current = current->right;
    }

    return result;
}

class MinStack {
private:
    stack<int> values;
    stack<int> minimums;

public:
    MinStack() {}

    void push(int val) {
        values.push(val);

        if (minimums.empty())
            minimums.push(val);
        else
            minimums.push(min(val, minimums.top()));
    }

    void pop() {
        values.pop();
        minimums.pop();
    }

    int top() {
        return values.top();
    }

    int getMin() {
        return minimums.top();
    }
};

class MyQueue {
private:
    stack<int> input;
    stack<int> output;

    void moveElements() {
        if (output.empty()) {
            while (!input.empty()) {
                output.push(input.top());
                input.pop();
            }
        }
    }

public:
    MyQueue() {}

    void push(int x) {
        input.push(x);
    }

    int pop() {
        moveElements();

        int value = output.top();
        output.pop();

        return value;
    }

    int peek() {
        moveElements();
        return output.top();
    }

    bool empty() {
        return input.empty() && output.empty();
    }
};

string decodeString(string s) {
    stack<int> numbers;
    stack<string> strings;

    string current = "";
    int number = 0;

    for (char c : s) {
        if (isdigit(c)) {
            number = number * 10 + (c - '0');
        } else if (c == '[') {
            numbers.push(number);
            strings.push(current);

            number = 0;
            current = "";
        } else if (c == ']') {
            int repeat = numbers.top();
            numbers.pop();

            string previous = strings.top();
            strings.pop();

            string temp = "";

            for (int i = 0; i < repeat; i++)
                temp += current;

            current = previous + temp;
        } else {
            current += c;
        }
    }

    return current;
}

int evalRPN(vector<string>& tokens) {
    stack<int> st;

    for (string token : tokens) {
        if (token == "+" || token == "-" ||
            token == "*" || token == "/") {

            int b = st.top();
            st.pop();

            int a = st.top();
            st.pop();

            if (token == "+")
                st.push(a + b);
            else if (token == "-")
                st.push(a - b);
            else if (token == "*")
                st.push(a * b);
            else
                st.push(a / b);
        } else {
            st.push(stoi(token));
        }
    }

    return st.top();
}

int longestValidParentheses(string s) {
    stack<int> st;
    st.push(-1);

    int answer = 0;

    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '(') {
            st.push(i);
        } else {
            st.pop();

            if (st.empty()) {
                st.push(i);
            } else {
                answer = max(answer, i - st.top());
            }
        }
    }

    return answer;
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
    cout << "1. "
         << (isValid("()[]{}") ? "true" : "false")
         << endl;

    TreeNode* root = new TreeNode(1);
    root->right = new TreeNode(2);
    root->right->left = new TreeNode(3);

    cout << "2. ";
    printVector(inorderTraversal(root));

    MinStack minStack;

    minStack.push(-2);
    minStack.push(0);
    minStack.push(-3);

    cout << "3. Min = " << minStack.getMin() << endl;

    minStack.pop();

    cout << "   Top = " << minStack.top() << endl;
    cout << "   Min = " << minStack.getMin() << endl;

    MyQueue myQueue;

    myQueue.push(1);
    myQueue.push(2);

    cout << "4. Peek = " << myQueue.peek() << endl;
    cout << "   Pop = " << myQueue.pop() << endl;
    cout << "   Empty = "
         << (myQueue.empty() ? "true" : "false")
         << endl;

    cout << "5. " << decodeString("3[a2[c]]") << endl;

    vector<string> tokens = {
        "2", "1", "+", "3", "*"
    };

    cout << "6. " << evalRPN(tokens) << endl;

    cout << "7. "
         << longestValidParentheses(")()())")
         << endl;

    return 0;
}
