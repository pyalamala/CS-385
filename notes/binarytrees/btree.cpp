#include <iostream>

using namespace std;

struct Node {
    int key;
    Node *left, *right;
};

void inorder(Node *n) {
    if (n != nullptr) {
        inorder(n->left);
        cout << n->key << endl;
        inorder(n->right);
    }
}

void preorder(Node *n) {
    if (n != nullptr) {
        cout << n->key << endl;
        preorder(n->left);
        preorder(n->right);
    }
}

void postorder(Node *n) {
    if (n != nullptr) {
        postorder(n->left);
        postorder(n->right);
        cout << n->key << endl;
    }
}

int sum_values(Node *n) {
    return (n != nullptr) ? n->key + sum_values(n->left) + sum_values(n->right) : 0;
}