#include <iostream>

using namespace std;

struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
};
Node *findMin(Node *root)
{
    if (root == NULL)
    {
        cout << "tree is empty";
        return nullptr;
    }
    Node *temp = root;
    while (temp->left != NULL)
    {
        temp = temp->left;
    }
    return temp;
}

Node *findMax(Node *root)
{
    if (root == NULL)
    {
        cout << "tree is empty";
        return nullptr;
    }
    Node *temp = root;
    while (temp->right != NULL)
    {
        temp = temp->right;
    }
    return temp;
}

Node *find(Node *root, int target)
{
    if (root == NULL)
        return NULL;
    if (root->data == target)
        return root;
    if (root->data >= target)
        return find(root->left, target);
    else
        return find(root->right, target);
}

Node *insert(Node *root, int val)
{
    if (root == NULL)
    {
        root = new Node();
        root->data = val;
        root->left = root->right = nullptr;
    }
    else if (root->data >= val)
        root->left = insert(root->left, val);
    else
        root->right = insert(root->right, val);
    return root;
}

int get_node_count(Node *root)
{
    if (root == NULL)
        return 0;
    return 1 + get_node_count(root->left) + get_node_count(root->right);
}

void delete_tree(Node *root)
{
    if (root == NULL)
        return;
    if (root->left)
    {
        delete_tree(root->left);
    }
    else if (root->right)
    {
        delete_tree(root->right);
    }
    delete root;
}

bool is_in_tree(Node *root, int target)
{
    if (root == NULL)
        return false;
    if (root->data > target)
    {
        return is_in_tree(root->left, target);
    }
    if (root->data < target)
    {
        return is_in_tree(root->right, target);
    }
    else
    {
        return true;
    }
}

int get_height(Node *root)
{
    if (root == NULL)
        return -1;
    int leftHeight = get_height(root->left);
    int rightHeight = get_height(root->right);

    return max(leftHeight, rightHeight) + 1;
}

bool is_binary_check(Node *root, int minValue, int maxValue)
{
    if (root == NULL)
        return true;

    if (root->data > minValue && root->data < maxValue &&
        is_binary_check(root->left, minValue, root->data) &&
        is_binary_check(root->right, root->data, maxValue))
        return true;
    else
        return false;
}
bool is_binary_search_tree(Node *root)
{
    return is_binary_check(root, INT_MIN, INT_MAX);
}

Node *delete_value(Node *root, int target)
{
    if (root == NULL)
    {
        return root;
    }
    else if (root->data > target)
        root->left = delete_value(root->left, target);
    else if (root->data < target)
        root->right = delete_value(root->right, target);
    else
    {
        if (root->left == NULL && root->right == NULL)
        {
            delete root;
            root = NULL;
        }
        else if (root->left == NULL)
        {
            struct Node *temp = root;
            root = root->right;
            delete temp;
        }
        else if (root->right == NULL)
        {
            struct Node *temp = root;
            root = root->left;
            delete temp;
        }
        else
        {
            struct Node *temp = findMin(root->right);
            root->data = temp->data;
            root->right = delete_value(root->right, temp->data);
        }
    }
    return root;
}

Node *get_successor(Node *root, int target)
{
    struct Node *current = find(root, target);
    if (current == NULL)
        return NULL;

    if (current->right != NULL)
    {
        return findMin(current->right);
    }
    else
    {
        struct Node *successor = NULL;
        struct Node *ancestor = root;

        while (ancestor != current)
        {
            if (current->data < ancestor->data)
            {
                successor = ancestor;
                ancestor = ancestor->left;
            }
            else
            {
                ancestor = ancestor->right;
            }
        }
        return successor;
    }
}

void print_values(Node *root)
{
    struct Node *temp = findMin(root);
    while (temp != NULL)
    {
        cout << temp->data << ' ';
        temp = get_successor(root, temp->data);
    }
}

int main()
{
    Node *root = nullptr;

    // BST에 값 삽입
    int values[] = {20, 10, 30, 5, 15, 25, 35, 12, 18};
    int n = sizeof(values) / sizeof(values[0]);
    for (int i = 0; i < n; i++)
    {
        root = insert(root, values[i]);
    }

    cout << "중위 순회 결과: ";
    print_values(root);
    cout << endl;

    cout << "노드 개수: " << get_node_count(root) << endl;
    cout << "트리 높이: " << get_height(root) << endl;
    cout << "BST인가? " << (is_binary_search_tree(root) ? "Yes" : "No") << endl;

    // 특정 노드의 존재 여부 및 후속자 테스트
    int testVal = 15;
    if (is_in_tree(root, testVal))
    {
        cout << testVal << " 노드가 트리에 존재합니다." << endl;
        Node *succ = get_successor(root, testVal);
        if (succ)
            cout << testVal << " 의 중위 후속자는 " << succ->data << " 입니다." << endl;
        else
            cout << testVal << " 의 중위 후속자가 없습니다." << endl;
    }
    else
    {
        cout << testVal << " 노드가 트리에 존재하지 않습니다." << endl;
    }

    // 노드 삭제 테스트 (예: 10 삭제)
    cout << "노드 10 삭제 후 중위 순회 결과: ";
    root = delete_value(root, 10);
    print_values(root);
    cout << endl;

    // 트리 메모리 해제
    delete_tree(root);

    return 0;
}