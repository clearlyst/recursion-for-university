#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <sstream>
#include <algorithm>
#include <climits>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

bool isSameTree(TreeNode* p, TreeNode* q) {
    queue<pair<TreeNode*, TreeNode*>> qnodes;
    qnodes.push({p, q});

    while (!qnodes.empty()) {
        auto [a, b] = qnodes.front();
        qnodes.pop();

        if (!a && !b)
            continue;

        if (!a || !b || a->val != b->val)
            return false;

        qnodes.push({a->left, b->left});
        qnodes.push({a->right, b->right});
    }

    return true;
}

bool isSymmetric(TreeNode* root) {
    if (!root)
        return true;

    queue<pair<TreeNode*, TreeNode*>> qnodes;
    qnodes.push({root->left, root->right});

    while (!qnodes.empty()) {
        auto [left, right] = qnodes.front();
        qnodes.pop();

        if (!left && !right)
            continue;

        if (!left || !right || left->val != right->val)
            return false;

        qnodes.push({left->left, right->right});
        qnodes.push({left->right, right->left});
    }

    return true;
}

TreeNode* invertTree(TreeNode* root) {
    if (!root)
        return nullptr;

    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        TreeNode* node = q.front();
        q.pop();

        swap(node->left, node->right);

        if (node->left)
            q.push(node->left);

        if (node->right)
            q.push(node->right);
    }

    return root;
}

int kthSmallest(TreeNode* root, int k) {
    vector<TreeNode*> stack;
    TreeNode* current = root;

    while (current || !stack.empty()) {
        while (current) {
            stack.push_back(current);
            current = current->left;
        }

        current = stack.back();
        stack.pop_back();

        k--;

        if (k == 0)
            return current->val;

        current = current->right;
    }

    return -1;
}

string serialize(TreeNode* root) {
    if (!root)
        return "null";

    string result;
    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        TreeNode* node = q.front();
        q.pop();

        if (node) {
            result += to_string(node->val) + ",";
            q.push(node->left);
            q.push(node->right);
        } else {
            result += "null,";
        }
    }

    return result;
}

TreeNode* deserialize(const string& data) {
    if (data.empty() || data == "null")
        return nullptr;

    vector<string> values;
    string value;
    stringstream ss(data);

    while (getline(ss, value, ','))
        if (!value.empty())
            values.push_back(value);

    if (values.empty() || values[0] == "null")
        return nullptr;

    TreeNode* root = new TreeNode(stoi(values[0]));
    queue<TreeNode*> q;
    q.push(root);

    int index = 1;

    while (!q.empty() && index < values.size()) {
        TreeNode* node = q.front();
        q.pop();

        if (values[index] != "null") {
            node->left = new TreeNode(stoi(values[index]));
            q.push(node->left);
        }

        index++;

        if (index < values.size() && values[index] != "null") {
            node->right = new TreeNode(stoi(values[index]));
            q.push(node->right);
        }

        index++;
    }

    return root;
}

int maxPathSum(TreeNode* root) {
    if (!root)
        return 0;

    vector<pair<TreeNode*, bool>> stack;
    map<TreeNode*, int> gain;
    int answer = INT_MIN;

    stack.push_back({root, false});

    while (!stack.empty()) {
        auto [node, visited] = stack.back();
        stack.pop_back();

        if (!node)
            continue;

        if (!visited) {
            stack.push_back({node, true});
            stack.push_back({node->right, false});
            stack.push_back({node->left, false});
        } else {
            int left = max(0, gain[node->left]);
            int right = max(0, gain[node->right]);

            answer = max(answer, node->val + left + right);
            gain[node] = node->val + max(left, right);
        }
    }

    return answer;
}

int minCameraCover(TreeNode* root) {
    if (!root)
        return 0;

    const int NOT_COVERED = 0;
    const int COVERED = 1;
    const int CAMERA = 2;

    map<TreeNode*, int> state;
    int cameras = 0;

    vector<pair<TreeNode*, bool>> stack;
    stack.push_back({root, false});

    while (!stack.empty()) {
        auto [node, visited] = stack.back();
        stack.pop_back();

        if (!node)
            continue;

        if (!visited) {
            stack.push_back({node, true});
            stack.push_back({node->right, false});
            stack.push_back({node->left, false});
        } else {
            int left = node->left ? state[node->left] : COVERED;
            int right = node->right ? state[node->right] : COVERED;

            if (left == NOT_COVERED || right == NOT_COVERED) {
                state[node] = CAMERA;
                cameras++;
            } else if (left == CAMERA || right == CAMERA) {
                state[node] = COVERED;
            } else {
                state[node] = NOT_COVERED;
            }
        }
    }

    if (state[root] == NOT_COVERED)
        cameras++;

    return cameras;
}

