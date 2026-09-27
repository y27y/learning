#include<iostream>
#include<stdexcept>
#include <list.hpp>

class my_list{//0--n
private:
    struct Node{
        int data;
        Node* next;
        Node(int val) : data(val), next(nullptr) {}
    };
    //friend mylist::Node* createNode(int val);

    Node* head = nullptr;
    Node* tail = nullptr;
    size_t sz = 0;

    Node* node_at(size_t pos) const {
        if(pos >= sz) return nullptr;
        Node* cur = head;
        while(pos--) cur = cur -> next;
        return cur;
    }
public:
    void push_front(int val){
        Node* temp = new Node(val);
        temp -> next = head;
        head = temp;
        if(sz == 0) tail = head;
        sz++;
    }

    void push_back(int val){
        Node* temp = new Node(val);
        if(sz == 0){
            head = tail = temp;
        }
        else{
            tail -> next = temp;
            tail = temp;
        }
        sz++;
    }

    bool insert(size_t pos, int val){
        if(pos > sz) return false;
        if(pos == 0){
            push_front(val);
            return true;
        }
        if(pos == sz){
            push_back(val);
            return true;
        }
        Node* temp = new Node(val);
        Node* prev = node_at(pos - 1);
        temp -> next = prev -> next;
        prev -> next = temp;
        sz++;
        return true;
    }

    bool erase(size_t pos){
        if(pos >= sz) return false;
        if(sz == 1){
            Node* temp = head;
            head = tail = nullptr;
            delete temp;
            return true;
        }
        if(pos == 0){
            Node* prev = head;
            head = head -> next;
            delete prev;
            return true;
        }
        if(pos == sz - 1){
            tail = node_at(pos - 1);
            delete tail -> next;
            return true;
        }
        Node* prev = node_at(pos - 1);
        Node* target = prev -> next;
        prev -> next = target -> next;
        delete target;
        return true;
    }
    
    int find(int target) const {
        int pos = 0;
        Node* cur = head;
        while(pos < sz){
            if(cur -> data == target) return pos;
            cur = cur -> next;
            pos++;
        }
        return -1;
    }

    bool contains(int x) const {
        return find(x) != -1;
    }

    int& at(size_t pos){
        if(pos >= sz) throw std::out_of_range("mylist::out_of_range");
        Node* cur = node_at(pos);
        return cur -> data;
    }

    const int& at(size_t pos) const {
        if(pos >= sz) throw std::out_of_range("mylist::out_of_range");;
        Node* cur = node_at(pos);
        return cur -> data;
    }

    bool empty() const {
        return head == nullptr;
    }

    int size() const {
        return sz;
    }

    void clear(){
        Node* cur = head;
        while(cur != nullptr){
            Node* nxt = cur -> next;
            delete cur;
            cur = nxt;
        }
        head = tail = nullptr;
        sz = 0;
    }

    bool pop_front(){
        if(empty()) return false;
        erase(0);
    }

    bool pop_back(){
        if(empty()) return false;
        erase(sz - 1);
    }

    int& front(){
        if(empty()) throw std::out_of_range("mylist::front on empty list");
        return head -> data;
    }
    
    const int& front() const {
        if(empty()) throw std::out_of_range("mylist::front on empty list");
        return head -> data;
    }

    int& back() {
        if(empty()) throw std::out_of_range("mylist::back on empty list");
        return tail -> data;
    }

    const int& back() const {
        if(empty()) throw std::out_of_range("mylist::back on empty list");
        return tail -> data;
    }
    
    void reverse(){
        Node* cur = head;
        Node* nxt = cur -> next;
        Node* prev = nullptr;
        tail = head;
        while(cur != nullptr){
            nxt = cur -> next;
            cur -> next = prev;
            prev = cur;
            cur = nxt;
        }
        head = prev;
    }
    int remove_all(int val){
        int num = 0;
        for(int i = 0; i < sz; i++){
            Node* cur = node_at(i);
            if(cur -> data = val){
                erase(i);
                
            }
        }
        return num;
    }

    void print(size_t start = 0, size_t end = static_cast<size_t>(-1)){
        if(sz == 0 || start >= sz) return;
        if(end == static_cast<size_t>(-1) || end >= sz) end = sz - 1;
        if(start > end) return;

        Node* cur = node_at(start);
        for(size_t i = start; i <= end && cur != nullptr; ++i){
            std::cout << cur -> data << " ";
            cur = cur -> next;
        }
    }
    
};


int main(){

    my_list l;

//     l.push_back(114);
//     l.push_back(514);
//     l.push_back(19);
    
//     l.erase(0);l.print(0, 1); 
}
