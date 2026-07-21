#ifndef MY_QUEUE
#define MY_QUEUE

#include <cstddef>
#include <stdexcept>

template <typename T>
class my_queue{
private:
    T* data;
    size_t front_;
    size_t rear_; //尾后
    size_t size_;
    size_t capacity_;
    void resize(size_t newcap);

public:
    explicit my_queue(size_t initcap = 16);
    ~my_queue();
    bool empty() const;    
    size_t size() const;
    T front();
    T back();
    void pop();
    void push(T x);

    void emplace();
    void swap();
};

template <typename T>
my_queue<T>::my_queue(size_t initcap) : data(new T[initcap]), front_(0), rear_(0), size_(0), capacity_(initcap) {}

template <typename T>
my_queue<T>::~my_queue(){
    delete[] data;
}

template <typename T>
void my_queue<T>::resize(size_t newcap){
    T* newdata = new T[newcap];
    for(size_t i = 0; i < size_; ++i){
        newdata[i] = data[(front_ + i) % capacity_];
    }
    delete[] data;
    data = newdata;
    capacity_ = newcap;
    front_ = 0;
    rear_ = size_;
    // bool operator==(const my_queue& other){
    //     return other.size_ == this->data;
    // }
}

template <typename T>
bool my_queue<T>::empty() const{
    return size_ == 0;
}

template <typename T>
T my_queue<T>::front(){
    if(empty()){
        throw std::out_of_range("queue is empty");
    }
    return data[front_];
}

template <typename T>
T my_queue<T>::back(){
    if(empty()){
        throw std::out_of_range("queue is empty");
    }
    return data[(rear_ + capacity_ - 1) % capacity_];
}

template <typename T>
void my_queue<T>::pop(){
    if(empty()){
        throw std::out_of_range("queue is empty");
    }
    T value = data[front_];
    front_ = (front_ + 1) % capacity_;
    --size_;
}
template <typename T>
size_t my_queue<T>::size() const{
    return size_;
}

template <typename T>
void my_queue<T>::push(T x){
    if(capacity_ == size_){
        resize(2 * capacity_);
    }
    data[rear_++] = x;
    size_++;
}


#endif