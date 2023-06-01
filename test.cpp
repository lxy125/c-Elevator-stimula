#include <iostream>
using namespace std;









class A {

public:

    A()  { cout << "1 "; }

    ~A() { cout << "-1 "; }

};


class B : public A {

public:

    B()  { cout << "2 ";}

    ~B() {cout << "-2 ";}

};


void f(){

    A a;

}

int main(){

    B b;

    f();

}