#include<iostream>
#include<vector>
#include<queue>
#include<unordered_map>
#include<unordered_set>
using namespace std;

struct multiway_treenode{
    int data;
    vector<multiway_treenode*> children;
    multiway_treenode(int val) : data(val){}
};

void traverse(multiway_treenode* root){//递归遍历
    if(root == nullptr){
        return;
    }
    //前序遍历
    //cout<< root->data << " ";
    for(multiway_treenode* child : root->children){
        traverse(child);
    }
    //后序遍历
}

void level_order_traverse(multiway_treenode* root){//层序遍历多叉树
    if(root == nullptr){
        return;
    }
    queue<multiway_treenode*> q;
    q.push(root);
    int depth = 1;
    while(!q.empty()){
        int sz = q.size();
        for(int i=0;i<sz;i++){
            multiway_treenode* parent = q.front();
            q.pop();
            //输出位置
            cout<<parent->data<<" ";
            for(auto &child : parent->children){
                if(child != nullptr){
                    q.push(child);
                }
            }
        }
        depth++;
    }
}

multiway_treenode* create_multiway_tree(int n){//创建多叉树（n为节点数）
    unordered_map<int,multiway_treenode*> mp;
    unordered_set<int> is_child;
    for(int i=0;i<n;i++){
        int temp_parent;
        int temp_child;
        cin >> temp_parent;
        if(mp[temp_parent] == nullptr){
            mp[temp_parent] = new multiway_treenode(temp_parent);//输入了data
        }
        while(cin >> temp_child && temp_child != -1){//每次输入最后必须是-1
            if(mp[temp_child] == nullptr){
                mp[temp_child] = new multiway_treenode(temp_child);//data
            }
            mp[temp_parent]->children.push_back(mp[temp_child]);
            is_child.insert(temp_child);
        }
    }

    for(auto &it : mp){
        if(is_child.count(it.first) == 0){
            return it.second;
        }
    }
    return nullptr;
}

int main(){
    int n;
    cin>>n;
    multiway_treenode* root=create_multiway_tree(n);
    level_order_traverse(root);
    //traverse(root);
}