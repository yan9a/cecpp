#include <iostream>
using namespace std;
class MyClass {
    void cbmethod0(int i);
    void cbmethod1(int i);
public:
    typedef void(MyClass::*cbm_t)(int);
    MyClass::cbm_t _cbtable[2];
    MyClass();
    void call();
};
MyClass::MyClass(){
    _cbtable[0] = &MyClass::cbmethod0;
    _cbtable[1] = &MyClass::cbmethod1;
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
    (this->*_cbtable[0])(0);
    (this->*_cbtable[1])(1);
}

int main(int, char**) {
    std::cout << "Hello call back method!\n";
    MyClass* p = new MyClass();
    p->call();
}
