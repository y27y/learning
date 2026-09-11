#ifndef MY_LIST
#define MY_LIST

template <typename T>
class my_list {//
private:
    struct node{
        T data;
        node* next;
        node(T val) : data(val), next(nullptr) {}
    }
    
};


#endif