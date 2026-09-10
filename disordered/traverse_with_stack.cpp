#include <iostream>
#include <stack>
#include <unordered_map>
#include <unordered_set>
// #include "head\tree.hpp"

struct node {
    int data;
    node* left;
    node* right;
    node(int x) : data(x), left(nullptr), right(nullptr) {}
};

node* plant_tree(int n) {
    std::unordered_map<int, node*> mp;
    std::unordered_set<int> is_child;
    int root, l, r;
    for (int i = 0; i < n; i++) {
        std::cin >> root >> l >> r;
        if (!mp[root]) {
            mp[root] = new node(root);
        }
        if (l != -1) {
            if (!mp[l]) {
                mp[l] = new node(l);
            }
            mp[root]->left = mp[l];
            is_child.insert(l);
        }
        if (r != -1) {
            if (!mp[r]) {
                mp[r] = new node(r);
            }
            mp[root]->right = mp[r];
            is_child.insert(r);
        }
    }
    for (auto& x : mp) {
        if (!is_child.count(x.first)) {
            return x.second;
        }
    }
    return nullptr;
}

void traverse_with_stack_1(node* root) { // 先序
    if (root == nullptr) {
        return;
    }
    std::stack<node*> s;
    s.push(root);
    while (!s.empty()) {
        node* cur = s.top();
        std::cout << cur->data << " ";
        s.pop();
        if (cur->right != nullptr) {
            s.push(cur->right);
        }
        if (cur->left != nullptr) {
            s.push(cur->left);
        }
    }
    return;
}

void traverse_with_stack_2(node* root) { // 中序
    if (root == nullptr) {
        return;
    }
    std::stack<node*> s;
    node* cur = root;
    while (!s.empty()) {
        if (cur != nullptr) {
            s.push(cur);
            cur = cur->left;
        } else {
            cur = s.top();
            std::cout << cur->data << " ";
            s.pop();
            cur = cur->right;
        }
    }
    return;
}

void traverse_with_stack_3_1(node* root) { // 后序，两个栈
    if (root == nullptr) {
        return;
    }
    std::stack<node*> s1;
    std::stack<node*> s2;
    node* cur = root;
    s1.push(cur);
    while (!s1.empty()) {
        node* cur = s1.top();
        s2.push(cur);
        s1.pop();
        if (cur->left != nullptr) {
            s1.push(cur->left);
        }
        if (cur->right != nullptr) {
            s1.push(cur->right) ;
        }
    }

    while (!s2.empty()) {
        std::cout << s2.top()->data << " ";
        s2.pop();
    }
}

void traverse_with_stack_3_2(node* root) { // 后序，一个栈
    if(root == nullptr){
        return;
    }
    std::stack<node*> s;
    while(!s.empty()){
        
    }
}

void traverse(node* root) {
    if (root == nullptr) {
        return;
    }

    traverse(root->left);
    traverse(root->right);
    std::cout << root->data << " ";
}

int main() {
    // int n;
    // std::cin >> n;
    // node* root = plant_tree(n);
    node* root = new node(1);
    root->left = new node(2);
    root->right = new node(3);
    root->left->left = new node(4);
    root->left->right = new node(5);
    root->right->left = new node(6);
    root->right->right = new node(7);

    // traverse_with_stack_1(root);
    // traverse_with_stack_2(root);
    // std::cout << std::endl;
    traverse(root);
    std::cout << std::endl;
    traverse_with_stack_3_1(root);
}

/*
1 2 3
2 4 5
3 6 7
4 -1 -1
5 -1 -1
6 -1 -1
7 -1 -1
*/