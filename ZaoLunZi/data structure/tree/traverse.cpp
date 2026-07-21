#include <iostream>
#include <stack>
#include <deque>

using namespace std;

template <typename T>
struct Node{
    T data_;
    Node* left_;
    Node* right_;
    Node() = default;
    Node(T x) : data_(x), left_(nullptr), right_(nullptr) {}
};


template <typename T>
void traverse(Node<T>* root){//递归
    if(root == nullptr) return;

    traverse(root->left_);
    std::cout << root->data_ << " ";
    traverse(root->right_);
}

template <typename T>
void traverse1(Node<T>* root){//非递归先序遍历
    if(root == nullptr) return;
    stack<Node<T>*> s;
    s.push(root);

    while(!s.empty()){
        Node<T>* cur = s.top();
        cout << cur -> data_ << " ";
        s.pop();
        if(cur -> right_ != nullptr)
            s.push(cur -> right_);
        if(cur -> left_ != nullptr)
            s.push(cur -> left_);
    }
}

template <typename T>
void traverse2(Node<T>* root){//非递归中序遍历
    stack<Node<T>*> s;
    Node<T>* cur = root;
    while(!s.empty() || cur != nullptr){
        if(cur != nullptr){
            s.push(cur);
            cur = cur -> left_;
        }
        else{
            cur = s.top();
            s.pop();
            cout << cur -> data_ << " ";
            cur = cur -> right_;
        }
    }

}

template <typename T>
void traverse3(Node<T>* root){//非递归后序遍历
    if(root == nullptr) return;

    stack<Node<T>*> s;
    Node<T>* h = root;
    s.push(root);
    while(!s.empty()){
        Node<T>* cur = s.top();
        if(cur -> left_ != nullptr && cur -> left_ != h && cur -> right_ != h){
            s.push(cur -> left_);
        }
        else if(cur -> right_ != nullptr && cur -> right_ != h){
            s.push(cur -> right_);
        }
        else{
            h = s.top();
            cout << h->data_ << " ";
            s.pop();
        }
    }
}
//还可以交换先序遍历两个左子树的顺序，再倒一下


int main(){
    Node<int> c;
}
