#include<iostream>
#include<vector>
using namespace std;

struct tree_node{
    int id;
    int val;
    tree_node* left;
    tree_node* right;
    tree_node(int id, int v) : id(id), val(v), left(nullptr), right(nullptr) {}
};


int main(){
    int n,w,u,v;
    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> w >> u >> v;
        
    }
}