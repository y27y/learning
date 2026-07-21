#include<iostream>
#include<vector>
#include<queue>
#include<unordered_map>
using namespace std;

struct Node{
    int val;
    Node* left;
    Node* right;
    Node(int v) : val(v), left(nullptr), right(nullptr) {}
};
vector<int> pre, in, post;
unordered_map<int,int> mp;

Node* Build1(int pl, int pr, int il, int ir){//前中建树
    if (pl > pr) return nullptr;

    int rootVal = pre[pl];
    Node* root = new Node(rootVal);

    int k = mp[rootVal];         // 根在中序的位置
    int leftSize = k - il;        // 左子树节点数

    root->left = Build1(pl + 1, pl + leftSize, il, k - 1);
    root->right = Build1(pl + leftSize + 1, pr, k + 1, ir);

    return root;
}

Node* Build2(int il, int ir, int pl, int pr){//中后建树
    if (il > ir) return nullptr;

    int rootval = post[pr];
    Node* root = new Node(rootval);

    int k = mp[rootval];         // 根在中序的位置
    int leftSize = k - il;        // 左子树节点数

    root->left = Build2(il, k - 1, pl, pl + leftSize - 1);
    root->right = Build2(k + 1, ir, pl + leftSize, pr - 1);

    return root;
}

void print_tree(Node* root){
    if (root == nullptr){
        return;
    }
    //pre
    //cout << root->val << " ";
    print_tree(root->left);
    //in
    //cout << root->val << " ";
    print_tree(root->right);
    //pos
    cout << root->val << " ";
}

void print_by_layer(Node* root){
    queue<Node*> q;
    int depth = 0;
    q.push(root);

    while (!q.empty()){
        int len = q.size();
        for(int i = 0; i < len; i++){
            Node* cur = q.front(); q.pop();
            cout << cur->val <<  " ";
            if (cur->left != nullptr){
                q.push(cur->left);
            }
            if (cur->right != nullptr){
                q.push(cur->right);
            }
        }
        depth++;
    }
    //cout << depth;
}
int main(){
    int n;
    cin >> n;

    pre.resize(n);
    in.resize(n);
    post.resize(n);

    for (int i = 0; i < n; i++) cin >> pre[i];
    for (int i = 0; i < n; i++) {
        cin >> in[i];
        mp[in[i]] = i;
    }
    for (int i = 0; i < n; i++) cin >> post[i];

    Node* root1 = Build1(0, n - 1, 0, n - 1);
    Node* root2 = Build2(0, n - 1, 0, n - 1);
    print_tree(root1);
    //print_tree(root2);
    //print_by_layer(root1);
    //print_by_layer(root2);
}

/*
9
8 3 1 6 4 7 10 14 13
1 3 4 6 7 8 10 13 14
1 4 7 6 3 13 14 10 8
*/