vector<vector<int>> verticalTraversal(TreeNode* root) {
    vector<tuple<int, int, int>> nodes;

    if (!root)
        return {};

    queue<tuple<TreeNode*, int, int>> q;
    q.push({root, 0, 0});

    while (!q.empty()) {
        auto [node, row, col] = q.front();
        q.pop();

        nodes.push_back({col, row, node->val});

        if (node->left)
            q.push({node->left, row + 1, col - 1});

        if (node->right)
            q.push({node->right, row + 1, col + 1});
    }

    sort(nodes.begin(), nodes.end());

    vector<vector<int>> result;
    int currentColumn = INT_MIN;

    for (auto [col, row, value] : nodes) {
        if (col != currentColumn) {
            result.push_back({});
            currentColumn = col;
        }

        result.back().push_back(value);
    }

    return result;
}

TreeNode* recoverFromPreorder(string traversal) {
    vector<TreeNode*> stack;
    int i = 0;

    while (i < traversal.size()) {
        int depth = 0;

        while (i < traversal.size() && traversal[i] == '-') {
            depth++;
            i++;
        }

        int value = 0;

        while (i < traversal.size() && isdigit(traversal[i])) {
            value = value * 10 + (traversal[i] - '0');
            i++;
        }

        TreeNode* node = new TreeNode(value);

        while (stack.size() > depth)
            stack.pop_back();

        if (!stack.empty()) {
            if (!stack.back()->left)
                stack.back()->left = node;
            else
                stack.back()->right = node;
        }

        stack.push_back(node);
    }

    return stack.empty() ? nullptr : stack[0];
}

TreeNode* createTree(const vector<int>& values) {
    if (values.empty())
        return nullptr;

    vector<TreeNode*> nodes;

    for (int value : values)
        nodes.push_back(new TreeNode(value));

    for (int i = 0; i < values.size(); i++) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < values.size())
            nodes[i]->left = nodes[left];

        if (right < values.size())
            nodes[i]->right = nodes[right];
    }

    return nodes[0];
}

void printTree(TreeNode* root) {
    if (!root) {
        cout << "[]\n";
        return;
    }

    queue<TreeNode*> q;
    q.push(root);

    cout << "[";

    bool first = true;

    while (!q.empty()) {
        TreeNode* node = q.front();
        q.pop();

        if (!first)
            cout << ", ";
        first = false;

        if (node) {
            cout << node->val;
            q.push(node->left);
            q.push(node->right);
        } else {
            cout << "null";
        }
    }

    cout << "]\n";
}

void printVertical(const vector<vector<int>>& result) {
    cout << "[";

    for (int i = 0; i < result.size(); i++) {
        cout << "[";

        for (int j = 0; j < result[i].size(); j++) {
            cout << result[i][j];

            if (j + 1 < result[i].size())
                cout << ", ";
        }

        cout << "]";

        if (i + 1 < result.size())
            cout << ", ";
    }

    cout << "]\n";
}

int main() {
    TreeNode* p = createTree({1, 2, 3});
    TreeNode* q = createTree({1, 2, 3});

    cout << "1. " << (isSameTree(p, q) ? "true" : "false") << endl;

    TreeNode* root2 = createTree({1, 2, 2, 3, 4, 4, 3});

    cout << "2. " << (isSymmetric(root2) ? "true" : "false") << endl;

    TreeNode* root3 = createTree({4, 2, 7, 1, 3, 6, 9});

    invertTree(root3);

    cout << "3. ";
    printTree(root3);

    TreeNode* root4 = createTree({3, 1, 4, 2});
    cout << "4. " << kthSmallest(root4, 1) << endl;

    TreeNode* root5 = createTree({1, 2, 3, 4, 5});

    string data = serialize(root5);
    TreeNode* restored = deserialize(data);

    cout << "5. " << data << endl;
    printTree(restored);

    TreeNode* root6 = createTree({1, 2, 3});
    cout << "6. " << maxPathSum(root6) << endl;

    TreeNode* root7 = createTree({0, 0, 0, 0, 0});
    cout << "7. " << minCameraCover(root7) << endl;

    TreeNode* root8 = createTree({3, 9, 20, 0, 0, 15, 7});

    cout << "8. ";
    printVertical(verticalTraversal(root8));

    string traversal = "1-2--3--4-5--6--7";

    TreeNode* root9 = recoverFromPreorder(traversal);

    cout << "9. ";
    printTree(root9);

    return 0;
}
