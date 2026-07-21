#include<iostream>
#include<vector>
#include<queue>
#include<unordered_map>
#include<unordered_set>
using namespace std;    

struct Node{
    int data;
    Node* left;
    Node* right;
    Node(int val):data(val),left(NULL),right(NULL){}
};
void traverse(Node *root){//递归遍历
    if(root==nullptr){
        return;
    }
    //前序遍历
    //cout<< root->data << " ";
    traverse(root->left);
    //中序遍历
    traverse(root->right);
    //后序遍历
}
void levelordertraverse(Node *root){//层序遍历
    if(root==nullptr){
        return;
    }
    queue<Node*> q;
    q.push(root);
    int depth=1;
    while(!q.empty()){
        int size=q.size();
        for(int i=0;i<size;i++){
            Node *cur=q.front();
            //输出位置
            cout << cur->data << " ";
            q.pop();
            if(cur->left!=nullptr){
                q.push(cur->left);
            }
            if(cur->right!=nullptr){
                q.push(cur->right);
            }
        }
        depth++;
    }
}
Node* CreateTree(int n){//（父 左 右）构建二叉树(缺失的子节点用-1表示)
    unordered_map<int,Node*> mp;
    unordered_set<int> isChlid;
    for(int i=0;i<n;i++){
        int p,l,r;
        cin>>p>>l>>r;

        if(!mp[p]) mp[p]=new Node(p);
        
        Node *parent=mp[p];

        if(l!=-1){
            if(!mp[l]) mp[l]=new Node(l);
            parent->left=mp[l];
            isChlid.insert(l);
        }

        if(r!=-1){
            if(!mp[r]) mp[r]=new Node(r);
            parent->right=mp[r];
            isChlid.insert(r);
        }
    } 

    for(auto &it : mp){
        if(!isChlid.count(it.first)){
            return it.second;
        }
    }
    return nullptr;
}

int main(){
    int n;
    cin>>n;
    Node *root=CreateTree(n);
    //traverse(root);
    levelordertraverse(root);
    return 0;
}