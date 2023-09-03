#include <iostream>
#include <functional>
using namespace std;
class MyClass {
    void cbmethod0(int i);
    void cbmethod1(int i);
public:
    // direct call back
    typedef void(MyClass::*cbm_t)(int);
    MyClass::cbm_t _cbtable[2];
    //-------------------
    // functional
    // https://en.cppreference.com/w/cpp/utility/functional/placeholders
    std::function<void(int)> _cbtable2[2];
    //-------------------
    // lambda
    std::function<void(int)> _cbtable3[2];
    //-------------------
    MyClass();
    void call();
};

MyClass::MyClass(){
    // direct
    _cbtable[0] = &MyClass::cbmethod0;
    _cbtable[1] = &MyClass::cbmethod1;

    // functional
    using std::placeholders::_1;
    _cbtable2[0] = std::bind(&MyClass::cbmethod0, this, _1);
    _cbtable2[1] = std::bind(&MyClass::cbmethod1, this, _1);

     // lambda
    _cbtable3[0] = [&](int a){this->cbmethod0(a);};
    _cbtable3[1] = [&](int a){this->cbmethod1(a);};

}
void MyClass::cbmethod0(int i)
{
    cout<< "cbmethod0, i = "<<i<<endl;   
}
void MyClass::cbmethod1(int i)
{
    cout<< "cbmethod1, i = "<<i<<endl; 
}
void MyClass::call()
{
    // direct
    (this->*_cbtable[0])(0);
    (this->*_cbtable[1])(1);

    // functional
    this->_cbtable2[0](2);
    this->_cbtable2[1](3);

    // lambda
    this->_cbtable3[0](4);
    this->_cbtable3[1](5);
}

class MyClass2 {
    void cbmethod0(int i);
    void cbmethod1(int i);
public:
    // direct call back
    typedef void(MyClass::*cbm_t)(int);
    MyClass::cbm_t _cbtable[2];
    //-------------------
    // functional
    // https://en.cppreference.com/w/cpp/utility/functional/placeholders
    std::function<void(int)> _cbtable2[2];
    //-------------------
    // lambda
    std::function<void(int)> _cbtable3[2];
    //-------------------
    MyClass2();
    void call();
};

MyClass2::MyClass2(){
    // direct
    _cbtable[0] = &MyClass::cbmethod0;
    _cbtable[1] = &MyClass::cbmethod1;

    // functional
    using std::placeholders::_1;
    _cbtable2[0] = std::bind(&MyClass::cbmethod0, this, _1);
    _cbtable2[1] = std::bind(&MyClass::cbmethod1, this, _1);

     // lambda
    _cbtable3[0] = [&](int a){this->cbmethod0(a);};
    _cbtable3[1] = [&](int a){this->cbmethod1(a);};

}

int main(int, char**) {
    std::cout << "Hello call back methods!\n";
    MyClass* p = new MyClass();
    p->call();

    MyClass2* p2 = new MyClass2();
    p2->call();
}
