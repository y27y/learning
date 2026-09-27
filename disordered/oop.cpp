#include <iostream>

class Animal {
private:
    //
public:
    int age;
    int size;
    virtual void run() {}
};
void Animal::run() {
    std::cout << "Animal Run" << std::endl;
}

//-------------------------------

class Dog : public Animal {
    virtual void run() override {}
};
void Dog::run() {
    std::cout << "Dog Run" << std::endl;
}

int main() {
    Dog d;
    d.run();
}